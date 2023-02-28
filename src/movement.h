#pragma once
#include "Client.h"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

using json = nlohmann::json;

struct Movement{
    Movement(){
        client.connect("tcp://127.0.0.1:5555");
        std::ifstream ifs("../src/values.json");
        j = json::parse(ifs);
        motorSpeed = j["motorSpeed"];
        movement_logger = spdlog::basic_logger_mt("Movement logger", "logs.txt");

    }

    int direction(const cv::Moments &m);

    void left();
    void right();
    void forward();

    void stop();
    void disconnect();
    void logger_output(std::string text);
private:
    Client client;
    MotionSpeed ms = (0.0, 0.0f);
    json j;
    float motorSpeed;
    std::shared_ptr<spdlog::logger> movement_logger;
};
