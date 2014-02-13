#ifndef farneback_h
#define farneback_h

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

class Farneback
{
  public:
    void drawOptFlowMap(cv::Mat &frame, int step);
    void drawOptFlowColour(cv::Mat &frame);
    cv::Mat calcOptFlowMap(cv::Mat frame, cv::FileStorage file, double pyr_scale, int levels, int winsize, int iterations, int poly_n, double poly_sigma, int flags);
    
  private:
    cv::Mat prevImg, nextImg, flow;
  
};

#endif /* farneback_h */