#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include "problem.h"

class SelectionMethod {
public:
  virtual std::vector<Problem*> select(std::vector<Problem*> bank, int numProblems, const std::vector<Constraint*>& constraints) = 0;
  virtual ~SelectionMethod() = default;
};

class RandomSelection : public SelectionMethod {
  public:
    std::vector<Problem*> select(std::vector<Problem*> bank, int numProblems, const std::vector<Constraint*>& constraints) override {
    // Used for random generation
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::shuffle(bank.begin(), bank.end(), gen);
    std::vector<Problem*> selectedProblems(bank.begin(), bank.begin() + numProblems);
    return selectedProblems;
  }
};

class FasterRandomSelection : public SelectionMethod {
  public:
    std::vector<Problem*> select(std::vector<Problem*> bank, int numProblems, const std::vector<Constraint*>& constraints) override {
    // Used for random generation
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::shuffle(bank.begin(), bank.end(), gen);
    std::vector<Problem*> selectedProblems;
    std::map<Constraint*, int> constraintSum;
    
    //init to zero
    for (Constraint* constraint : constraints) {
        constraintSum[constraint] = 0;
    }
    
    //add probs unless exceeds constraint
    for (Problem* prob : bank) {
        if (selectedProblems.size() >= numProblems) {
            break;
        }
        
        bool exceedsSum = false;
        for (Constraint* constraint : constraints) {
            int value = constraint->func(prob);
            if (constraintSum[constraint] + value > (constraint->max)) {
              //skip
                exceedsSum = true;
                break;
            }
        }
        if (!exceedsSum) {
          //add problem
            selectedProblems.push_back(prob);
            for (Constraint* constraint : constraints) {
              //add score to sum
                constraintSum[constraint] += constraint->func(prob);
            }
        }
    }
    return selectedProblems;
  }
};