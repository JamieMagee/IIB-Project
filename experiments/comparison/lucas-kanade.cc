#include "lucas-kanade.h"

void LucasKanade::drawOptFlowMap(Mat &frame, vector<Point2f> prevPts, vector<Point2f> nextPts)
{
  double l_max, l;
  for(int i = 0; i < nextPts.size(); i++)
  {
    l = sqrt(nextPts[i].x*nextPts[i].x+nextPts[i].y*nextPts[i].y);
	  if(l>l_max) l_max = l;	 
  }
  
  for(int i = 0; i < nextPts.size(); i++)
  {
    double scaleSize = 5.0 * l/l_max; 
    
    Point points[2];
    points[0] = Point(cvRound(prevPts[i].x), cvRound(prevPts[i].y));
    points[1] = Point(cvRound(nextPts[i].x), cvRound(nextPts[i].y));

    line(frame, points[0], points[1], CV_RGB(0, 255, 0), 1, CV_AA);
	  
	  double angle;                                                                          
	  angle = atan2((double) points[0].y - points[1].y, (double) points[0].x - points[1].x );
	
	  points[0].x = (int) (points[1].x + scaleSize * cos(angle + 3.1416 / 4));
	  points[0].y = (int) (points[1].y + scaleSize * sin(angle + 3.1416 / 4));
	  line(frame, points[0], points[1], CV_RGB(0, 255, 0), 1,CV_AA);

	  points[0].x = (int) (points[1].x + scaleSize * cos(angle - 3.1416 / 4));
	  points[0].y = (int) (points[1].y + scaleSize * sin(angle - 3.1416 / 4));
	  line(frame, points[0], points[1], CV_RGB(0, 255, 0), 1, CV_AA);
  }
}

Mat LucasKanade::calcOptFlowMap(Mat frame, int maxCorners)
{
  cvtColor(frame, nextImg, CV_BGR2GRAY);
  goodFeaturesToTrack(nextImg, nextPts, maxCorners, 0.01, 5);
  cornerSubPix(nextImg, nextPts, Size(10, 10), Size(-1, -1), TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3));
  
  if(prevImg.data)
  {
    calcOpticalFlowPyrLK(prevImg, nextImg, prevPts, nextPts, status, err);
    drawOptFlowMap(frame, prevPts, nextPts);
  }
  std::swap(prevImg, nextImg);
  std::swap(prevPts, nextPts);
  return frame;
}