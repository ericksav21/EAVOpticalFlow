#ifndef MATRIZ_VECTOR_H
#define MATRIZ_VECTOR_H

#include <stdio.h>
#include <math.h>

#include "memo.h"

/*
	Esta librería contiene muchas operaciones básicas que
	se realizan con matrices y vectores 
*/ 

#define max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

/*---------- MATRIX ZONE ----------*/

/* Crea una matriz identidad */
double** get_I(int n);

/* Hace una copia de la matriz A en la matriz B ya inicializada */
double** copy_matrix(double **A, double **B, int nr, int nc);

/* Imprime una matriz en consola */
void print_matrix(double **A, int nr, int nc);

/* Imprime una matriz de enteros en consola */
void print_matrix_i(int **A, int nr, int nc);

/* Transpone la matriz A y la guarda en la matriz X */
double** transpose_matrix(double **A, double **X, int nr, int nc);

/* Suma dos matrices y guarda el resultado en X */
double** add_mat(double **A, double **B, double **X, int nr, int nc);

/* Resta dos matrices y guarda el resultado en X */
int** substract_mat(int **A, int **B, int **X, int nr, int nc);

/* Realiza el producto c*A donde c es un escalar y guarda el resultado
   en X */
double** scale_mat(double **A, double **X, int nr, int nc, double c);

/* Realiza el producto Av donde v es un vector y guarda el resultado
   en x*/
double* mul_mat_vector(double **A, double *v, double *x, int nr, int nc);

/* Realiza la multiplicación de dos matrices cuadradas */
double** mul_mat_mat(double **A, double **B, double **X, int n);

/* Calcula la norma infinito de una matriz */
double norm_inf(double **A, int nr, int nc);

/* Calcula el error generado en el sistema Ax = b */
double get_err(double **A, double *v, double vp, int nr, int nc);

/*---------- END MATRIX ZONE ----------*/

/*---------- VECTOR ZONE ----------*/

/* Imprime un vector en consola */
void print_vector(double *vect, int n);

/* Realiza la suma de dos vectores y guarda el resultado en x */
double* add_vect(double *v1, double *v2, double *x, int sz);

/* Realiza la resta de dos vectores y guarda el resultado en x */
double* substract_vect(double *v1, double *v2, double *x, int sz);

/* Realiza el producto c*x donde c es un escalar y guarda el resultado
   en v */
double* scale_vect(double *x, double *v, int sz, double c);

/* Calcula el producto punto entre dos vectores */
double inner_product(double *v, double *x, int sz);

/* Calcula la norma 2 de un vector */
double norm_2(double *x, int sz);

/* Calcula la norma p de un vector donde p es un número
   mayor o igual que 1 */
double norm_p(double *x, int sz, int p);

/* Normaliza el vector v usando la norma 2 y guarda el resultado en x */
double* normalize(double *v, double *x, int sz);

/*---------- END VECTOR ZONE ----------*/

#endif