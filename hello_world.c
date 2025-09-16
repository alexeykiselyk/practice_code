#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// An application of Newton's method to find the stationary points of the function f(x) = 3x^2 - 2x^3 for scalar x. 

double df(double x) {
    // The first derivative of the original function, with input x
    return (6*x) - (6*x*x);
}

double ddf(double x) {
    // The second derivative of the original function, with input x
    return 6 - (12*x);
}

int newton(double x_0) {
    // Function which codes Newton's method, taking x_0 as input (x_0 = first value of x inserted into Newton's method)
    // Set variables x_next (next value of x)
    double x_next;
    // x_curr = x_0 (current value of x)
    double x_curr = x_0;
    // counter = 0 which counts number of iterations
    long count = 0;
    // The first application of Newton's method
    x_next = x_0 - (df(x_curr)/ddf(x_curr));
    if(fabs(ddf(x_curr)) < 1e-20) {
        printf("For x0 = %.10lf there is a point of inflection present.\n", x_0);
        return 0;
    }
    // While loop tests whether x_next and x_curr are within 10 decimal places of each other
    // Sets x_curr as the x_next calculated before, then updates x_next with another iteration, increases count by +1 for each loop 
    while(fabs(x_next - x_curr) > 0.00000000001) {
        x_curr = x_next;
        x_next = x_curr - ((df(x_curr))/(ddf(x_curr)));
        count++;
    }
    x_curr = fabs(x_curr);
    // Returns the number of iterations needed for x_0 to reach stationary point
    printf("For x0 = %.10lf stationary point found at x = %.10lf in %ld iterations.\n", x_0, x_curr, count);
    return 1;
}

int main() {
    // Defines range x is tested in
    // x_l = left-most on number line x value
    double x_l = -2.0;
    // x_r = right-most on number line x value
    double x_r = 1.0;
    // N = number of x values tested in range
    long N = 10000;
    // d_x = increment in x-value
    double d_x = fabs(x_r - x_l)/(N-1);
    // for loop runs through x-range in equally spaced steps, applying Newton's method and finding number of iterations needed at each x value
    for(long j=0; j<N; j++) {
        newton(x_l + (d_x*j));
    }
    return 0;
}