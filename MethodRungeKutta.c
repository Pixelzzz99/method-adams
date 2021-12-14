#include <stdio.h>
#include <stdlib.h>

double f(double x, double y)
{
    return y;
}

double* MethodRungeKutta(double x0, double y0, double h, int n)
{
    double* x = (double*)malloc(n * sizeof(double));
    double* y = (double*)malloc(n * sizeof(double));
    x[0] = x0;
    y[0] = y0;
    for (int i = 1; i < n; i++)
    {
        x[i] = x[i - 1] + h;
        y[i] = y[i - 1] + h * f(x[i - 1], y[i - 1]);
    }
    return y;
}
