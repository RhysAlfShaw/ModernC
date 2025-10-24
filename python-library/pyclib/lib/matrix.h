#ifndef MATRIX_H
#define MATRIX_H

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT
#endif

// dot product of two vectors
EXPORT double dot_product(double *a, double *b, int n);

// length of a vector
EXPORT double vector_length(double *a, int n);

// matrix multiplication
EXPORT double *mat_mult(double *A, double *B, int m, int n, int p);

// free memory
EXPORT void free_memory(double *ptr);

#endif // MATRIX_H