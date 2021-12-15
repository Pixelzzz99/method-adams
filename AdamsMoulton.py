import numpy as np 
# from matplotlib import pyplot as plt
# from matplotlib.patches import Patch

def f(t, y):
    return (t-3.2)*y + 8 * t * np.exp((t-3.2)**2/2) * np.cos(4*t**2)

def dfy(t, y):
    return t-3.2 

def solution(t, t0, y0):
    C = y0 * np.exp(-(t0 - 3.2)**2/2)-np.sin(4*t0**2)
    return np.exp((t-3.2)**2/2)*np.sin(4*t**2) + C

# Backword Euler 
def BackwardEuler(t0, y0, tn, n):
    h = abs(tn-t0)/n
    t = np.linspace(0, tn, n+1)
    y = np.zeros(n+1)
    y[0] = y0

    for k in range(0, n):
        err = 1
        zold = y[k] + h * f(t[k], y[k])
        I = 0
        # Newton-Raphson
        while err > 10**(-10) and I < 5:
            F = y[k] + h * f(t[k], zold) - zold
            dF = h * dfy(t[k], zold) - 1
            znew = zold - F/dF
            err = abs(znew - zold)
            zold = znew
            I += 1
        y[k+1] = znew

    return y

# Runge-Kutta 4
def RungeKutta4(t0, y0, tn, n):
    h = abs(tn-t0)/n
    t = np.linspace(0, tn, n+1)
    y = np.zeros(n+1)
    y[0] = y0

    for i in range(0, n):
        K1 = f(t[i], y[i])
        K2 = f(t[i] + h/2, y[i] + h/2 * K1)
        K3 = f(t[i] + h/2, y[i] + h/2 * K2)
        K4 = f(t[i] + h, y[i] + h * K3)
        y[i+1] = y[i] + h/6 * (K1 + 2*K2 + 2*K3 + K4)
    return y

# AdamsMoulton corrector
def AdamsMoulton(t0, y0, tn, n):
    h = abs(tn-t0)/n
    t = np.linspace(0, tn, n+1)
    y = np.zeros(n+1)

    # Calculate RungeKutta4
    y[0:3] = RungeKutta4(t0, y0, t0+2*h, 2)
    print(y[0:3])
    K1 = f(t[1], y[1])
    K2 = f(t[0], y[0])
    for k in range(2, n):
        K3 = K2
        K2 = K1
        K1 = f(t[k], y[k])
        # y[k+1] = y[k] + h/12 * (23 * K1 - 16 * K2 + 5 * K3)
        K0 = f(t[k+1], y[k+1])
        # Adams-Moulton corrector
        # y[k+1] = y[k] + h/24 * (55 * K0 - 59 * K1 + 37 * K2 - 9 * K3)
        y[k+1] = y[k] + h/24 * (9 * K0 + 19 * K1 - 5 * K2 + K3)
    return y


def main():
    fg = 1
    n = 300
    t0 = 0 
    tn = 6
    y0 = 0.75
    t = np.linspace(0, tn, n+1)
    yb = AdamsMoulton(t0, y0, tn, n)
    for i in range(0, n+1):
        print('%.15f' % yb[i])
    # ypc = AdamsMoulton(t0, y0, tn, n)
    # plt.figure(fg)
    # plt.plot(t, yb, 'red', label='Backward Euler')
    # plt.plot(t, ypc, 'black', label='Predictor/Corrector 3/4')
    # t = np.linspace(0, tn, 401)
    # ysol = solution(t, t0, y0)
    # plt.plot(t, ysol, color="green", label='Exact')
    # plt.title('n = %d' % n)
    # plt.axis([0, tn, -60, 40])
    # plt.legend(loc='lower left')
    # plt.show()

if __name__ == '__main__':
    main()
