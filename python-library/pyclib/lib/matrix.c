#include "matrix.h"
#include <math.h>
#include <stdlib.h>

EXPORT double dot_product(double *a, double *b, int n) {
    double result = 0;
    for (int i = 0; i < n; i++) {
        result += a[i] * b[i];
    }
    return result;
}

EXPORT double vector_length(double *a, int n) {
    double result = 0;
    for (int i = 0; i < n; i++) {
        result += a[i] * a[i];
    }
    return sqrt(result);
}

double *mat_mult(double *A, double *B, int m, int n, int p) {
    double *C = (double *)malloc(m * p * sizeof(double));
    if (C == NULL) {
        return NULL;
    }

    for (int i = 0; i < m * p; i++) {
        C[i] = 0.0;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < n; k++) {
                C[i * p + j] += A[i * n + k] * B[k * p + j];
            }
        }
    }

    return C;  
}

void free_memory(double *ptr) {
    free(ptr);
}