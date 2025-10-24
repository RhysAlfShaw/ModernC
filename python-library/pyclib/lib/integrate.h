#ifndef INTEGRATE_H
#define INTEGRATE_H

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT

#endif
// Function to integrate a function f(x) using the trapezoidal rule
EXPORT double trapezoidal_rule(double (*f)(double), double a, double b, int n);

// Function to integrate a function f(x) using Simpson's rule
EXPORT double simpsons_rule(double (*f)(double), double a, double b, int n);

EXPORT int test_integrate(int n);

#endif // INTEGRATE_H