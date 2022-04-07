#include <iostream>
#include <omp.h>

int main() {
    int nthreads, tid, num_threads;

    std::cout << "Enter num of threads: ";
    std::cin >> num_threads;

    // Установка количества потоков для программы
    omp_set_num_threads(num_threads);

    // Создание параллельной области
    #pragma omp parallel private(tid)
    {
        // Печать номера потока
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

        // Печать количества потоков – только master
        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    }

    return 0;
}
