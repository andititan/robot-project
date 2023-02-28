#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "movement.h"
#include <unistd.h>  
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;
using namespace cv;

void Movement::left(){ 
    ms = MotionSpeed{-motorSpeed,-motorSpeed};
    client.setMotorCommand(ms);
    sleep(j["sleepTime"]);
    stop();
}

void Movement::right(){
    ms = MotionSpeed{motorSpeed, motorSpeed};
    client.setMotorCommand(ms);
    sleep(j["sleepTime"]);
    stop();
}

void Movement::forward(){
    ms = MotionSpeed{motorSpeed,-motorSpeed};
    client.setMotorCommand(ms);
    sleep(j["sleepTime"]);
    stop();
}

void Movement::stop(){
    client.stopCommand();
}

void Movement::disconnect() {
    client.disconnect();
}

int Movement::direction(const Moments &m){
    //getting center of the object
    Point center(m.m10/m.m00, m.m01/m.m00);

    //m.m00 is the object`s area
    if(m.m00 == 0){
        left();
        //logger_output("No object");
        return 1;
    }else if(m.m00 > j["maxArea"]){
        //logger_output("Arrived next to object");
        return 0;
    }else if(abs(center.x - (640/2)) <= 90){
        //logger_output("Centered");
        forward();
        return 1;
    }else if(center.x > (640/2)){
        //logger_output("Object on right");
        right();
        return 1;
    }
    //logger_output("Object on left");
    left();
    return 1;
}

void Movement::logger_output(string text){
    movement_logger->info(text);
}
