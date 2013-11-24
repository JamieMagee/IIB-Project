#include "farneback.h"

void Farneback::drawOptFlowMap(Mat &frame, int step)
{
  double l_max;

  for (int y = 0; y < frame.rows; y += step)  
  {
    for (int x = 0; x < frame.cols; x += step)
    {
      const Point2f& fxy = flow.at<Point2f>(y, x);
      double l = sqrt(fxy.x*fxy.x + fxy.y*+fxy.y);                                                             
      if(l>l_max) l_max = l;
    }
  }
	
	for(int y = 0; y < frame.rows; y += step)
	{
    for(int x = 0; x < frame.cols; x += step)
    {
      Point p = Point(x,y);
      const Point2f& fxy = flow.at<Point2f>(y, x);
      double l = sqrt(fxy.x*fxy.x + fxy.y*fxy.y);
      
      if (l>0.0)
      {
        double scaleSize = 5.0 * l/l_max; 

        Point p2 = Point(cvRound(x+fxy.x), cvRound(y+fxy.y));
        line(frame, p, p2, CV_RGB(0, 255, 0), 1, CV_AA);

        double angle;                                                                          
        angle = atan2( (double) p.y - p2.y, (double) p.x - p2.x );
        
        p.x = (int) (p2.x + scaleSize * cos(angle + 3.1416 / 4));
        p.y = (int) (p2.y + scaleSize * sin(angle + 3.1416 / 4));
        line(frame, p, p2, CV_RGB(0, 255, 0), 1, CV_AA);

        p.x = (int) (p2.x + scaleSize * cos(angle - 3.1416 / 4));
        p.y = (int) (p2.y + scaleSize * sin(angle - 3.1416 / 4));
        line(frame, p, p2, CV_RGB(0, 255, 0), 1, CV_AA);    
      }
    }
	}
}

void Farneback::drawOptFlowColour(Mat &frame)
{
  Mat HSV(frame.rows, frame.cols, CV_8UC3);
  Mat _hsv[2];
  Mat mag, ang, xy[2];
  
  split(flow, xy);
  
  cartToPolar(xy[0], xy[1], mag, ang, true);
  normalize(mag, mag, 0, 255, NORM_MINMAX);
  
  ang.convertTo(_hsv[0], CV_8UC1);
  _hsv[1] = Mat::ones(ang.size(), CV_8UC1);
  _hsv[1] = 255;
  mag.convertTo(_hsv[2], CV_8UC1);
  merge(_hsv, 3, HSV);
  cvtColor(HSV, frame, CV_HSV2BGR);
    
}

Mat Farneback::calcOptFlowMap(Mat frame, double pyr_scale, int levels, int winsize, int iterations, int poly_n, double poly_sigma, int flags)
{
  cvtColor(frame, nextImg, CV_BGR2GRAY);
  
  if(prevImg.data)
  {
    calcOpticalFlowFarneback(prevImg, nextImg, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
    drawOptFlowColour(frame);
    drawOptFlowMap(frame, 16);
  }
  std::swap(prevImg, nextImg);
  return frame;
}