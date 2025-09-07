#include <limits>
#include <iostream>
#include <chrono>
#include "algorithms.h"
#include "numbers_generator.h"

void Algorithms::transform_matrix_with_min(std::vector<std::vector<int>>& A)
{
    int rows = A.size();
    if (rows == 0) return;
    int cols = A[0].size();

    int min_positive = std::numeric_limits<int>::max();
    bool found_positive = false;
    operations_counter += 5; // Кол-во операций инициализации

    for (int i = 0; i < rows; ++i) {
        operations_counter += 2;

        for (int j = 0; j < cols; ++j) {
            operations_counter += 2;

            int num = A[i][j];
            operations_counter += 2;

            if (num > 0 && num < min_positive) {
                operations_counter += 4;
                min_positive = num;
                found_positive = true;
                operations_counter += 1;
            }
        }
    }

    operations_counter += 1;
    if (!found_positive) {
        return;
    }

    for (int i = 0; i < rows; ++i) {
        operations_counter += 2;

        for (int j = 0; j < cols; ++j) {
            operations_counter += 2;

            if ((j + 1) % 2 == 0 && A[i][j] % 2 == 0) {
                operations_counter += 5;
                A[i][j] = min_positive;
                operations_counter += 1;
            }
        }
    }
}

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    std::cout << "\n";
    for (const auto& row : matrix) {
        std::cout << "[";
        for (size_t i = 0; i < row.size(); i++) {
            std::cout << row[i];
            if (i < row.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }
}

void simple_matrix_test_case(Algorithms *algo) {
    std::vector<std::vector<int>> A(3, std::vector<int>(4));
    A[0] = {1, 2, 3, 4};
    A[1] = {5, 6, 7, 8};
    A[2] = {9, 10, 11, 12};
    algo->transform_matrix_with_min(A);
    printMatrix(A);
}

BenchmarkResult compute_matrices(Algorithms *algo)
{
    const std::vector<int> m = {5000, 6000, 7000, 8000, 9000, 10000};
    const std::vector<int> n = {5000, 6000, 7000, 8000, 9000, 10000};
    QVector<int> sizes(m.size(), 0);

    for (int i = 0; i < m.size(); i++) {
        sizes[i] = m[i] * n[i];
    }

    BenchmarkResult results;
    results.durations.resize(3);
    results.operations.resize(3);
    results.sizes = sizes;

    for (int i = 0; i < 3; i++) {
        results.durations[i].resize(m.size());
        results.operations[i].resize(m.size());
    }

    for (size_t i = 0; i < m.size(); i++) {
        int rows = m[i];
        int cols = n[i];

        // Тест 1: Положительная арифметическая прогрессия
        std::vector<std::vector<int>> data_pos = generate_arithmetic_progression(rows, cols, 0, 1);
        auto start = std::chrono::high_resolution_clock::now();
        algo->transform_matrix_with_min(data_pos);
        auto end = std::chrono::high_resolution_clock::now();
        results.durations[0][i] = QPointF(results.sizes[i], std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        results.operations[0][i] = QPointF(results.sizes[i], algo->get_operations_cnt());
        algo->reset_operations_cnt();

        // Тест 2: Отрицательная арифметическая прогрессия
        std::vector<std::vector<int>> data_neg = generate_arithmetic_progression(rows, cols, 0, -1);
        start = std::chrono::high_resolution_clock::now();
        algo->transform_matrix_with_min(data_neg);
        end = std::chrono::high_resolution_clock::now();
        results.durations[1][i] = QPointF(results.sizes[i], std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        results.operations[1][i] = QPointF(results.sizes[i], algo->get_operations_cnt());
        algo->reset_operations_cnt();

        // Тест 3: Случайные числа
        std::vector<std::vector<int>> data_rand = generate_random_numbers(rows, cols,
                                                             std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        start = std::chrono::high_resolution_clock::now();
        algo->transform_matrix_with_min(data_rand);
        end = std::chrono::high_resolution_clock::now();
        results.durations[2][i] = QPointF(results.sizes[i], std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        results.operations[2][i] = QPointF(results.sizes[i], algo->get_operations_cnt());
        algo->reset_operations_cnt();
    }

    return results;
}
