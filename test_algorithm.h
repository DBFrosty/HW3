#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include "problem.h"

class SelectionMethod {
public:
  virtual std::vector<Problem*> select(std::vector<Problem*> bank, int numProblems) = 0;
  virtual ~SelectionMethod() = default;
};

class RandomSelection : public SelectionMethod {
  public:
    std::vector<Problem*> select(std::vector<Problem*> bank, int numProblems) override {
    // Used for random generation
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::shuffle(bank.begin(), bank.end(), gen);
    std::vector<Problem*> selectedProblems(bank.begin(), bank.begin() + numProblems);
    return selectedProblems;
  }
};

//class OtherSelectionMethods : public SelectionMethod...