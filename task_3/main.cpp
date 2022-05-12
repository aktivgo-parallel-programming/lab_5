#include <iostream>
#include <omp.h>

int main() {
    int N;
    int *arr_1, *arr_2, *res;

    std::cout << "Enter N: ";
    std::cin >> N;

    arr_1 = new int[N];
    arr_2 = new int[N];
    res = new int[N];

    //Проинициализируем созданные массивы
    for (int i = 0; i < N; ++i)
    {
        arr_1[i] = i + 1;
        arr_2[i] = i;
        res[i] = 0;
    }

    int index;

    // Создание параллельной области
    #pragma omp parallel shared(index)
    {
        //Раздадим итерации цикла последовательными порциями
        #pragma omp for schedule(static)
            for (index = 0; index < N; ++index)
                res[index] = arr_1[index] * arr_2[index];
    }

    for(int i = 0; i < N; i++) {
        std::cout << arr_1[i] << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < N; i++) {
        std::cout << arr_2[i] << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < N; i++) {
        std::cout << res[i] << " ";
    }
    std::cout << std::endl;

    delete[] arr_1;
    delete[] arr_2;
    delete[] res;

    return 0;
}
