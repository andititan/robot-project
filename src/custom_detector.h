#pragma once
#include <opencv2/opencv.hpp>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <memory>

enum color {red, green, blue, black};

struct Detector{
    Detector() {
        detector_logger = spdlog::basic_logger_mt("Detector logger", "logs.txt");
    }

    cv::Moments detect(cv::VideoCapture &video);
    void nextColor();
    color getColor();
private:
    color current_color = red;
    std::shared_ptr<spdlog::logger> detector_logger;
};
