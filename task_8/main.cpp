#include <iostream>
#include <omp.h>
#include <vector>
#include <ctime>

const int RandomLimit = 10000;
const bool Print = false;

std::vector<std::vector<int>> create_random_matrix(int);

std::vector<std::vector<int>> create_empty_matrix(int);

void print_matrix(const std::vector<std::vector<int>> &);

int main() {
    srand(time(nullptr));

    int N, num_threads;
    double start, end, diff;
    std::vector<std::vector<int>> matrix;

    std::cout << "Enter N: ";
    std::cin >> N;

    std::cout << "Enter num of threads: ";
    std::cin >> num_threads;

    matrix = create_random_matrix(N);

    if (Print) {
        print_matrix(matrix);
    }

    start = omp_get_wtime();

    std::vector<int> localMins;
    for (int i = 0; i < N; ++i) {
        localMins.push_back(0);
    }

    int localMin = INT32_MAX;
    int max = -1;

    #pragma omp parallel num_threads(num_threads)
    {
        #pragma omp for schedule(static)
            for (int i = 0; i < N; ++i) {
                localMin = INT32_MAX;
                for (int j = 0; j < N; ++j)
                    if (matrix[i][j] < localMin)
                        localMin = matrix[i][j];
                localMins[i] = localMin;
            }
        #pragma omp flush(localMins)
        #pragma omp for schedule(static)
            for (int i = 0; i < N; ++i) {
                #pragma omp critical
                    if (localMins[i] > max)
                        max = localMins[i];
            }
    }

    if (Print) {
        for (int min : localMins)
            std::cout << min << " ";
        std::cout << std::endl;
        std::cout << std::endl;
    }

    end = omp_get_wtime();
    diff = end - start;
    std::cout << diff << std::endl;
    std::cout << std::endl;

    std::cout << "max = " << max << std::endl;

    return 0;
}

std::vector<std::vector<int>> create_random_matrix(int size) {
    std::vector<std::vector<int>> matrix;

    for (int i = 0; i < size; ++i) {
        matrix.emplace_back();
        for (int j = 0; j < size; ++j) {
            matrix[i].push_back(rand() % RandomLimit);
        }
    }

    return matrix;
}

void print_matrix(const std::vector<std::vector<int>> &matrix) {
    for (const auto &row: matrix) {
        for (auto column: row) {
            std::cout << column << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
