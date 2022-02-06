#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double sqr(double x)
{
    return x*x;
}

double f(double t, double y)
{
    return (t-3.2)*y + 8 * t * exp(sqr(t - 3.2)/2) * cos(4*sqr(t));
}

double dfy(double t, double y)
{
    return t - 3.2;
}

//def solution(t, t0, y0):
//    C = y0 * np.exp(-(t0 - 3.2)**2/2)-np.sin(4*t0**2)
//    return np.exp((t-3.2)**2/2)*np.sin(4*t**2) + C
double* solution(double* t, double t0, double y0, int n)
{
    double C = y0 * exp(-((t0 - 3.2)*(t0 - 3.2))/2)-sin(4*t0*t0);
    double* res = (double*)malloc(sizeof(double)*n);
    for (int i = 0; i < n; i++)
    {
        res[i] = exp((t[i] - 3.2)*(t[i] - 3.2)/2)*sin(4*t[i]*t[i]) + C;
    }
    return res;
}

double* linspace(double a, double b, int n)
{
    double* x = (double*)malloc(n * sizeof(double));
    double h = (b - a) / (n - 1);
    for (int i = 0; i < n; i++)
    {
        x[i] = floor(100000000 * (a + i * h))/ 100000000;
    }
    return x;
}

double absolute(double x)
{
    if (x < 0)
    {
        return -x;
    }
    return x;
}

double* zeros(int n)
{
    double* x = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
    {
        x[i] = 0;
    }
    return x;
}

double* backwardEuler(double t0, double tn, double y0, double n)
{
    double h = absolute(tn - t0) / n;
    double* t = linspace(0, tn, n);
    double* y = zeros(n+1);
    y[0] = y0;

    for (int i = 0; i < n; i++)
    {
        double error = 1;
        double zold = y[i] + h * f(t[i], y[i]);
        int I = 0;

        // Newton-Raphson method to find the root of f(t, y) = 0
        double znew;
        while (error > 1e-10 && I < 5)
        {
            double F = y[i] + h * f(t[i], zold) - zold;
            double df = h * dfy(t[i], zold) - 1;
            znew = zold - F / df;
            error = abs(znew - zold);
            zold = znew;
            I++;
        }
        y[i+1] = znew;
    }
    return y;
}

double* RungeKutta4(double t0, double tn, double y0, double n)
{
    double h = (tn - t0) / n;
    double* t = linspace(0, tn, n+1);
    double* y = zeros(n+1);
    y[0] = y0;

    for (int i = 0; i < n; i++)
    {
        double k1 = f(t[i], y[i]);
        double k2 = f(t[i] + h/2, y[i] + h/2 * k1);
        double k3 = f(t[i] + h/2, y[i] + h/2 * k2);
        double k4 = f(t[i] + h, y[i] + h * k3);
        y[i+1] = y[i] + h/6 * (k1 + 2*k2 + 2*k3 + k4);
    }
    return y;
}

double error(double* y, double* y_exact, int n)
{
    double error = 0;
    for (int i = 0; i < n; i++)
    {
        error += sqr(y[i] - y_exact[i]);
    }
    return sqrt(error);
}

double* AdamsMoulton(double t0, double tn, double y0, double n)
{
    double h = absolute(tn - t0) / n;

    double* t = linspace(0, tn, n);
    double* y = zeros(n+1);

    double* temp = RungeKutta4(t0, tn+2*h, y0, n);

    y[0] = temp[0];
    y[1] = temp[1];
    y[2] = temp[2];
    printf("%f %f %f \n", y[0], y[1], y[2]);
    double K1 = f(t[1], y[1]);
    double K2 = f(t[0], y[0]);

    for (int i = 2; i < n; i++)
    {
        double K3 = K2;
        double K4 = K1;
        K1 = f(t[i], y[i]);
        
        double K0 = f(t[i+1], y[i+1]);
        // Adams-Moulton method
        y[i+1] = y[i] + h/24 * (9*K0 + 19 * K1 - 5 * K2 + K3);
    }

    return y;
}

int main()
{
    double n = 300;
    double t0 = 0;
    double tn = 6;
    double y0 = 0.75;
    double* t = linspace(0, tn, n);
    double* y = AdamsMoulton(t0, tn, y0, n);
    //write to file
    FILE *file = fopen("./results.txt", "w");
    double* linspace_t = linspace(0, tn, n+1);
    double* solve = solution(linspace_t, t0, y0, n);
    for (int i = 0; i < n; i++)
    {
        printf("%f %f %f \n", linspace_t[i], y[i], solve[i]);
        fprintf(file, "%f %0.15f %0.15f \n", t[i], y[i], solve[i]);
    }

    return 0;
}
