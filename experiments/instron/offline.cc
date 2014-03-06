#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <cstdio>
#include <iostream>

void help(char** argv)
{
	printf("Usage: %s frame1 frame2 output...\n\n", argv[0]);
}

void drawOptFlowMap(cv::Mat &frame, cv::Mat flow, int step)
{
  double l_max;

  for (int y = 0; y < frame.rows; y += step)  
  {
    for (int x = 0; x < frame.cols; x += step)
    {
      const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
      double l = sqrt(fxy.x*fxy.x + fxy.y*+fxy.y);                                                             
      if(l>l_max) l_max = l;
    }
  }
	
	for(int y = 0; y < frame.rows; y += step)
	{
    for(int x = 0; x < frame.cols; x += step)
    {
      cv::Point p = cv::Point(x,y);
      const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
      double l = sqrt(fxy.x*fxy.x + fxy.y*fxy.y);
      
      if (l>0.0)
      {
        double scaleSize = 5.0 * l/l_max; 

        cv::Point p2 = cv::Point(cvRound(x+fxy.x), cvRound(y+fxy.y));
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

void drawOptFlowColour(cv::Mat &frame, cv::Mat flow)
{
  cv::Mat HSV(frame.rows, frame.cols, CV_8UC3);
  cv::Mat _hsv[2];
  cv::Mat mag, ang, xy[2];
  
  split(flow, xy);
  
  cartToPolar(xy[0], xy[1], mag, ang, true);
  normalize(mag, mag, 0, 255, cv::NORM_MINMAX);
  
  ang.convertTo(_hsv[0], CV_8UC1);
  _hsv[1] = cv::Mat::ones(ang.size(), CV_8UC1);
  _hsv[1] = 255;
  mag.convertTo(_hsv[2], CV_8UC1);
  merge(_hsv, 3, HSV);
  cvtColor(HSV, frame, CV_HSV2BGR);
}

cv::Mat calcOptFlowMap(cv::Mat frame/*, cvFileStorage file*/, double pyr_scale, int levels, int winsize, int iterations, int poly_n, double poly_sigma, int flags)
{
  static cv::Mat prevImg, nextImg, flow;
  cvtColor(frame, nextImg, CV_BGR2GRAY);
  
  if(prevImg.data)
  {
    calcOpticalFlowFarneback(prevImg, nextImg, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
    //drawOptFlowColour(frame, flow);
    drawOptFlowMap(frame, flow, 16);
  }
  std::swap(prevImg, nextImg);
  return frame;
}

int main(int argc, char** argv)
{
  help(argv);
  if (argc < 4)
  {  
    printf("Three input arguments are required\n");
    exit(1);
  }
  
  cv::Mat frame1 = cv::imread(argv[1]);
  cv::Mat frame2 = cv::imread(argv[2]);
  cv::Mat flow;

  if (frame1.empty()) {
    printf("Image #1 : %s cannot be read\n", argv[0]);
    exit(1);
  }

  if (frame2.empty()) {
    printf("Image #2 : %s cannot be read\n", argv[1]);
    exit(1);
  }

  if (frame1.rows != frame2.rows && frame1.cols != frame2.cols) {
    printf("Images should be of equal sizes\n");
    exit(1);
  }

  if (frame1.type() != 16 || frame2.type() != 16) {
    printf("Images should be of equal type CV_8UC3\n");
    exit(1);
  }
  
  flow = calcOptFlowMap(frame1, 0.5, 3, 15, 3, 5, 1.2, 0);
  flow = calcOptFlowMap(frame2, 0.5, 3, 15, 3, 5, 1.2, 0);
  cv::imwrite(argv[3], frame2);
  
  cv::namedWindow(argv[3], CV_WINDOW_AUTOSIZE);
  cv::imshow(argv[3], frame2);
  
  cv::waitKey(0);
}