#include <iostream>
#include <omp.h>
#include <vector>

int main() {
    int N;
    std::vector<long> vec;

    std::cout << "Enter N: ";
    std::cin >> N;

    vec.reserve(N);
    for (int i = 0; i < N; ++i) {
        vec.push_back(2 * i + 1);
        //std::cout << vec[i] << " ";
    }

    //std::cout << std::endl;

    long max = INT32_MIN;
    long local_max = INT32_MIN;

    #pragma omp parallel private(local_max)
    {
        #pragma omp for schedule(dynamic, 1000)
            for (int i = 0; i < N; ++i) {
                if (local_max < vec[i]) {
                    local_max = vec[i];
                }
            }
        #pragma omp critical
            if (max < local_max) {
                max = local_max;
            }
    }

    std::cout << "Max = " << max << std::endl;

    return 0;
}
