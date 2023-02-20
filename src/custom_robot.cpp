#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "custom_robot.h"

using namespace std;
using namespace cv;

void Robot::run(VideoCapture &video){
    while(detector.getColor() != 3){
        if(move.direction(detector.detect(video)) == 0){
            detector.nextColor();
        }
    }
    move.stop();
    move.disconnect();
}

