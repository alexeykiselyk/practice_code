#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sodium.h>

/* Code to implement the Metropolis algorithm on a 2D array of particles */

int array_generator(long N, long arr[N][N]) {
    /* Create a N x N grid of random 1's and 0's */
    srand(time(NULL));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(rand() % 2 == 1) {
                arr[i][j] = 1;
            }
            else {
                arr[i][j] = 0;
            }
        }
    }
    return 0;
}

long energy_calc(long N, long arr[N][N]) {
    long energy = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            /* Use periodic boundery conditions */
            if(arr[i][j] == 1) {
                int down = arr[(i+1) % N][j];
                int up = arr[(i-1) % N][j];
                int left = arr[i][(j-1) % N];
                int right = arr[i][(j+1) % N];
                energy = up + down + left + right;
            }
        }
    }
    energy = energy/2;
    return energy;
}

long element_chooser(long N, long* row, long* column) {
    /* Choose random element of data matrix */
    srand(time(NULL));

    double num1 = (double)rand()/(double)RAND_MAX;
    double num2 = (double)rand()/(double)RAND_MAX;

    long i = 0;
    long j = 0;
    while(i/N > num1 || (i+1)/N < num1) {
        i++;
    }
    while(j/N > num2 || (j+1)/N < num2) {
        j++;
    }
    *row = i;
    *column = j;
    return 0;
}

double boltzmann_probability(double temperature, double energy_x, double energy_xprime) {
    /* Calculator of Boltzmann probability */
    double q = exp((energy_x - energy_xprime)/temperature);
    return q/(1+q);
}

int main() {
    long N = 10;
    long data[N][N];
    double T = 1.0;
    array_generator(N, data);

    printf("Old array:\n");
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            printf("%ld,", data[i][j]);
        }
        printf("\n");
    }

    long long end_time = 10;
    long long t;

    /* For loop over time */
    for(t = 0; t < end_time; t++) {
        
        long row1, column1;
        element_chooser(N, &row1, &column1);

        printf("Row: %ld, Column: %ld\n", row1, column1);

        long row2, column2;
        element_chooser(N, &row2, &column2);

        if(data[row1][column1] + data[row2][column2] == 1) {

            double e_x = energy_calc(N, data);

            data[row1][column1] = data[row2][column2];

            double e_xp = energy_calc(N, data);

            data[row1][column1] = data[row2][column2];

            double prob = boltzmann_probability(T, e_x, e_xp);
            // printf("Boltzmann prob: %lf\n", prob);

            srand(time(NULL));

            double num3 = (double)rand()/(double)RAND_MAX;

            if(0 < num3 && num3 < prob) {
                data[row1][column1] = data[row2][column2];
            }

        }

    }

    printf("New array:\n");
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            printf("%ld,", data[i][j]);
        }
        printf("\n");
    }

    return 0;
}