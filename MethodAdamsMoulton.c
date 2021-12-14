#include <stdio.h>
#include <stdlib.h>

double sqr(double number)
{
    return number * number;
}

double f(double x, double y)
{
    return -y + x / sqr(1.0 + x);
}

double f_prime(double x)
{
    return -1.0 + 2.0 * x / sqr(1.0 + x);
}

double* MethodEuler(double* x0, double* y0, int h, int n)
{
    double* x = x0;
    double* y = y0;
    
    for (int i = 0; i < n; i++)
    {
        x[i + 1] = x[i] + h;
        y[i + 1] = y[i] + h * f(x[i], y[i]);
    }

    return y;
}

double *MetodAdamsMoulton(double *x0, double *y0, int h, int n)
{
    double *x = x0;
    double *y = y0;

    printf("MethodMoulton \n");
    
    for (int i = 0; i < n; i++)
    {
        x[i + 1] = x[i] + h;
        y[i + 1] = y[i] + h * f(x[i], y[i]) + h * f_prime(x[i]) * (y[i + 1] - y[i]);
        printf("%f %f\n", x[i+1], y[i+1]);
    }
    
    return y;
}

int main()
{
    double x0 = 0.0;
    double y0 = 1.0;
    double h = 0.1;
    int n = 10;

    double* x = malloc(n * sizeof(double));
    double* y = malloc(n * sizeof(double));

    x[0] = x0;
    y[0] = y0;

    y = MethodEuler(x, y, h, n);
    printf("MethodEuler \n");
    for (int i = 0; i < n; i++)
    {
        printf("%f %f\n", x[i], y[i]);
    }
    
    y = MetodAdamsMoulton(x, y, h, n);


    free(x);
    free(y);

    return 0;
}
