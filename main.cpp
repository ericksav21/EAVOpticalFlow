#include <stdio.h>
#include <string.h>
#include <map>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "parameter.h"
#include "matriz_vector.h"
#include "met_num.h"
#include "test.h"

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
	Parameter par(argc, argv);
	if(argc < 5) {
		if(argc >= 2 && string(argv[1]) == "--help") {
			par.print_help();
			return 0;
		}
		printf("Error. Ejecute %s --help para ver la ayuda del sistema.", argv[0]);
		return 0;
	}
	map<string, string> parameters = par.process();
	char img_path1[50], img_path2[50];
	sprintf(img_path1, "%s/%s", PATH_IMG, parameters["file1"].c_str());
	sprintf(img_path2, "%s/%s", PATH_IMG, parameters["file2"].c_str());
	Mat img1 = imread(img_path1, 1);
	Mat img2 = imread(img_path2, 1);
	double lambda = stof(parameters["lambda"]);

	Mat g_img1, g_img2;
	int width = img1.cols;
	int height = img1.rows;

	cvtColor(img1, g_img1, CV_BGR2GRAY);
	cvtColor(img2, g_img2, CV_BGR2GRAY);

	Mat g1, g2;
	GaussianBlur(g_img1, g1, Size(5, 5), 0, 0);
	GaussianBlur(g_img2, g2, Size(5, 5), 0, 0);

	int algo;
	if(parameters["algo"] == "GS") algo = 0;
	else if(parameters["algo"] == "GPF") algo = 1;
	else {
		printf("Error. No se reconoce el algoritmo.\n");
		return 0;
	}
	double tol = (parameters.count("toler") ? stof(parameters["toler"]) : 0.1);
	int iter = (parameters.count("iter") ? stoi(parameters["iter"]) : 5000);
	double scale = (parameters.count("scale") ? stof(parameters["scale"]) : 1.0);

	double **vx = create_matrix(height, width, double);
	double **vy = create_matrix(height, width, double);
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			vx[i][j] = vy[i][j] = 0.0;
		}
	}
	if(!algo)
		Horn_Schunck(g1, g2, &vx, &vy, iter, lambda, tol);
	else
		Horn_Schunck2(g1, g2, &vx, &vy, iter, lambda, tol);
	quiver(img2, vx, vy, width, height, scale);

	if(parameters.count("test")) {
		char test_file[50];
		sprintf(test_file, "%s/%s", PATH_TEST, parameters["test"].c_str());
		string tf(test_file);
		Test t(tf);
		t.run(vx, vy, width, height);
	}

	free_matrix(vx);
	free_matrix(vy);

    return 0;
}