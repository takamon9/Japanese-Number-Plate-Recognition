#ifndef __HEADER_H_INCLUDED__
#define __HEADER_H_INCLUDED__

#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;
using namespace cv;

Scalar colorNum(0, 255, 0);
Scalar colorComm(255, 255, 0);

Mat grayNP;
Mat cropNumberPlate, resizedNP, commercialPlate;
Mat original, image, gray;

string uname = "root";
string password = "taka1974";
string ip_address = "http://" + uname + ":" + password + "@169.254.174.88/mjpg/video.mjpg";

vector<Rect> commPlate;

VideoCapture capture;

CascadeClassifier commNumPlate_cascade;

struct sort_struct {
	int arrX;
	Mat numRect;

};

#endif


