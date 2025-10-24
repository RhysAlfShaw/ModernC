import ctypes
import numpy as np
import os
from .libctypes import lib


class cmath:
    """
    Python wrapper for the C math_operations library.
    """


    # Python wrapper function
    def dot_1d(a, b):
        """
        Wrapper for the C dot_product function.

        Args:
            a (numpy.ndarray): First array of doubles.
            b (numpy.ndarray): Second array of doubles.

        Returns:
            float: Dot product of arrays a and b.
        """
        if len(a) != len(b):
            raise ValueError("Arrays must have the same length")

        n = len(a)

        # Call the C function using ctypes
        result = lib.dot_product(
            a.ctypes.data_as(ctypes.POINTER(ctypes.c_double)),
            b.ctypes.data_as(ctypes.POINTER(ctypes.c_double)),
            ctypes.c_int(n),
        )

        return result

    def vector_length(a):
        n = len(a)
        a = a.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
        return lib.vector_length(a, ctypes.c_int(n))

    def mat_mul(a, b):

        if a.shape[1] != b.shape[0]:
            raise ValueError("Matrix A's columns must be equal to Matrix B's rows")

        # Get the dimensions of the matrices
        m, n = a.shape
        p, q = b.shape

        # Convert the matrices to 1D arrays
        a = np.ascontiguousarray(a, dtype=np.float64)
        b = np.ascontiguousarray(b, dtype=np.float64)
        c = np.zeros((m, q), dtype=np.float64)
        # Call the C function using ctypes
        c_ptr = lib.mat_mult(
            a.ctypes.data_as(ctypes.POINTER(ctypes.c_double)),
            b.ctypes.data_as(ctypes.POINTER(ctypes.c_double)),
            ctypes.c_int(m),
            ctypes.c_int(n),
            ctypes.c_int(p),
        )
        if c_ptr is not None:

            C = np.ctypeslib.as_array(c_ptr, shape=(m, q))
            lib.free_memory(c_ptr)
            return C
        else:
            return None