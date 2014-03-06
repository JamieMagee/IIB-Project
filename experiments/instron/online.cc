#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <ctype.h>

void help()
{
  std::cout << "\nHot keys: \n"
          "\tESC - quit the program\n"
          "\tr - auto-initialize tracking\n"
          "\tc - delete all the points\n"
          "\tn - switch the \"night\" mode on/off\n"
          "To add/remove a feature point click it\n" << std::endl;
}

cv::Point2f point;
bool addRemovePt = false;

static void onMouse(int event, int x, int y, int /*flags*/, void* /*param*/)
{
  if(event == cv::EVENT_LBUTTONDOWN)
  {
    point = cv::Point2f((float)x, (float)y);
    addRemovePt = true;
  }
}

int main(int argc, char** argv)
{
  help();

  cv::VideoCapture cap;
  cv::TermCriteria termcrit(cv::TermCriteria::COUNT|cv::TermCriteria::EPS,20,0.03);
  cv::Size subPixWinSize(10,10), winSize(31,31);

  const int MAX_COUNT = 500;
  bool needToInit = false;
  bool nightMode = false;

  cap.open(0);

  if(!cap.isOpened())
  {
    std::cout << "Could not initialize camera...\n";
    return 0;
  }

  cv::namedWindow("Instron Demo", 1);
  cv::setMouseCallback("Instron Demo", onMouse, 0);

  cv::Mat gray, prevGray, image;
  std::vector<cv::Point2f> points[2];

  for(;;)
  {
    cv::Mat frame;
    cap >> frame;
    if(frame.empty()) break;
    
    frame.copyTo(image);
    cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    if(nightMode) image = cv::Scalar::all(0);

    if(needToInit)
    {
      // automatic initialization
      goodFeaturesToTrack(gray, points[1], MAX_COUNT, 0.01, 10, cv::Mat(), 3, 0, 0.04);
      cornerSubPix(gray, points[1], subPixWinSize, cv::Size(-1,-1), termcrit);
      addRemovePt = false;
    }
    else if(!points[0].empty())
    {
      std::vector<uchar> status;
      std::vector<float> err;
      if(prevGray.empty()) gray.copyTo(prevGray);
      
      calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize,
                           3, termcrit, 0, 0.001);
      size_t i, k;
      for(i = k = 0; i < points[1].size(); i++ )
      {
        if(addRemovePt)
        {
          if(norm(point - points[1][i]) <= 5)
          {
            addRemovePt = false;
            continue;
          }
        }

        if(!status[i]) continue;

        points[1][k++] = points[1][i];
        //circle(image, points[1][i], 3, cv::Scalar(0,255,0), -1, 8);
        cv::Point linePts[2];
        linePts[0] = cv::Point(cvRound(points[0][i].x), cvRound(points[0][i].y));
        linePts[1] = cv::Point(cvRound(points[1][i].x), cvRound(points[1][i].y));

        line(image, linePts[0], linePts[1], CV_RGB(0, 255, 0), 1, CV_AA);
        
        double angle;                                                                          
        angle = atan2((double) linePts[0].y - linePts[1].y, (double) linePts[0].x - linePts[1].x );

        linePts[0].x = (int) (linePts[1].x + cos(angle + 3.1416 / 4));
        linePts[0].y = (int) (linePts[1].y + sin(angle + 3.1416 / 4));
        line(image, linePts[0], linePts[1], CV_RGB(0, 255, 0), 1,CV_AA);

        linePts[0].x = (int) (linePts[1].x + cos(angle - 3.1416 / 4));
        linePts[0].y = (int) (linePts[1].y + sin(angle - 3.1416 / 4));
        line(image, linePts[0], linePts[1], CV_RGB(0, 255, 0), 1, CV_AA);
        
      }
      points[1].resize(k);
    }

    if(addRemovePt && points[1].size() < (size_t)MAX_COUNT)
    {
      std::vector<cv::Point2f> tmp;
      tmp.push_back(point);
      cornerSubPix(gray, tmp, winSize, cv::Size(-1,-1), termcrit);
      points[1].push_back(tmp[0]);
      addRemovePt = false;
    }

    needToInit = false;
    imshow("Instron Demo", image);

    char c = (char)cv::waitKey(10);
    if(c == 27) break;
    switch( c )
    {
      case 'r':
        needToInit = true;
        break;
      case 'c':
        points[0].clear();
        points[1].clear();
        break;
      case 'n':
        nightMode = !nightMode;
        break;
    }

    std::swap(points[1], points[0]);
    cv::swap(prevGray, gray);
  }

  return 0;
}