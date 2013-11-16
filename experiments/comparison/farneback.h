#ifndef farneback_h
#define farneback_h

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

class Farneback
{
  public:
    void drawOptFlowMap(int step);
    Mat calcOptFlowMap(Mat frame, double pyr_scale, int levels, int winsize, int iterations, int poly_n, double poly_sigma, int flags); 
    
  private:
    Mat prevgray, gray, flow, cflow;
  
};

#endif /* farneback_h */