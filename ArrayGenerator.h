#ifndef ARRAY_GENERATOR_H
#define ARRAY_GENERATOR_H

#include <vector>
#include <random>


class ArrayGenerator {
private://
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;

public:
    ArrayGenerator(int seed = 42) : rng(seed), dist(0, 6000) {}

    // Генерация случайного массива
    std::vector<int> generateRandom(int size) {
        std::vector<int> arr(size);
        for (int& x : arr) {
            x = dist(rng);
        }
        return arr;
    }

    // Генерация обратно отсортированного массива
    std::vector<int> generateReverseSorted(int size) {
        std::vector<int> arr(size);
        for (int i = 0; i < size; ++i) {
            arr[i] = size - i;
        }
        return arr;
    }

    // Генерация "почти" отсортированного массива
    std::vector<int> generateAlmostSorted(int size, int swaps = 5) {
        std::vector<int> arr(size);
        for (int i = 0; i < size; ++i) {
            arr[i] = i;
        }
        std::uniform_int_distribution<int> swapDist(0, size - 1);
        for (int i = 0; i < swaps; ++i) {
            int i1 = swapDist(rng);
            int i2 = swapDist(rng);
            std::swap(arr[i1], arr[i2]);
        }
        return arr;
    }
};

#endif
