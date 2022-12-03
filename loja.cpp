#include "loja.hpp"

std::vector<int> values;
std::vector<std::vector<int>> DPmatrix;
int vectorSize;

std::vector<int> createVector(int size) {
    std::vector<int> vect(size);
    int aux = 0;
    
    for (int i = 0; i < size; i++) {
        std::cin >> aux;
        vect[i] = aux;
    }
    
    return vect;
}

std::vector<std::vector<int>> createMatrix(int rows, int colums) {
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(colums, -1));
    
    return matrix;
}

int getRollsAmountRecursive(int rollIndex, int totalValue, std::pair<int, int> valuesInterval) {
    if(rollIndex == vectorSize) 
        return 0;
    
    // if(DPmatrix[rollIndex][totalValue] != -1) {
    //     return DPmatrix[rollIndex][totalValue];
    // }

    std::pair<int, int> emptyInterval(-1, -1);

    // we can insert the element in the shelf or not
    int rollsWithRollIndex = -1;
    int rollsWithoutRollIndex = -1;

    // inserting the roll with rollIndex in the shelf
    // if the shelf doesnt contain rolls
    if(valuesInterval == emptyInterval) {
        rollsWithRollIndex =  getRollsAmountRecursive(
            rollIndex + 1, 
            totalValue + values[rollIndex], 
            { values[rollIndex], values[rollIndex] }
        ) + 1;
    } else {
        // if the element is greater than the shelf start
        if(values[rollIndex] > valuesInterval.first) {
            rollsWithRollIndex = getRollsAmountRecursive(
                rollIndex + 1, 
                totalValue + values[rollIndex], 
                { values[rollIndex], valuesInterval.second }
            ) + 1;
        } 
        // if the element is smaller than the shelf end
        else if(values[rollIndex] < valuesInterval.second) {
            rollsWithRollIndex = getRollsAmountRecursive(
                rollIndex + 1, 
                totalValue + values[rollIndex], 
                { valuesInterval.first, values[rollIndex] }
            ) + 1;
        } 
        // if the element is between the start and end of the shelf
        else {
            rollsWithRollIndex = -1;
        }       
    }
    
    // not inserting the roll with rollIndex in the shelf
    rollsWithoutRollIndex = getRollsAmountRecursive(
                rollIndex + 1, 
                totalValue, 
                valuesInterval
    );


    if(rollsWithRollIndex > rollsWithoutRollIndex){
        // std::cout << "[" << rollIndex << ", " << totalValue << "] ";
        // if(DPmatrix[rollIndex][totalValue] != -1) {
        //     std::cout << DPmatrix[rollIndex][totalValue] << " -> ";
        // }
        DPmatrix[rollIndex][totalValue] = rollsWithRollIndex;
        // std::cout << DPmatrix[rollIndex][totalValue] << std::endl;
        return rollsWithRollIndex;
    }
    
    // std::cout << "[" << rollIndex << ", " << totalValue << "] ";
    // if(DPmatrix[rollIndex][totalValue] != -1) {
    //     std::cout << DPmatrix[rollIndex][totalValue] << " -> ";
    // }
    DPmatrix[rollIndex][totalValue] = rollsWithoutRollIndex;
    // std::cout << DPmatrix[rollIndex][totalValue] << std::endl;
    return rollsWithoutRollIndex;

}

int getRollsAmount() {
    std::pair<int, int> emptyInterval(-1, -1);
    
    return getRollsAmountRecursive(0, 0, emptyInterval);
}

void readFile() {

    int numTests = 0;
    std::cin >> numTests;

    for (int i = 0; i < numTests; i++) {
        int numRolls = 0;
        std::cin >> numRolls;

        values = createVector(numRolls);
        vectorSize = numRolls;

        // for (int i = 0; i < numRolls; i++) {
        //     std::cout << values[i] << " ";
        // }
        // std::cout << std::endl;
        // std::cout << std::endl;

        int valuesSum = 0;

        for (int i = 0; i < numRolls; i++) {
            valuesSum += values[i];
        }
        
        DPmatrix = createMatrix(numRolls, valuesSum+1);

        int rollsAmount = getRollsAmount();

        // for (int i = 0; i < numRolls; i++) {
        //     for (int j = 0; j < valuesSum+1; j++) {
        //         if(DPmatrix[i][j] != -1)
        //             std::cout << DPmatrix[i][j] << " ";
        //     }
        //     std::cout << std::endl;
        // }

        // std::cout << std::endl;
        // std::cout << "-------------------------------------" << std::endl;

        
        std::cout << rollsAmount << std::endl;
    }
}    