#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <QPointF>
#include <QString>
#include <QVector>

#define TEST_CASES_AMOUNT 3

class Algorithms {
public:
    Algorithms() = default;
    std::vector<int> merge_triplets(std::vector<int>& array1, std::vector<int>& array2, std::vector<int>& array3);
    void transform_matrix_with_min(std::vector<std::vector<int>>& matrix);

    unsigned long long get_operations_cnt() {
        return this->operations_counter;
    }

    void reset_operations_cnt() {
        this->operations_counter = 0;
    }

protected:
    unsigned long long operations_counter = 0;
};

struct BenchmarkResult {
    QVector<int> sizes;
    QVector<QVector<QPointF>> durations;
    QVector<QVector<QPointF>> operations;
    QStringList test_names = {"Положительные числа", "Отрицательные числа", "Случайные числа"};
};

void printMatrix(const std::vector<std::vector<int>>& matrix);
void simple_matrix_test_case(Algorithms *algo);
BenchmarkResult compute_matrices(Algorithms *algo);

void simple_merge_test_case(Algorithms *algo);
BenchmarkResult compute_triplets(Algorithms *algo);

#endif // ALGORITHMS_H
