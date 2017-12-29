#ifndef MEMO_H
#define MEMO_H

#include <stdlib.h>

#define create_vector(sz, type) (type *)create_matrix_1d(sz, sizeof(type))
#define create_matrix(nr, nc, type) (type **)create_matrix_2d(nr, nc, sizeof(type))
#define free_vector(v) free_matrix_1d((void *)v)
#define free_matrix(m) free_matrix_2d((void **)m)

void *create_matrix_1d(int sz, size_t type_size);

void **create_matrix_2d(int nr, int nc, size_t type_size);

void free_matrix_1d(void *v);

void free_matrix_2d(void **m);

#endif