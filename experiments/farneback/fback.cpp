#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>

using namespace cv;
using namespace std;

static void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step,
                    double, const Scalar& color)
{
    double l_max;

    for (int y = 0; y < cflowmap.rows; y += step)  
    {
        for (int x = 0; x < cflowmap.cols; x += step)
        {
            const Point2f& fxy = flow.at<Point2f>(y, x);
            double l = sqrt(fxy.x*fxy.x + fxy.y*+fxy.y);                                                             
            if(l>l_max) l_max = l;
        }
    }
	
	for(int y = 0; y < cflowmap.rows; y += step)
	{
        for(int x = 0; x < cflowmap.cols; x += step)
        {
			Point p = Point(x,y);
			const Point2f& fxy = flow.at<Point2f>(y, x);
            double l = sqrt(fxy.x*fxy.x + fxy.y*fxy.y);
			if (l>1.0)
			{
				double spinSize = 5.0 * l/l_max; 

				Point p2 = Point(cvRound(x+fxy.x), cvRound(y+fxy.y));
				line(cflowmap, p, p2, color, 1, CV_AA);

				double angle;                                                                          
				angle = atan2( (double) p.y - p2.y, (double) p.x - p2.x );
				
				p.x = (int) (p2.x + spinSize * cos(angle + 3.1416 / 4));
				p.y = (int) (p2.y + spinSize * sin(angle + 3.1416 / 4));
				line(cflowmap, p, p2, color, 1, CV_AA);

				p.x = (int) (p2.x + spinSize * cos(angle - 3.1416 / 4));
				p.y = (int) (p2.y + spinSize * sin(angle - 3.1416 / 4));
				line( cflowmap, p, p2, color, 1, CV_AA);
			
			}
        }
	}
}

int main(int argc, char** argv)
{
    VideoCapture cap(argv[1]);
    if( !cap.isOpened() )
        return -1;

    Mat prevgray, gray, flow, cflow, frame;
	VideoWriter vWriter;
	
	vWriter.open("flow.avi", cap.get(CV_CAP_PROP_FOURCC), 1,
				Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH),
                  (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT)));

    for(;;)
    {
		clock_t tStart = clock();
        cap >> frame;
        cvtColor(frame, gray, CV_BGR2GRAY);

        if( prevgray.data )
        {
            calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
            cvtColor(prevgray, cflow, CV_GRAY2BGR);
            drawOptFlowMap(flow, cflow, 16, 1.5, CV_RGB(0, 255, 0));
			//sprintf(filename,"flow%.2d.jpg",n++);
            //imwrite(filename,cflow);
            //cout << "Saved " << filename << endl;
			vWriter << cflow;
			printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
        }
        if(waitKey(30)>=0)
            break;
        std::swap(prevgray, gray);
    }
    return 0;
}
