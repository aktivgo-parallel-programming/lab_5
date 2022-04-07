#include <iostream>
#include <omp.h>
#include <vector>

int main() {
    int N, num_threads;
    double start, end, diff;
    std::vector<std::vector<int>> matrix_1, matrix_2, res;

    std::cout << "Enter N: ";
    std::cin >> N;

    std::cout << "Enter num of threads: ";
    std::cin >> num_threads;

    for (int i = 0; i < N; ++i) {
        matrix_1.emplace_back();
        matrix_2.emplace_back();
        for (int j = 0; j < N; ++j) {
            matrix_1[i].push_back(i + 2);
            matrix_2[i].push_back(i + 3);
            std::cout << matrix_1[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    start = omp_get_wtime();


    #pragma omp parallel num_threads(num_threads)
    {
        #pragma omp for schedule(dynamic)
            for (int i = 0; i < N; ++i) {
                res.emplace_back();
                for (int j = 0; j < N; ++j) {
                    res[i].push_back(0);
                    for (int k = 0; k < N; ++k) {
                        res[i][j] += matrix_1[i][k] * matrix_2[k][j];
                    }
                }
            }
    }

    end = omp_get_wtime();
    diff = end - start;
    std::cout << diff << std::endl;

    for (const auto& row : res) {
        for (auto column : row) {
            std::cout << column << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
