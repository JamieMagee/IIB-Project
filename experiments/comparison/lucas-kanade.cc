#include "lucas-kanade.h"

void LucasKanade::drawOptFlowMap(cv::Mat &frame, std::vector<cv::Point2f> prevPts, std::vector<cv::Point2f> nextPts)
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
    
    cv::Point points[2];
    points[0] = cv::Point(cvRound(prevPts[i].x), cvRound(prevPts[i].y));
    points[1] = cv::Point(cvRound(nextPts[i].x), cvRound(nextPts[i].y));

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

cv::Mat LucasKanade::calcOptFlowMap(cv::Mat frame, cv::FileStorage file, int maxCorners)
{
  cvtColor(frame, nextImg, CV_BGR2GRAY);
  
  //goodFeaturesToTrack(nextImg, nextPts, maxCorners, 0.0000001, 0);
  //cornerSubPix(nextImg, nextPts, cv::Size(10, 10), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3));
  for (int i = 0; i < frame.rows; i+=16)
  {
    for(int j = 0; j < frame.cols; j+=16)
    {
      nextPts.push_back(cv::Point2f(i, j));
    }
  }
  
  if(prevImg.data)
  {
    calcOpticalFlowPyrLK(prevImg, nextImg, prevPts, nextPts, status, err);
    file << "nextPts" << nextPts;
    file << "prevPts" << prevPts;
    drawOptFlowMap(frame, prevPts, nextPts);
  }
  std::swap(prevImg, nextImg);
  std::swap(prevPts, nextPts);
  return frame;
}