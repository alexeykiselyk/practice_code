#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
// #include <sodium.h>

/* Code to implement the Metropolis algorithm on a 2D array of particles */

// int foo() {
//     char myString[32];
//     uint32_t myInt;
    
//     randombytes_buf(myString, 32);
//     /* myString will be an array of 32 random bytes, not null-terminated */
//     myInt = randombytes_uniform(10);
//     /* myInt will be a random number between 0 and 9 */
// }

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
    int up, down, left, right;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            /* Use periodic boundery conditions */
            if(arr[i][j] == 1) {
                down = arr[(i+1+N) % N][j];
                up = arr[(i-1+N) % N][j];
                left = arr[i][(j-1+N) % N];
                right = arr[i][(j+1+N) % N];
                energy += up + down + left + right;
                // printf("L: %d, R: %d, U: %d, D: %d\n", left, right, up, down);
                // printf("Total: %ld\n", energy);
            }
        }
    }
    energy = energy/2;
    return energy;
}

long element_chooser(long N, long* row, long* column) {
    /* Choose random element of data matrix */

    double num1 = (double)rand()/(double)RAND_MAX;
    double num2 = (double)rand()/(double)RAND_MAX;

    long i = 0;
    long j = 0;

    /* While loops */
    while((double)(i)/(double)(N) > num1 || (double)((i+1))/(double)(N) < num1) {
        i++;
    }
    while((double)(j)/(double)(N) > num2 || (double)((j+1))/(double)(N) < num2) {
        j++;
    }
    *row = i;
    *column = j;
    return 0;
}

// void swap_element(long* a, long* b) {
//     long* temp = a;
//     a = b;
//     b = temp;
// }

double boltzmann_probability(double temperature, double energy_x, double energy_xprime) {
    /* Calculator of Boltzmann probability */
    double q = exp((energy_x - energy_xprime)/temperature);
    return q/(1+q);
}

int main() {

    srand(time(NULL));

    long N = 50;
    long data[N][N];
    double T = 100.0;
    long grid_diff[N][N];
    array_generator(N, data);

    long init_data[N][N];
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            init_data[i][j] = data[i][j];
        }
    }   

    printf("Initial array:\n");
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf("%ld,", data[i][j]);
        }
        printf("\n");
    }

    long long end_time = 1000;
    long long t;

    // int matrix[3][3] = { {1, 4, 2}, {3, 6, 8}, {5, 7, 9} };

    // printf("Part of matrix: %d\n", matrix[1][2]);


    /* For loop over time */
    for(t = 0; t < end_time; t++) {
        
        long row1, column1;
        element_chooser(N, &row1, &column1);

        long row2, column2;
        element_chooser(N, &row2, &column2);

        // printf("Row1, column1: %ld, %ld\n", row1, column1);
        // printf("Row2, column2: %ld, %ld\n", row2, column2);

        long element1 = data[row1][column1];
        long element2 = data[row2][column2];

        if(element1 + element2 == 1) {

            long e_x = energy_calc(N, data);

            // printf("Energy before: %ld\n", e_x);

            /* Swap the elements directly in the data array */
            long temp = data[row1][column1];
            data[row1][column1] = data[row2][column2];
            data[row2][column2] = temp;

            long e_xp = energy_calc(N, data);

            // printf("Energy after: %ld\n", e_xp);

            // printf("Energy difference: %ld\n", e_x - e_xp);

            /* Swap the elements directly in the data array */
            temp = data[row1][column1];
            data[row1][column1] = data[row2][column2];
            data[row2][column2] = temp;

            double prob = boltzmann_probability(T, (double)e_x, (double)e_xp);
            // printf("Probability: %lf\n", prob);

            double num3 = (double)rand()/(double)RAND_MAX;

            if(0 < num3 && num3 < prob) {
                temp = data[row1][column1];
                data[row1][column1] = data[row2][column2];
                data[row2][column2] = temp;
            }

        }

    }

    printf("New array:\n");
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf("%ld,", data[i][j]);
        }
        printf("\n");
    }

    /* Comparing initial and final data grids */
    printf("Array differences:\n");
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            grid_diff[i][j] = data[i][j] - init_data[i][j];

            printf("%ld,", grid_diff[i][j]);
        }
        printf("\n");
    }


    return 0;
}