#ifndef lucas_kanade_h
#define lucas_kanade_h

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

class LucasKanade
{
  public:
    void drawOptFlowMap(Mat &frame, vector<Point2f> prevPts, vector<Point2f> nextPts);
    Mat calcOptFlowMap(Mat frame, int maxCorners);
  
  private:
    Mat prevImg, nextImg;
    vector<Point2f> prevPts, nextPts;
    vector<uchar> status;
    vector<float> err;
    
};

#endif /* lucas_kanade_h */