/*
    Write an OpenMP program for pi calculation.
*/

#include <stdio.h>
#include <omp.h>
int numSteps = 100000;
double step;
#define NUM_THREADS 2

int main() {
    int nThreads;
    double pi = 0.0;
    double sum[NUM_THREADS];

    step = 1.0/(double)numSteps;

    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        int id;
        int nt;
        double x;

        id = omp_get_thread_num();
        nt = omp_get_num_threads();

        if (id == 0) {
            nThreads = nt;
        }

        sum[id] = 0.0;

        for (int i = id; i < numSteps; i += nt) {
            x = (i + 0.5) * step;
            sum[id] += 4.0/(1.0 + x*x);
        }
    }

    for (int i = 0; i < nThreads; i++) {
        pi += sum[i] * step;
    }

    printf("\nThe approximate computed value of Pi computed with %d steps: %.9f\n", numSteps, pi);

    return 0;
}
