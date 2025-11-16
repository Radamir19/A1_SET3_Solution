#ifndef SORT_TESTER_H
#define SORT_TESTER_H
#include <iostream>
#include <vector>
#include <string>


class SortTester {
public:
    // Стандартный Merge Sort
    static void mergeSort(std::vector<int>& arr, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }

    // Гибридный Merge+Insertion Sort
    static void hybridMergeSort(std::vector<int>& arr, int l, int r, int threshold = 10) {
        if (r - l + 1 <= threshold) {
            insertionSort(arr, l, r);
        } else {
            int m = l + (r - l) / 2;
            hybridMergeSort(arr, l, m, threshold);
            hybridMergeSort(arr, m + 1, r, threshold);
            merge(arr, l, m, r);
        }
    }

    // Вспомогательные функции
private:
    static void merge(std::vector<int>& arr, int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;

        std::vector<int> L(n1), R(n2);

        for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
        for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];

        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                ++i;
            } else {
                arr[k] = R[j];
                ++j;
            }
            ++k;
        }

        while (i < n1) {
            arr[k] = L[i];
            ++i;
            ++k;
        }

        while (j < n2) {
            arr[k] = R[j];
            ++j;
            ++k;
        }
    }

    static void insertionSort(std::vector<int>& arr, int l, int r) {
        for (int i = l + 1; i <= r; ++i) {
            int key = arr[i];
            int j = i - 1;

            while (j >= l && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

public:
    // Замер времени выполнения функции
    template<typename Func>
    static long long measureTime(Func&& func) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    // Проведение эксперимента для одного типа данных и одного алгоритма
    static std::vector<long long> runExperiment(
        const std::vector<int>& sizes,
        const std::string& dataType,
        std::function<void(std::vector<int>&)> sortFunc,
        ArrayGenerator& gen
    ) {
        std::vector<long long> times;
        for (int size : sizes) {
            std::vector<int> arr;
            if (dataType == "random") {
                arr = gen.generateRandom(size);
            } else if (dataType == "reverse") {
                arr = gen.generateReverseSorted(size);
            } else if (dataType == "almost_sorted") {
                arr = gen.generateAlmostSorted(size, 5); // 5 перестановок
            }

            // Копируем для повторных замеров
            std::vector<int> copy = arr;
            long long total = 0;
            const int runs = 5; // Усредняем по 5 запускам

            for (int i = 0; i < runs; ++i) {
                copy = arr; // Восстанавливаем исходный массив
                long long time = measureTime([&]() { sortFunc(copy); });
                total += time;
            }

            times.push_back(total / runs); // Среднее время
        }
        return times;
    }

    // Вывод результатов в консоль
    static void printResults(const std::vector<int>& sizes,
                             const std::vector<long long>& times,
                             const std::string& algorithmName,
                             const std::string& dataType) {
        std::cout << "\n--- Results for " << algorithmName << " on " << dataType << " data ---\n";
        std::cout << "Size\tTime (μs)\n";
        for (size_t i = 0; i < sizes.size(); ++i) {
            std::cout << sizes[i] << "\t" << times[i] << "\n";
        }
        std::cout << "\n";
    }
};

#endif
