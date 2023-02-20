#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>
#include "movement.h"

using namespace std;
using namespace cv;

int main(){
    movement move;
    move.left();
    sleep(3);
    move.stop();
    move.right();
    sleep(3);
    move.stop();
    move.forward();
    sleep(3);
    move.stop();
    move.deactivate();
    return 0;
}
