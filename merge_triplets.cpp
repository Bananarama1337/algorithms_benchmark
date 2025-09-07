#include <limits>
#include <chrono>
#include <iostream>
#include "algorithms.h"
#include "numbers_generator.h"

std::vector<int> Algorithms::merge_triplets(std::vector<int>& A,
                                            std::vector<int>& B,
                                            std::vector<int>& C)
{
    int n = A.size();   operations_counter += 1;
    std::vector<int> D; operations_counter += 1;
    D.reserve(3 * n);   operations_counter += 3 * n;

    for (int i = 0; i < n; i++) {
        operations_counter += 2;
        D.push_back(A[i]); operations_counter += 2;
        D.push_back(B[i]); operations_counter += 2;
        D.push_back(C[i]); operations_counter += 2;
    }

    return D;
}

void simple_merge_test_case(Algorithms *algo) {
    std::vector<int> A = {2, 4, 8, 16};
    std::vector<int> B = {3, 9, 27, 81};
    std::vector<int> C = {5, 25, 125, 625};
    std::vector<int> D = algo->merge_triplets(A, B, C);
    std::cout << "[";
    for (int i = 0; i < D.size(); i++) {
        std::cout << D[i];
        if (i < D.size() - 1)
            std::cout << ", ";
    }
    std::cout << "]";
}

BenchmarkResult compute_triplets(Algorithms *algo)
{
    const QVector<int> sizes = {10000, 100000, 250000, 500000, 1000000, 1500000, 2000000, 3000000};
    BenchmarkResult results;
    results.durations.resize(3);
    results.operations.resize(3);
    results.sizes = sizes;

    for (int i = 0; i < 3; i++) {
        results.durations[i].resize(sizes.size());
        results.operations[i].resize(sizes.size());
    }

    for (size_t i = 0; i < sizes.size(); i++) {
        int size = sizes[i];

        // Тест 1: Положительная арифметическая прогрессия
        std::vector<int> data_pos = generate_arithmetic_progression(size, 0, 1);
        auto start = std::chrono::high_resolution_clock::now();
        algo->merge_triplets(data_pos, data_pos, data_pos);
        auto end = std::chrono::high_resolution_clock::now();
        results.durations[0][i] = QPointF(size, std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        results.operations[0][i] = QPointF(size, algo->get_operations_cnt());
        algo->reset_operations_cnt();

        // Тест 2: Отрицательная арифметическая прогрессия
        std::vector<int> data_neg = generate_arithmetic_progression(size, 0, -1);
        start = std::chrono::high_resolution_clock::now();
        algo->merge_triplets(data_neg, data_neg, data_neg);
        end = std::chrono::high_resolution_clock::now();
        results.durations[1][i] = QPointF(size, std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        results.operations[1][i] = QPointF(size, algo->get_operations_cnt());
        algo->reset_operations_cnt();

        // Тест 3: Случайные числа
        std::vector<int> data_rand = generate_random_numbers(size,
                                                             std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        start = std::chrono::high_resolution_clock::now();
        algo->merge_triplets(data_rand, data_rand, data_rand);
        end = std::chrono::high_resolution_clock::now();
        results.durations[2][i] = QPointF(size, std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        results.operations[2][i] = QPointF(size, algo->get_operations_cnt());
        algo->reset_operations_cnt();
    }

    return results;
}
