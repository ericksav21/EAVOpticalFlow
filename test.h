#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

class Test {
private:
	string files_name;
	const float FLOW_TAG_FLOAT = 202021.25f;
	const char *FLOW_TAG_STRING = "PIEH";
	Mat readOpticalFlow();
public:
	Test(string files_name);
	~Test();
	void run(double **vx, double **vy, int width, int height);
};

#endif