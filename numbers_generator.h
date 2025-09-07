#ifndef NUMBERS_GENERATOR_H
#define NUMBERS_GENERATOR_H

#include <vector>

std::vector<int> generate_random_numbers(int amount, int min, int max);
std::vector<std::vector<int>> generate_random_numbers(int rows, int cols, int min, int max);
std::vector<int> generate_arithmetic_progression(int n, int start, int step);
std::vector<std::vector<int>> generate_arithmetic_progression(int n, int m, int start, int step);

#endif // NUMBERS_GENERATOR_H
