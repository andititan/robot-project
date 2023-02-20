#pragma once
#include "Client.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Movement{
    Movement(){
        client.connect("tcp://127.0.0.1:5555");
        std::ifstream ifs("../src/values.json");
        j = json::parse(ifs);
        motorSpeed = j["motorSpeed"];
    }

    int direction(const cv::Moments &m);

    void left();
    void right();
    void forward();

    void stop();
    void disconnect();
private:
    Client client;
    MotionSpeed ms = (0.0, 0.0f);
    json j;
    float motorSpeed;
};
