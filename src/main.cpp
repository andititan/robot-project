#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>
#include "custom_robot.h"

using namespace std;
using namespace cv;

int main(){
    VideoCapture video;
    video.open(0, CAP_V4L2);
    if (!video.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    
    custom_robot robot;
    robot.run(video);

    return 0;
}
