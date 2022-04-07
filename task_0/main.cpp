#include <iostream>

int main() {
    #ifdef _OPENMP
        printf("OpenMP is supported! %d\n", _OPENMP);
    #else
        printf("OpenMP is not supported!\n");
    #endif

    #pragma omp parallel
    {
        std::cout << "Hello!\n";
    }

    return 0;
}
