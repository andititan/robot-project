
#include <opencv2/opencv.hpp>
#include <iostream>
#pragma once

enum color {red, green, blue, black};

struct Detector{
    Detector() = default;

    cv::Moments detect(cv::VideoCapture &video);
    void nextColor();
    color getColor();
private:
    color current_color = red;
};
