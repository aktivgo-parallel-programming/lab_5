#include <iostream>
#include <omp.h>
#include <vector>
#include <ctime>

const int RandomLimit = 10;
const bool Print = true;

std::vector<std::vector<int>> create_random_matrix(int);
std::vector<std::vector<int>> create_empty_matrix(int);
void print_matrix(const std::vector<std::vector<int>>&);

int main() {
    srand(time(nullptr));

    int N, num_threads;
    double start, end, diff;
    std::vector<std::vector<int>> matrix_1, matrix_2, result;

    std::cout << "Enter N: ";
    std::cin >> N;

    std::cout << "Enter num of threads: ";
    std::cin >> num_threads;

    matrix_1 = create_random_matrix(N);
    matrix_2 = create_random_matrix(N);
    result = create_empty_matrix(N);

    if (Print) {
        print_matrix(matrix_1);
        print_matrix(matrix_2);
    }

    start = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads)
    {
        #pragma omp for schedule(static)
            for (int i = 0; i < N; ++i) {
                for (int k = 0; k < N; ++k) {
                    for (int j = 0; j < N; ++j) {
                        result[i][j] += matrix_1[i][k] * matrix_2[k][j];
                    }
                }
            }
    }

    end = omp_get_wtime();
    diff = end - start;
    std::cout << diff << std::endl;
    std::cout << std::endl;

    if (Print) {
        print_matrix(result);
    }

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

std::vector<std::vector<int>> create_empty_matrix(int size) {
    std::vector<std::vector<int>> matrix;

    for (int i = 0; i < size; ++i) {
        matrix.emplace_back();
        for (int j = 0; j < size; ++j) {
            matrix[i].push_back(0);
        }
    }

    return matrix;
}

void print_matrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (auto column : row) {
            std::cout << column << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
