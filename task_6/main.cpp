#include <iostream>
#include <omp.h>
#include <vector>

long largest_prime_divisor(long);

int main() {
    int N, num_threads;
    double start, end, diff;
    std::vector<long> vec;

    std::cout << "Enter N: ";
    std::cin >> N;

    std::cout << "Enter num of threads: ";
    std::cin >> num_threads;

    vec.reserve(N);
    for (int i = 0; i < N; ++i) {
        vec.push_back(i + 2);
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    start = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads)
    {
        #pragma omp for schedule(static)
            for (int i = 0; i < N; ++i)
                vec[i] = largest_prime_divisor(vec[i]);
    }

    end = omp_get_wtime();
    diff = end - start;
    std::cout << diff << std::endl;

    for (long i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}

long largest_prime_divisor(long n) {
    int maxPrime = -1;

    // Пока число четное, делим его на 2
    while (n % 2 == 0) {
        maxPrime = 2;
        n /= 2;
    }

    // Пока число делится на 3, делим его на 3
    while (n % 3 == 0) {
        maxPrime = 3;
        n /= 3;
    }

    // Проходим по натуральным числам, которые не делятся на 2 и 3
    for (int i = 5; i <= sqrt(n); i += 6) {
        // Пока число делится на i, делим его на i
        while (n % i == 0) {
            maxPrime = i;
            n /= i;
        }
        // Пока число делится на i + 2, делим его на i + 2
        while (n % (i + 2) == 0) {
            maxPrime = i + 2;
            n /= i + 2;
        }
    }

    // n - простое число больше 4
    if (n > 4)
        maxPrime = n;

    return maxPrime;
}
