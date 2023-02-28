#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "custom_robot.h"

using namespace std;
using namespace cv;

void Robot::run(VideoCapture &video){
    robot_logger->info("Starting program");
    while(detector.getColor() != black){
        if(move.direction(detector.detect(video)) == 0){
            detector.nextColor();
        }
    }
    robot_logger->info("Ending program");
    move.stop();
    move.disconnect();
}

