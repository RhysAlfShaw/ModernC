#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <omp.h>

void* thread_function(void* arg) {
    int* num = (int*)arg;
    printf("Hello from thread! Argument: %d\n", *num);
    // do some hard work here
    int sum = 0;
    for (int i = 0; i < 10000000; i++) {
        sum += i;
    }  

    printf("Goodbye from thread!\n");
    // free(num);
    return NULL;
}

void posix_threading(int N_threads) {
    pthread_t threads[N_threads];
    int thread_args[N_threads];
    for (int i = 0; i < N_threads; i++) {
        thread_args[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            exit(1);
        }
    }
    for (int i = 0; i < N_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}

void openmp_parallel_region(int N_threads) {
    // set the numeber of threads in parallel regions
    omp_set_num_threads(N_threads);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Hello from OpenMP thread %d\n", thread_id);
    }
}

int main() {
    
    // POSIX threading

    int N_threads = 4;
    printf("Starting POSIX threading with %d threads.\n", N_threads);
    posix_threading(N_threads);
    
    // OpenMP 
    N_threads = 10;
    printf("Starting OpenMP parallel region with %d threads.\n", N_threads);
    openmp_parallel_region(N_threads);


    return 0;
}