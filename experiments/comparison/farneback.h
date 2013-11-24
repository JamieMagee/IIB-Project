#ifndef farneback_h
#define farneback_h

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace std;
using namespace cv;

class Farneback
{
  public:
    void drawOptFlowMap(Mat &frame, int step);
    void drawOptFlowColour(Mat &frame);
    Mat calcOptFlowMap(Mat frame, double pyr_scale, int levels, int winsize, int iterations, int poly_n, double poly_sigma, int flags);
    
  private:
    Mat prevImg, nextImg, flow;
  
};

#endif /* farneback_h */