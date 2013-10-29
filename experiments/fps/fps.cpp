#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int, char**)
{
	VideoCapture cap(0);
	if(!cap.isOpened())
		return -1;
	
    namedWindow("video", 1);
	
	Mat frame;
	
	for(;;)
    {
		cap >> frame;
		imshow("video", frame);
		cout << "FPS: " << cap.get(CV_CAP_PROP_FRAME_WIDTH) << endl;
		if(waitKey(30)>=0)
			break;
	}
	return 0;
}

