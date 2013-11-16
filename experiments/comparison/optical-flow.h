#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "farneback.h"
#include "lucas-kanade.h"
#include "simpleflow.h"

#include <stdio.h>
#include <getopt.h>
#include <string.h>

using namespace std;
using namespace cv;

void farnebackFlow(VideoCapture cap, string output);
void lucasKanadeFlow(VideoCapture cap, string output);
void simpleFlow(VideoCapture cap, string output);
void help(char** argv);
void version();