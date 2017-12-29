#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>
#include <time.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "structures.h"
#include "memo.h"
#include "matriz_vector.h"
#include "image.h"

#define PATH_IMG "images"
#define PATH_OUT "out"
#define PATH_TEST "test"

using namespace cv;

double** pderivative_x(Mat img);

double** pderivative_y(Mat img);

double** pderivative_t(Mat img1, Mat img2);

void get_derivatives(Mat img1, Mat img2, double ***dx, double ***dy, double ***dt);

int check_convergence(double **vx, double **vy, double **vx1, double **vy1, int width, int height, double tol);

void Horn_Schunck(Mat img1, Mat img2, double ***vx, double ***vy, int iter, double lambda, double tol);

void Horn_Schunck2(Mat img1, Mat img2, double ***vx, double ***vy, int iter, double lambda, double tol);

void quiver(Mat img, double **vx, double **vy, int width, int height, double scale);

#endif