#ifndef simpleflow_h
#define simpleflow_h

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

class SimpleFlow
{
  public:
    Mat calcOptFlowMap(Mat &frame, int layers, int averaging_block_size, int max_flow);
    void drawOptFlowMap(Mat &frame, int step);
  
  private:
    Mat prevImg, nextImg, flow;
  
};

#endif