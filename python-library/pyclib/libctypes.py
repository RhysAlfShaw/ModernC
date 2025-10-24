import ctypes
import os
import sys


# Add the bin directory to the system path
bin_dir = os.path.join(os.path.dirname(__file__), "bin")
sys.path.append(bin_dir)

# Load the shared library
if os.name == "posix":
    if sys.platform == "darwin":
        lib = ctypes.CDLL(
            os.path.join(bin_dir, "libmath_operations.dylib")
        )  # For macOS
    else:
        lib = ctypes.CDLL(os.path.join(bin_dir, "libmath_operations.so"))  # For Linux
elif os.name == "nt":
    lib = ctypes.CDLL(os.path.join(bin_dir, "math_operations.dll"))  # For Windows
else:
    raise OSError("Unsupported operating system")

# Define the argument and return types of the functions

lib.dot_product.argtypes = [
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
]
lib.dot_product.restype = ctypes.c_double

lib.vector_length.argtypes = [ctypes.POINTER(ctypes.c_double)]
lib.vector_length.restype = ctypes.c_double

lib.mat_mult.argtypes = [
    ctypes.POINTER(ctypes.c_double),  # A
    ctypes.POINTER(ctypes.c_double),  # B
    ctypes.c_int,  # m (rows of A)
    ctypes.c_int,  # n (columns of A / rows of B)
    ctypes.c_int,  # p (columns of B)
]

lib.mat_mult.restype = ctypes.POINTER(ctypes.c_double)  # No return value (void)

lib.trapezoidal_rule.argtypes = [
    ctypes.CFUNCTYPE(ctypes.c_double, ctypes.c_double),
    ctypes.c_double,
    ctypes.c_double,
    ctypes.c_int,
]
lib.trapezoidal_rule.restype = ctypes.c_double

lib.simpsons_rule.argtypes = [
    ctypes.CFUNCTYPE(ctypes.c_double, ctypes.c_double),
    ctypes.c_double,
    ctypes.c_double,
    ctypes.c_int,
]
lib.simpsons_rule.restype = ctypes.c_double


lib.test_integrate.argtypes = [ctypes.c_int]
lib.test_integrate.restype = None

# free the memory allocated by the C function
lib.free_memory.argtypes = [ctypes.POINTER(ctypes.c_double)]
lib.free_memory.restype = None