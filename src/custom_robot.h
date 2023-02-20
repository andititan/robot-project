#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include "custom_detector.h"
#include "movement.h"

struct custom_robot{
    custom_robot() = default;

    void run(cv::VideoCapture &video);
private:
    custom_detector detector;
    movement move;
};
