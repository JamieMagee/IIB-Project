#include "farneback.h"

void Farneback::drawOptFlowMap(int step)
{
  double l_max;

  for (int y = 0; y < cflow.rows; y += step)  
  {
    for (int x = 0; x < cflow.cols; x += step)
    {
      const Point2f& fxy = flow.at<Point2f>(y, x);
      double l = sqrt(fxy.x*fxy.x + fxy.y*+fxy.y);                                                             
      if(l>l_max) l_max = l;
    }
  }
	
	for(int y = 0; y < cflow.rows; y += step)
	{
    for(int x = 0; x < cflow.cols; x += step)
    {
      Point p = Point(x,y);
      const Point2f& fxy = flow.at<Point2f>(y, x);
      double l = sqrt(fxy.x*fxy.x + fxy.y*fxy.y);
      
      if (l>0.0)
      {
        double scaleSize = 5.0 * l/l_max; 

        Point p2 = Point(cvRound(x+fxy.x), cvRound(y+fxy.y));
        line(cflow, p, p2, CV_RGB(0, 255, 0), 1, CV_AA);

        double angle;                                                                          
        angle = atan2( (double) p.y - p2.y, (double) p.x - p2.x );
        
        p.x = (int) (p2.x + scaleSize * cos(angle + 3.1416 / 4));
        p.y = (int) (p2.y + scaleSize * sin(angle + 3.1416 / 4));
        line(cflow, p, p2, CV_RGB(0, 255, 0), 1, CV_AA);

        p.x = (int) (p2.x + scaleSize * cos(angle - 3.1416 / 4));
        p.y = (int) (p2.y + scaleSize * sin(angle - 3.1416 / 4));
        line(cflow, p, p2, CV_RGB(0, 255, 0), 1, CV_AA);    
      }
    }
	}
}

Mat Farneback::calcOptFlowMap(Mat frame, double pyr_scale, int levels, int winsize, int iterations, int poly_n, double poly_sigma, int flags)
{
  cvtColor(frame, gray, CV_BGR2GRAY);
  
  if(prevgray.data)
  {
    calcOpticalFlowFarneback(prevgray, gray, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
    cvtColor(prevgray, cflow, CV_GRAY2BGR);
    drawOptFlowMap(16);
  }
  std::swap(prevgray, gray);
  return cflow;
}