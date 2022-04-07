#include <iostream>
#include <omp.h>

void thread_process(int, int);

int main() {
    int nthreads, tid, N;

    std::cout << "Enter N: ";
    std::cin >> N;

    // Установка количества потоков для программы
    omp_set_num_threads(2);

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

        // Выполнение работы потока
        thread_process(tid, N);
    }

    return 0;
}

void thread_process(int tid, int N) {
    switch(tid) {
        case 0:
            for (int i = 0; i < N; ++i) {
                printf("Num = %d from thread %d\n", i + 1, tid);
            }
            break;
        case 1:
            for (int i = 0; i < N; ++i) {
                printf("Hello World from thread %d\n", tid);
            }
            break;
        default:
            printf("Not support more then 2 threads\n");
    }
}
