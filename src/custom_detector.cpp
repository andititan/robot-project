#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "custom_detector.h"

using namespace std;
using namespace cv;

void Detector::logger_output(string text){
    detector_logger->info(text);
}

//getting a frame and editing it, so we can get the object from it
Moments Detector::detect(VideoCapture &video){
    //read frame and save it in "frame"
    Mat frame;
    video.read(frame);

    //our camera is rotated at 180 degrees, so we fix that 
    flip(frame, frame, -1);

    Mat frame_HSV;
    Mat full_mask;

    cvtColor(frame, frame_HSV, COLOR_BGR2HSV);

    //editing the frame to HSV
    if(current_color == red){
        Mat lower_mask;
        Mat upper_mask;
        inRange(frame_HSV, Scalar(0, 100, 100), Scalar(10, 255, 255), lower_mask);
        inRange(frame_HSV, Scalar(160, 100, 100), Scalar(179,255,255), upper_mask);
        full_mask = lower_mask + upper_mask;
    }else if(current_color == blue){
        inRange(frame_HSV, Scalar(90, 100, 100), Scalar(135, 255, 255), full_mask);
    }else{
        inRange(frame_HSV, Scalar(30, 100, 100), Scalar(75, 255, 255), full_mask);
    }

    //using morphology to make a better looking object
    morphologyEx(full_mask, full_mask, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(3, 3)));
    morphologyEx(full_mask, full_mask, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)));

    //moment detection for object
    Moments m = moments(full_mask, true);

    cout << "             Area:" << m.m00 << endl;
    return m;
}

//going trough every color, when color is set to black we end the program
void Detector::nextColor(){
    if(current_color == red){
        current_color = blue;
        logger_output("Red object found, looking for blue");
    }else if(current_color == blue){
        cout << "BLUE!!!" << endl;
        //current_color = green;
        logger_output("Blue object found, looking for green");
        //Test
        current_color = black;
    }else{
        logger_output("Green object found, done");
        current_color = black;
    }
}

color Detector::getColor(){
    return current_color;
}
