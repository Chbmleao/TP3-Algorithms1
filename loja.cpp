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
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(colums, 0));
    
    return matrix;
}

int getRollsAmountRecursive(int rollIndex, std::pair<int, int> valuesInterval) {
    if(rollIndex == vectorSize) 
        return 0;

    if(DPmatrix[valuesInterval.first][valuesInterval.second]) {
        return DPmatrix[valuesInterval.first][valuesInterval.second];
    }
        

    std::pair<int, int> emptyInterval(0, 0);

    // we can insert the element in the shelf or not
    int rollsWithRollIndex = 0;
    int rollsWithoutRollIndex = 0;

    // inserting the roll with rollIndex in the shelf
    // if the shelf doesnt contain rolls
    if(valuesInterval == emptyInterval) {
        rollsWithRollIndex =  getRollsAmountRecursive(
            rollIndex + 1, 
            { values[rollIndex], values[rollIndex] }
        ) + 1; 
    } else {
        // if the element is greater than the shelf start
        if(values[rollIndex] > valuesInterval.first) {
            rollsWithRollIndex = getRollsAmountRecursive(
                rollIndex + 1, 
                { values[rollIndex], valuesInterval.second }
            ) + 1;
        } 
        // if the element is smaller than the shelf end
        else if(values[rollIndex] < valuesInterval.second) {
            rollsWithRollIndex = getRollsAmountRecursive(
                rollIndex + 1, 
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
        valuesInterval
    );

    if(rollsWithRollIndex > rollsWithoutRollIndex){
        DPmatrix[valuesInterval.first][valuesInterval.second] = rollsWithRollIndex;
        return rollsWithRollIndex;
    }

    DPmatrix[valuesInterval.first][valuesInterval.second] = rollsWithoutRollIndex;
    return rollsWithoutRollIndex;
}

int getRollsAmount() {
    std::pair<int, int> emptyInterval(0, 0);
    
    return getRollsAmountRecursive(0, emptyInterval);
}

void readFile() {

    int numTests = 0;
    std::cin >> numTests;

    for (int i = 0; i < numTests; i++) {
        int numRolls = 0;
        std::cin >> numRolls;

        values = createVector(numRolls);
        vectorSize = numRolls;
        
        DPmatrix = createMatrix(numRolls+1, numRolls+1);

        int rollsAmount = getRollsAmount();

        // std::cout << "n = " << numRolls << " -> ";
        // std::cout << "chamadas recursivas: " << count;
        // std::cout << " chamadas matriz: " << count2;
        // std::cout << " atualizacao da matriz: " << count3 << std::endl;

        // for (int i = 0; i < numRolls+1; i++)
        // {
        //     for (int j = 0; j < numRolls+1; j++)
        //     {
        //         std::cout << DPmatrix[i][j] << " ";
        //     }
        //     std::cout<<std::endl;
        // }
        
        
        std::cout << rollsAmount << std::endl;
    }
}    