#include <iostream>
#include <vector>
#include <utility>

void readFile();
std::vector<int> createVector(int size);
std::vector<std::vector<int>> createMatrix(int rows, int colums);
int getRollsAmount();
int getRollsAmountRecursive(int rollIndex, std::pair<int, int> valuesInterval);