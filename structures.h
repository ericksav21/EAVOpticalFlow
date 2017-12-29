#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef struct pixel {
	int i, j;
} PIXEL;

typedef struct img {
	int **mat;
	int width, height;
} IMG;

#endif