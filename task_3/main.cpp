#include <iostream>
#include <omp.h>

int main() {
    int N;
    int *arr_1, *arr_2, *res;
    double start, end, diff;

    std::cout << "Enter N: ";
    std::cin >> N;

    arr_1 = new int[N];
    arr_2 = new int[N];
    res = new int[N];

    //Проинициализируем созданные массивы
    for (int i = 0; i < N; ++i)
    {
        arr_1[i] = 1;
        arr_2[i] = i;
        res[i] = 0;
    }

    int index;
    start = omp_get_wtime();

    // Создание параллельной области
    #pragma omp parallel shared(index)
    {
        //Раздадим итерации цикла последовательными порциями
        #pragma omp for schedule(static)
            for (index = 0; index < N; ++index)
                res[index] = arr_1[index] + arr_2[index];
    }

    end = omp_get_wtime();
    diff = end - start;
    std::cout << diff << std::endl;

    //Проверим правильность работы программы
    int err = 0;
    for (int i = 0; i < N; ++i) {
        if (res[i] != i + 1) {
            err++;
            std::cout << i << ": " << res[i];
        }
    }

    if (err) {
        std::cout << "Wrong program, num errors: " << err << std::endl;
    } else {
        std::cout << "Good" << std::endl;
    }

    delete[] arr_1;
    delete[] arr_2;
    delete[] res;

    return 0;
}
