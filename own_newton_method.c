#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double x) {
    /* returns f(x) */
    return (3*x*x) - (2*x*x*x);
}

double df(double x) {
    /* returns first deriv of f(x) */
    return (6*x) - (6*x*x);
}

double ddf(double x) {
    return 6 - (12*x);
}

int newton_method(double x) {
    
    double x_0 = x;
    double x_np1;
    long iter = 0;

    if(fabs(ddf(x)) < 1e-20) {
        printf("For x0 = %.10lf there is a point of inflection present.\n", x);
        return 0;
    }

    while(fabs(df(x)) > 0.0000000001) {
        x_np1 = x - (df(x)/ddf(x));
        x = x_np1;
        iter++;
    }

    printf("For x = %.10f, stationary point found at x = %.10f in %ld iteration(s)\n", x_0, x, iter);

    return 0;
}

int main() {
    double N = 100;
    double x_low = -1.0;
    double x_high = 2.0;
    double dx = fabs((x_high - x_low)/(N-1));
    long j;

    for(j = 0; j < N; j++) {
        newton_method(x_low + j*dx);
    }

    printf("sim end");

    return 0;
} 