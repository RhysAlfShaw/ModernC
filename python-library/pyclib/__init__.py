from .libctypes import lib
import ctypes


class cintegrate:

    def test_integrate(n):
        # test the integrate functions pure c.
        lib.test_integrate(ctypes.c_int(n))

    def trapezoidal_rule(f, a, b, n):
        # Convert the Python function to a C function pointer
        f = ctypes.CFUNCTYPE(ctypes.c_double, ctypes.c_double)(f)

        # Call the C function using ctypes
        return lib.trapezoidal_rule(f, a, b, n)

    def simpsons_rule(f, a, b, n):
        # Convert the Python function to a C function pointer
        f = ctypes.CFUNCTYPE(ctypes.c_double, ctypes.c_double)(f)
        # Call the C function using ctypes
        return lib.simpsons_rule(f, a, b, n)