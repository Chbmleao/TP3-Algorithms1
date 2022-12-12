#include "loja.hpp"

std::vector<int> values;
std::vector<int> lis;
std::vector<int> lds;
std::vector<int> finalSequence;

int max(int x, int y) {
    if(x > y)
        return x;
    return y;
}

std::vector<int> createInvVector(int size) {
    std::vector<int> vect(size);
    int aux = 0;
    
    for (int i = size-1; i >= 0; i--) {
        std::cin >> aux;
        vect[i] = aux;
    }
    
    return vect;
}

void longestIncreasingSubsequence(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if(values[i] > values[j]) {
                lis[i] = max(lis[i], lis[j]+1);
            }
        }
    }
}

void longestDecreasingSubsequence(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if(values[i] < values[j])
                lds[i] = max(lds[i], lds[j]+1);
        }
    }
}

void readFile() {
    int numTests = 0;
    std::cin >> numTests;

    for (int i = 0; i < numTests; i++) {
        int numRolls = 0;
        std::cin >> numRolls;

        values = createInvVector(numRolls);
        lis = std::vector<int>(numRolls, 1);
        lds = std::vector<int>(numRolls, 1);
        finalSequence = std::vector<int>(numRolls, -1);

        longestIncreasingSubsequence(numRolls);
        longestDecreasingSubsequence(numRolls);

        for (int i = 0; i < numRolls; i++) {
            finalSequence[i] = lis[i] + lds[i];
        }
        
        int rollsAmount = 0;
        for (int i = 0; i < numRolls; i++) {
            if(finalSequence[i] > rollsAmount)
                rollsAmount = finalSequence[i];
        }
        
        std::cout << rollsAmount-1 << std::endl;
    }
}    