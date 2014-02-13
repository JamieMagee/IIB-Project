#include "optical-flow.h"

int main(int argc, char** argv)
{
 static struct option options[] =
	{
		{"help",    no_argument, NULL, 'h'},
		{"version", no_argument, NULL, 'v'},
    {"output", no_argument, NULL, 'o'},
    {"lucas-kanade", no_argument, NULL, 'l'},
    {"farneback", no_argument, NULL, 'f'},
    {"simpleflow", no_argument, NULL, 's'},
		{0, 0, 0, 0}
	};
	int option_index;
  int c = 0;
  unsigned char method = 0;
  std::string output = "";

	while (c != -1)
	{
		c = getopt_long(argc, argv, "hvo:lfs", options, &option_index);
		switch (c)
		{
      case 'h':
        help(argv);
        break;

      case 'v':
        version();
        break;
        
      case 'o':
        output = optarg;
        break;
       
      case 'l':
        method |= 0x01;
        break;

      case 'f':
        method |= 0x02;
        break;
        
      case 's':
        method |= 0x04;
        break;
        
      case '?':
        break;

      default:
        break;
		}
	}
  
  std::string input;
  if (argv[optind++]) input = argv[optind];
  
  cv::VideoCapture cap(input);
  if(!cap.isOpened())
    return -1;

  if (method & 0x01)
  {
    std::string outputlk = "";
    if (output == "")
    {
      std::string::size_type split = input.find_last_of('.');
      outputlk = input.substr(0, split)+".lucas-kanade.avi";
    }
    else
    {
      std::string::size_type split = output.find_last_of('.');
      outputlk = output.substr(0, split)+".lucas-kanade.avi";
    }
    printf("Output file %s using Lucas-Kanade optical flow\n\n", outputlk.c_str());
    lucasKanadeFlow(cap, outputlk);
  }
  if (method & 0x02)
  {
    std::string outputfb = "";
    if (output == "")
    {
      std::string::size_type split = input.find_last_of('.');
      outputfb = input.substr(0, split)+".farneback.avi";
    }
    else
    {
      std::string::size_type split = output.find_last_of('.');
      outputfb = output.substr(0, split)+".farneback.avi";
    }
    printf("Output file %s using Farneback optical flow\n\n", outputfb.c_str());
    farnebackFlow(cap, outputfb);
  }
  if (method & 0x04)
  {
    std::string outputsf = "";
    if (output == "")
    {
      std::string::size_type split = input.find_last_of('.');
      outputsf = input.substr(0, split)+".simpleflow.avi";
    }
    else
    {
      std::string::size_type split = output.find_last_of('.');
      outputsf = output.substr(0, split)+".simpleflow.avi";
    }
    printf("Output file %s using SimpleFlow optical flow\n\n", outputsf.c_str());
    simpleFlow(cap, outputsf);
  }
  
  return 0;  
}

void farnebackFlow(cv::VideoCapture cap, std::string output)
{
  Farneback *fb = new Farneback();
  cv::Mat frame;    
  
  cv::VideoWriter vWriter;
  vWriter.open(output, cap.get(CV_CAP_PROP_FOURCC), cap.get(CV_CAP_PROP_FPS),
                cv::Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH),
                     (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT)));
                     
  cap.set(CV_CAP_PROP_POS_FRAMES, 0);
  cv::FileStorage file(output+".yml", cv::FileStorage::WRITE);
  
  for (int i = 0; i < cap.get(CV_CAP_PROP_FRAME_COUNT); i++)
  {
    clock_t tStart = clock();
    cap >> frame;
    
    vWriter << fb->calcOptFlowMap(frame, file, 0.5, 3, 15, 3, 5, 1.2, 0);
    
    printf("Frame %u took %.2fs to process\n",(int)cap.get(CV_CAP_PROP_POS_FRAMES), 
           (double)(clock() - tStart)/CLOCKS_PER_SEC);
  }
  file.release();
  printf("\nProcessing complete for %s\n", output.c_str());
}

void lucasKanadeFlow(cv::VideoCapture cap, std::string output)
{
  LucasKanade *lk = new LucasKanade();
  cv::Mat frame;
  
  cv::VideoWriter vWriter;
  vWriter.open(output, cap.get(CV_CAP_PROP_FOURCC), cap.get(CV_CAP_PROP_FPS),
                cv::Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH),
                     (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT)));
  
  cap.set(CV_CAP_PROP_POS_FRAMES, 0);
  cv::FileStorage file(output+".yml", cv::FileStorage::WRITE);
  
  for (int i = 0; i < cap.get(CV_CAP_PROP_FRAME_COUNT); i++)
  {
    clock_t tStart = clock();
    cap >> frame;
    
    vWriter << lk->calcOptFlowMap(frame, file, 200000);
    
    printf("Frame %u took %.2fs to process\n",(int)cap.get(CV_CAP_PROP_POS_FRAMES), 
           (double)(clock() - tStart)/CLOCKS_PER_SEC);
  }
  printf("\nProcessing complete for %s\n", output.c_str());
}

void simpleFlow(cv::VideoCapture cap, std::string output)
{
  SimpleFlow *sf = new SimpleFlow();
  cv::Mat frame;
  
  cv::VideoWriter vWriter;
  vWriter.open(output, cap.get(CV_CAP_PROP_FOURCC), cap.get(CV_CAP_PROP_FPS),
                cv::Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH),
                     (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT)));
                     
  cap.set(CV_CAP_PROP_POS_FRAMES, 0);
  for (int i = 0; i < cap.get(CV_CAP_PROP_FRAME_COUNT); i++)
  {
    clock_t tStart = clock();
    cap >> frame;
    
    vWriter << sf->calcOptFlowMap(frame, 3, 2, 4);
    
    printf("Frame %u took %.2fs to process\n",(int)cap.get(CV_CAP_PROP_POS_FRAMES), 
           (double)(clock() - tStart)/CLOCKS_PER_SEC);
  }
  printf("\nProcessing complete for %s\n", output.c_str());
}

void help(char** argv)
{
	printf("Usage: %s [options] file...\n\n", argv[0]);
	printf("Options:\n");
  printf("  -h, --help          Display this help message\n");
  printf("  -v, --version       Display the program version\n");
  printf("  -o, --output        The file you wish to write to\n");
  printf("  -f, --farneback     Use the Farneback optical flow method\n");
  printf("  -l, --lucas-kanade  Use the Lucas-Kanade optical flow method\n");
  printf("  -s, --simpleflow    Use the Simpleflow optical flow method\n");
}


void version()
{
	printf("Version 0.0.1\n");
} 