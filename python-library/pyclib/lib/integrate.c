#include <stdio.h>
#include "integrate.h"

double example_function(double x) {
    return x * x; 
}

int test_integrate(int n) {
    double a = 0.0;
    double b = 1.0;

    double result_trapezoidal = trapezoidal_rule(example_function, a, b, n);
    double result_simpsons = simpsons_rule(example_function, a, b, n);
    return 0;
}

double trapezoidal_rule(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }

    return sum * h;
}

double simpsons_rule(double (*f)(double), double a, double b, int n) {
    if (n % 2 != 0) {
        n++; 
    }

    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0) {
            sum += 2 * f(x);
        } else {
            sum += 4 * f(x);
        }
    }

    return sum * h / 3.0;
}