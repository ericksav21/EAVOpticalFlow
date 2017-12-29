#include "memo.h"

void *create_matrix_1d(int sz, size_t type_size) {
	void *vector;
	vector = (void *)malloc(sz * type_size);
	return vector;
}

void **create_matrix_2d(int nr, int nc, size_t type_size) {
	void **mat;
	mat = (void **)malloc(nr * sizeof(void *));
	mat[0] = (void *)malloc(nr * nc * type_size);
	for(int i = 1; i < nr; i++)
		mat[i] = mat[i - 1] + nc * type_size;

	return mat;
}

void free_matrix_1d(void *v) {
	free(v);
}

void free_matrix_2d(void **m) {
	free(m[0]);
	free(m);
}