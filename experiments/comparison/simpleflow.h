#ifndef simpleflow_h
#define simpleflow_h

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

class SimpleFlow
{
  public:
    cv::Mat calcOptFlowMap(cv::Mat &frame, int layers, int averaging_block_size, int max_flow);
    void drawOptFlowMap(cv::Mat &frame, int step);
  
  private:
    cv::Mat prevImg, nextImg, flow;
  
};

#endif