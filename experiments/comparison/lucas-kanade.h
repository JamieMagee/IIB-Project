#ifndef lucas_kanade_h
#define lucas_kanade_h

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

class LucasKanade
{
  public:
    void drawOptFlowMap(cv::Mat &frame, std::vector<cv::Point2f> prevPts, std::vector<cv::Point2f> nextPts);
    cv::Mat calcOptFlowMap(cv::Mat frame, cv::FileStorage file, int maxCorners);
  
  private:
    cv::Mat prevImg, nextImg;
    std::vector<cv::Point2f> prevPts, nextPts;
    std::vector<uchar> status;
    std::vector<float> err;
};

#endif /* lucas_kanade_h */