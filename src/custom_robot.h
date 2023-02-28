#pragma once
#include <opencv2/opencv.hpp>
#include "custom_detector.h"
#include "movement.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <memory>

struct Robot{
    Robot() {
        robot_logger = spdlog::basic_logger_mt("Robot logger", "logs.txt");
    }

    void run(cv::VideoCapture &video);
private:
    Detector detector;
    Movement move;
    std::shared_ptr<spdlog::logger> robot_logger;
};
