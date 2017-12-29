#include "met_num.h"

double** pderivative_x(Mat img) {
	int width = img.cols;
	int height = img.rows;
	double **res = create_matrix(height, width, double);
	for(int i = 0; i < height; i++) {
		for(int j = 1; j < width - 1; j++) {
			res[i][j] = ((double)(img.at<uchar>(i, j + 1)) - (double)(img.at<uchar>(i, j - 1))) / 2.0;
		}
		res[i][0] = (double)(img.at<uchar>(i, 0));
		res[i][width - 1] = (double)(img.at<uchar>(i, width - 1));
	}

	return res;
}

double** pderivative_y(Mat img) {
	int width = img.cols;
	int height = img.rows;
	double **res = create_matrix(height, width, double);
	for(int i = 0; i < width; i++) {
		for(int j = 1; j < height - 1; j++) {
			res[j][i] = ((double)(img.at<uchar>(j + 1, i)) - (double)(img.at<uchar>(j - 1, i))) / 2.0;
		}
		res[0][i] = (double)(img.at<uchar>(0, i));
		res[height - 1][i] = (double)(img.at<uchar>(height - 1, i));
	}

	return res;
}

double** pderivative_t(Mat img1, Mat img2) {
	int width = img1.cols;
	int height = img1.rows;
	double **res = create_matrix(height, width, double);
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			res[i][j] = ((double)(img2.at<uchar>(i, j)) - (double)(img1.at<uchar>(i, j))) / 2.0;
		}
	}

	return res;
}

void get_derivatives(Mat img1, Mat img2, double ***dx, double ***dy, double ***dt) {
	int width = img1.cols;
	int height = img1.rows;
	(*dx) = pderivative_x(img1);
	(*dy) = pderivative_y(img1);
	(*dt) = pderivative_t(img1, img2);

	Mat idx(height, width, CV_8UC1, Scalar(0));
	Mat idy(height, width, CV_8UC1, Scalar(0));
	Mat idt(height, width, CV_8UC1, Scalar(0));

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			idx.at<uchar>(i, j) = (int)fabs((*dx)[i][j]);
			idy.at<uchar>(i, j) = (int)fabs((*dy)[i][j]);
			idt.at<uchar>(i, j) = (int)fabs((*dt)[i][j]);
		}
	}

	char r1[25], r2[25], r3[25];
	sprintf(r1, "%s/dx.jpg", PATH_OUT);
	sprintf(r2, "%s/dy.jpg", PATH_OUT);
	sprintf(r3, "%s/dt.jpg", PATH_OUT);
	imwrite(r1, idx);
	imwrite(r2, idy);
	imwrite(r3, idt);
}

int check_convergence(double **vx, double **vy, double **vx1, double **vy1, int width, int height, double tol) {
	double **ex = create_matrix(height, width, double);
	double **ey = create_matrix(height, width, double);

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			ex[i][j] = vx1[i][j] - vx[i][j];
			ey[i][j] = vy1[i][j] - vy[i][j];
		}
	}

	double nx = 0.0, ny = 0.0;
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			nx += (ex[i][j] * ex[i][j]);
			ny += (ey[i][j] * ey[i][j]);
		}
	}
	nx = sqrt(nx);
	ny = sqrt(ny);

	free_matrix(ex);
	free_matrix(ey);

	printf("EV_x: %g EV_y: %g\n", nx, ny);

	if(nx < tol && ny < tol)
		return 1;
	else
		return 0;
}

