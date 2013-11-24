#include "simpleflow.h"

void SimpleFlow::drawOptFlowMap(Mat &frame, int step)
{
  double l_max;

  for (int y = 0; y < flow.rows; y += step)  
  {
    for (int x = 0; x < flow.cols; x += step)
    {
      const Point2f& fxy = flow.at<Point2f>(y, x);
      double l = sqrt(fxy.x*fxy.x + fxy.y*+fxy.y);                                                             
      if(l>l_max) l_max = l;
    }
  }
	
	for(int y = 0; y < flow.rows; y += step)
	{
    for(int x = 0; x < flow.cols; x += step)
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

Mat SimpleFlow::calcOptFlowMap(Mat &frame, int layers, int averaging_block_size, int max_flow)
{
  nextImg = frame;
  if (prevImg.data)
  {
    calcOpticalFlowSF(prevImg, nextImg, flow, layers, averaging_block_size, max_flow);
    drawOptFlowMap(frame, 16);
  }
  std::swap(prevImg, nextImg);
  return frame;
}

