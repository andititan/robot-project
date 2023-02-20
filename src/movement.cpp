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

void movement::left(){ 
    ms = MotionSpeed{-motorSpeed,-motorSpeed};
    client.setMotorCommand(ms);
    sleep(j["sleepTime"]);
    stop();
}

void movement::right(){
    ms = MotionSpeed{motorSpeed, motorSpeed};
    client.setMotorCommand(ms);
    sleep(j["sleepTime"]);
    stop();
}

void movement::forward(){
    ms = MotionSpeed{motorSpeed,-motorSpeed};
    client.setMotorCommand(ms);
    sleep(j["sleepTime"]);
    stop();
}

void movement::stop(){
    client.stopCommand();
}

void movement::disconnect() {
    client.disconnect();
}

int movement::direction(const Moments &m){
    //getting center of the object
    Point center(m.m10/m.m00, m.m01/m.m00);

    //m.m00 is the object`s area
    if(m.m00 == 0){
        left();
        cout << "           No object" << endl;
        return 1;
    }else if(m.m00 > j["maxArea"]){
        cout << "               Arrived next to object" << endl;
        return 0;
    }else if(abs(center.x - (640/2)) <= 90){
        cout << "               Centered" << endl;
        forward();
        return 1;
    }else if(center.x > (640/2)){
        cout << "           Object on right" << endl;
        right();
        return 1;
    }
    cout << "            Object on left" << endl;
    left();
    return 1;
}   
