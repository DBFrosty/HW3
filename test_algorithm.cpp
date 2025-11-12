#include "test_algorithm.h"
#include <random>
#include <algorithm>

std::vector<Problem*> RandomSelection::select(std::vector<Problem*> bank, int numProblems) {
    // Used for random generation
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::shuffle(bank.begin(), bank.end(), gen);
    std::vector<Problem*> selectedProblems(bank.begin(), bank.begin() + numProblems);
    return selectedProblems;
}