//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/video/tracking.hpp"
//#include "opencv2/highgui/highgui.hpp"
#include "farneback.h"
#include "lucas-kanade.h"
#include "simpleflow.h"

#include <cstdio>
#include <getopt.h>
#include <string>

void farnebackFlow(cv::VideoCapture cap, std::string output);
void lucasKanadeFlow(cv::VideoCapture cap, std::string output);
void simpleFlow(cv::VideoCapture cap, std::string output);
void help(char** argv);
void version();