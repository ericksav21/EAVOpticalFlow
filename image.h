#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "structures.h"

/*
	Librería para la creación y manipulación de imágenes y puntos(pixeles).
*/

int pixel_cmp(const void *a, const void *b);

IMG* create_img(int width, int height);

IMG* create_img2(int **mat, int width, int height);

IMG* read_img(char *files_name);

void print_img(IMG *img, char *files_name);

IMG* copy_img(IMG *img);

void free_img(IMG *obj);

IMG* resize_img(IMG *img);

void draw_line(IMG *img, int x0, int y0, int x1, int y1);

#endif