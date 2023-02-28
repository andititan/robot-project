#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>
#include "custom_robot.h"
#include "serverStarter.h"
using namespace std;
using namespace cv;

int main(){
    PythonScript ps(true);
    VideoCapture video;
    video.open(0, CAP_V4L2);
    if (!video.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    
    Robot robot;
    robot.run(video);

    return 0;
}