void Horn_Schunck(Mat img1, Mat img2, double ***vx, double ***vy, int iter, double lambda, double tol) {
	printf("Número de iteraciones: %d\n", iter);
	printf("Tolerancia: %g\n", tol);
	int width = img1.cols;
	int height = img1.rows;

	//Obtener las derivadas parciales
	double **dx, **dy, **dt;
	get_derivatives(img1, img2, &dx, &dy, &dt);
	
	int k = 0;
	double **vx1 = create_matrix(height, width, double);
	double **vy1 = create_matrix(height, width, double);
	
	//Gauss-Seidel
	clock_t t_start = clock();
	while(k < iter) {
		printf("Iteración %d.\n", (k + 1));
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width; j++) {
				vx1[i][j] = vy1[i][j] = 0.0;
			}
		}

		for(int i = 1; i < height - 1; i++) {
			for(int j = 1; j < width - 1; j++) {
				//Obtener la vecindad de pixeles
				double vsx = 0.0, vsy = 0.0;
				int ns = 8;
				for(int c = -1; c <= 1; c++) {
					for(int h = -1; h <= 1; h++) {
						if(c == 0 && h == 0)
							continue;
						vsx += (*vx)[i + c][j + h];
						vsy += (*vy)[i + c][j + h];
					}
				}

				double numx = -dx[i][j] * dy[i][j] * (*vy)[i][j] - dt[i][j] * dx[i][j] + lambda * vsx;
				double numy = -dx[i][j] * dy[i][j] * (*vx)[i][j] - dt[i][j] * dy[i][j] + lambda * vsy;

				double denx = lambda * (double)ns + (dx[i][j] * dx[i][j]);
				double deny = lambda * (double)ns + (dy[i][j] * dy[i][j]);

				vx1[i][j] = numx / denx;
				vy1[i][j] = numy / deny;
			}
		}

		if(check_convergence((*vx), (*vy), vx1, vy1, width, height, tol)) {
			break;
		}

		for(int i = 1; i < height - 1; i++) {
			for(int j = 1; j < width - 1; j++) {
				(*vx)[i][j] = vx1[i][j];
				(*vy)[i][j] = vy1[i][j];
			}
		}

		k++;
	}
	clock_t t_end = clock();
	printf("Terminado.\n");
	printf("Tiempo transcurrido: %.2fs\n", (double)(t_end - t_start) / CLOCKS_PER_SEC);
	//Escribir en archivo
	char res_n[25];
	sprintf(res_n, "%s/resumen.txt", PATH_OUT);
	FILE *res = fopen(res_n, "w");
	fprintf(res, "Resultados de la prueba:\n\n*Algoritmo: Horn (Gauss-Seidel)\n");
	fprintf(res, "*Tamaño de la imagen: %dx%d\n", width, height);
	fprintf(res, "*Tiempo transcurrido: %.2fs", (double)(t_end - t_start) / CLOCKS_PER_SEC);
	fclose(res);

	free_matrix(dx);
	free_matrix(dy);
	free_matrix(dt);
	free_matrix(vx1);
	free_matrix(vy1);
}

