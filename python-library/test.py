from pyclib import cmath
from time import time

#### MATRIX OPERATIONS ####
import numpy as np

# Define the matrices
a = np.array([1.0, 2.0, 3.0, 2.2, 3.4, 4.1], dtype=np.float64)
b = np.array([4.0, 5.0, 6.0, 8.4, 9.3, 10.1], dtype=np.float64)

t0 = time()
dot_product_result_c = cmath.dot_1d(a, b)
vector_length_result_c = cmath.vector_length(a)
t1 = time()

print(f"Dot product of the matrices is: {dot_product_result_c}")
print(f"Vector length of the matrix is: {vector_length_result_c}")
print(f"Time taken to perform the operation C: {t1 - t0} seconds")

# native python
t0 = time()
dot_product_result = np.dot(a, b)
vector_length_result = np.linalg.norm(a)
t1 = time()

print(f"Dot product of the matrices is: {dot_product_result}")
print(f"Vector length of the matrix is: {vector_length_result}")
print(f"Time taken to perform the operation Python: {t1 - t0} seconds")

mat1 = np.array([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]], dtype=np.float64)
mat2 = np.array([[7.0, 8.0], [9.0, 10.0], [11.0, 12.0]], dtype=np.float64)

t0 = time()
matrix_multiply_result_c = cmath.mat_mul(mat1, mat2)
t1 = time()

print(f"Matrix multiplication result is: {matrix_multiply_result_c}")
print(f"Time taken to perform the operation C: {t1 - t0} seconds")

# native python
t0 = time()
matrix_multiply_result = np.dot(mat1, mat2)
t1 = time()

print(f"Matrix multiplication result is: {matrix_multiply_result}")
print(f"Time taken to perform the operation Python: {t1 - t0} seconds")

# Assert the results
assert dot_product_result == dot_product_result_c
assert vector_length_result == vector_length_result_c
assert matrix_multiply_result.all() == matrix_multiply_result_c.all()
print("All  operations are correct")

# Test integrate

from pyclib import cintegrate

cintegrate.test_integrate()


from math import sin


def f(x):
    return x * x + 10 + sin(x) + x * x * x


trap_result_c = cintegrate.trapezoidal_rule(f, 0, 1, 1000)
simp_result_c = cintegrate.simpsons_rule(f, 0, 1, 1000)

print(f"Trapezoidal rule result: {trap_result_c}")
print(f"Simpson's rule result: {simp_result_c}")