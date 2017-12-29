#include "matriz_vector.h"

/*---------- MATRIX ZONE ----------*/

double** get_I(int n) {
	double **I = create_matrix(n, n, double);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i == j)
				I[i][j] = 1.0;
			else
				I[i][j] = 0.0;
		}
	}

	return I;
}

double** copy_matrix(double **A, double **B, int nr, int nc) {
	for(int i = 0; i < nr; i++) {
		for (int j = 0; j < nc; j++) {
			B[i][j] = A[i][j];
		}
	}

	return B;
}

void print_matrix(double **A, int nr, int nc) {
	for(int i = 0; i < nr; i++) {
		for (int j = 0; j < nc; j++) {
			printf("%lf ", A[i][j]);
		}
		printf("\n");
	}
}

void print_matrix_i(int **A, int nr, int nc) {
	for(int i = 0; i < nr; i++) {
		for (int j = 0; j < nc; j++) {
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
}

double** transpose_matrix(double **A, double **X, int nr, int nc) {
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nr; j++) {
			X[j][i] = A[i][j];
		}
	}

	return X;
}

double** add_mat(double **A, double **B, double **X, int nr, int nc) {
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			X[i][j] = A[i][j] + B[i][j];
		}
	}

	return X;
}

int** substract_mat(int **A, int **B, int **X, int nr, int nc) {
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			X[i][j] = A[i][j] - B[i][j];
		}
	}

	return X;
}

double** scale_mat(double **A, double **X, int nr, int nc, double c) {
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			X[i][j] = A[i][j] * c;
		}
	}

	return X;
}

double* mul_mat_vector(double **A, double *v, double *x, int nr, int nc) {
	for(int i = 0; i < nr; i++) {
		double aux = 0.0;
		for(int j = 0; j < nc; j++) {
			aux += (A[i][j] * v[j]);
		}
		x[i] = aux;
	}

	return x;
}

double** mul_mat_mat(double **A, double **B, double **X, int n) {
	for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            double aux = 0;
            for(int k = 0; k < n; k++) {
                aux += (A[i][k] * B[k][j]);
            }
            X[i][j] = aux;
        }
    }

    return X;
}

double norm_inf(double **A, int nr, int nc) {
	double *x = create_vector(nr, double);
	for(int i = 0; i < nr; i++) {
		double aux = 0.0;
		for(int j = 0; j < nc; j++) {
			aux += fabs(A[i][j]);
		}
		x[i] = aux;
	}
	double res = x[0];
	for(int i = 1; i < nr; i++) {
		res = max(res, x[i]);
	}

	free_vector(x);
	return res;
}

double get_err(double **A, double *v, double vp, int nr, int nc) {
	double *aux1 = create_vector(nc, double);
	double *aux2 = create_vector(nc, double);
	double *aux3 = create_vector(nc, double);
	aux1 = mul_mat_vector(A, v, aux1, nr, nc);
	aux2 = scale_vect(v, aux2, vp, nc);
	aux3 = substract_vect(aux1, aux2, aux3, nc);
	double err = norm_p(aux3, nc, 2);

	free_vector(aux1);
	free_vector(aux2);
	free_vector(aux3);

	return err;
}

/*---------- END MATRIX ZONE ----------*/

/*---------- VECTOR ZONE ----------*/

void print_vector(double *vect, int n) {
	for(int i = 0; i < n; i++) {
		printf("%lf ", vect[i]);
	}
	printf("\n");
}

double* add_vect(double *v1, double *v2, double *x, int sz) {
	for(int i = 0; i < sz; i++) {
		x[i] = v2[i] + v1[i];
	}

	return x;
}

double* substract_vect(double *v1, double *v2, double *x, int sz) {
	for(int i = 0; i < sz; i++) {
		x[i] = v2[i] - v1[i];
	}

	return x;
}

double* scale_vect(double *x, double *v, int sz, double c) {
	for(int i = 0; i < sz; i++) {
		v[i] = c * x[i];
	}

	return v;
}

double inner_product(double *v, double *x, int sz) {
	double res = 0.0;
	for(int i = 0; i < sz; i++) {
		res += x[i] * v[i];
	}

	return res;
}

double norm_2(double *x, int sz) {
	double n = 0.0;
	for(int i = 0; i < sz; i++) {
		n += pow(x[i], 2);
	}

	return sqrt(n);
}

double norm_p(double *x, int sz, int p) {
	double res = 0.0;
	for(int i = 0; i < sz; i++) {
		res += pow(fabs(x[i]), p);
	}
	
	return pow(res, 1.0 / (double)p);
}

double* normalize(double *v, double *x, int sz) {
	double n = norm_2(v, sz);
	for(int i = 0; i < sz; i++) {
		x[i] = v[i] / n;
	}

	return x;
}

/*---------- END VECTOR ZONE ----------*/