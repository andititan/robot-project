#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include "custom_detector.h"
#include "movement.h"

struct Robot{
    Robot() = default;

    void run(cv::VideoCapture &video);
private:
    Detector detector;
    Movement move;
};
