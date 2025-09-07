#include "numbers_generator.h"
#include <random>

std::vector<int> generate_random_numbers(int amount, int min = 0, int max = 100)
{
    if (amount <= 0) {
        return {};
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);

    std::vector<int> numbers;
    numbers.reserve(amount);

    for (int i = 0; i < amount; ++i) {
        numbers.push_back(dist(gen));
    }

    return numbers;
}

std::vector<std::vector<int>> generate_random_numbers(int rows, int cols, int min = 0, int max = 100) {
    if (rows <= 0 || cols <= 0) return {};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);

    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));

    for (auto& row : matrix) {
        for (int& element : row) {
            element = dist(gen);
        }
    }

    return matrix;
}

std::vector<int> generate_arithmetic_progression(int n, int start = 0, int step = 1) {
    if (n <= 0) return {};

    std::vector<int> arr;
    arr.reserve(n);

    for (int i = 0; i < n; ++i) {
        arr.push_back(start + i * step);
    }

    return arr;
}

std::vector<std::vector<int>> generate_arithmetic_progression(int n, int m, int start = 0, int step = 1) {
    if (n <= 0 || m <= 0) return {};

    std::vector<std::vector<int>> matrix;
    matrix.reserve(n);

    for (int i = 0; i < n; ++i) {
        std::vector<int> row;
        row.reserve(m);

        for (int j = 0; j < m; ++j) {
            row.push_back(start + (i * m + j) * step);
        }

        matrix.push_back(std::move(row));
    }

    return matrix;
}