void Horn_Schunck2(Mat img1, Mat img2, double ***vx, double ***vy, int iter, double lambda, double tol) {
	printf("Número de iteraciones: %d\n", iter);
	printf("Tolerancia: %g\n", tol);
	double h = 0.000005;
	int width = img1.cols;
	int height = img1.rows;

	//Obtener las derivadas parciales
	double **dx, **dy, **dt;
	get_derivatives(img1, img2, &dx, &dy, &dt);
	
	int k = 0;
	double **vx1 = create_matrix(height, width, double);
	double **vy1 = create_matrix(height, width, double);

	clock_t t_start = clock();
	while(k < iter) {
		printf("Iteración %d.\n", (k + 1));
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width; j++) {
				vx1[i][j] = vy1[i][j] = 0.0;
			}
		}

		for(int i = 1; i < height - 1; i++) {
			for(int j = 1; j < width - 1; j++) {
				//Obtener la vecindad de pixeles
				double vsx = 0.0, vsy = 0.0;
				for(int c = -1; c <= 1; c++) {
					for(int h = -1; h <= 1; h++) {
						if(c == 0 && h == 0)
							continue;
						vsx += ((*vx)[i][j] - (*vx)[i + c][j + h]);
						vsy += ((*vy)[i][j] - (*vy)[i + c][j + h]);
					}
				}
				double Ux = 0.0, Uy = 0.0;
				double pp = (dx[i][j] * (*vx)[i][j] + dy[i][j] * (*vy)[i][j] + dt[i][j]);

				Ux = 2.0 * pp * dx[i][j];
				Ux += 2.0 * lambda * vsx;

				Uy = 2.0 * pp * dy[i][j];
				Uy += 2.0 * lambda * vsy;

				vx1[i][j] = (*vx)[i][j] - (h * Ux);
				vy1[i][j] = (*vy)[i][j] - (h * Uy);
			}
		}

		if(check_convergence((*vx), (*vy), vx1, vy1, width, height, tol)) {
			break;
		}
		for(int i = 1; i < height - 1; i++) {
			for(int j = 1; j < width - 1; j++) {
				(*vx)[i][j] = vx1[i][j];
				(*vy)[i][j] = vy1[i][j];
			}
		}
		k++;
	}
	clock_t t_end = clock();
	printf("Terminado.\n");
	printf("Tiempo transcurrido: %.2fs\n", (double)(t_end - t_start) / CLOCKS_PER_SEC);
	//Escribir en archivo
	char res_n[25];
	sprintf(res_n, "%s/resumen.txt", PATH_OUT);
	FILE *res = fopen(res_n, "w");
	fprintf(res, "Resultados de la prueba:\n\n*Algoritmo: Horn (Gradiente paso fijo)\n");
	fprintf(res, "*Tamaño de la imagen: %dx%d\n", width, height);
	fprintf(res, "*Tiempo transcurrido: %.2fs", (double)(t_end - t_start) / CLOCKS_PER_SEC);
	fclose(res);

	free_matrix(dx);
	free_matrix(dy);
	free_matrix(dt);
	free_matrix(vx1);
	free_matrix(vy1);
}

void quiver(Mat img, double **vx, double **vy, int width, int height, double scale) {
	printf("Factor de escalamiento: %lf\n", scale);
	Mat bw(height, width, CV_8UC1, Scalar(0));
	double l_max = -10;

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			vx[i][j] *= scale;
			vy[i][j] *= scale;
		}
	}

	for(int y = 0; y < height; y += 10) {
		for(int x = 0; x < width; x += 10) {
			double dx = vx[y][x];
			double dy = vy[y][x];

			double l = sqrt(dx * dx + dy * dy);
			if(l > l_max)
				l_max = l;
		}
	}

	for(int y = 0; y < height; y += 10) {
		for(int x = 0; x < width; x += 10) {
			double dx = vx[y][x];
			double dy = vy[y][x];

			Point p = Point(x, y);
			double l = sqrt(dx * dx + dy * dy);
			if(l > 0) {
				double spinSize = 5.0 * l / l_max;
				Point p2 = Point(p.x + (int)(dx), p.y + (int)(dy));

				line(img, p, p2, CV_RGB(0, 255, 0), 1, CV_AA);
				line(bw, p, p2, CV_RGB(255, 255, 255), 1, CV_AA);
				double angle = atan2((double)p.y - p2.y, (double)p.x - p2.x);

				p.x = (int)(p2.x + spinSize * cos(angle + M_PI / 4.0));
            	p.y = (int)(p2.y + spinSize * sin(angle + M_PI / 4.0));
				line(img, p, p2, CV_RGB(0, 255, 0), 1, CV_AA);
				line(bw, p, p2, CV_RGB(255, 255, 255), 1, CV_AA);

				p.x = (int)(p2.x + spinSize * cos(angle - M_PI / 4.0));
            	p.y = (int)(p2.y + spinSize * sin(angle - M_PI / 4.0));
				line(img, p, p2, CV_RGB(0, 255, 0), 1, CV_AA);
				line(bw, p, p2, CV_RGB(255, 255, 255), 1, CV_AA);
			}
		}
	}

	char r1[25], r2[25];
	sprintf(r1, "%s/out.jpg", PATH_OUT);
	sprintf(r2, "%s/out_bw.jpg", PATH_OUT);
	imwrite(r1, img);
	imwrite(r2, bw);
}