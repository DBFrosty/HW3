#pragma once
#include <vector>
#include <functional>
#include "problem.h"

class Constraint {
  public:
    int min;
    int max;
    Constraint(int min, int max) : min(min), max(max) {}
    virtual int func(Problem* problem) = 0;
    virtual ~Constraint() = default;
};

//extendable constraints
class CAddition : public Constraint {
  public:
    CAddition(int min, int max) : Constraint(min, max) {}
    
    int func(Problem* problem) override {
      const TopicProblem* prob = dynamic_cast<const TopicProblem*>(problem);
      // now this code works for ANY problem that promises a TopicProblem interface
      if (prob->getTopic() == "addition") {
          return 1;
      }
      return 0;
    }
};

class CSubtraction : public Constraint {
  public:
    CSubtraction(int min, int max) : Constraint(min, max) {}
    
    int func(Problem* problem) override {
      const TopicProblem* prob = dynamic_cast<const TopicProblem*>(problem);
      if (prob->getTopic() == "subtraction") {
          return 1;
      }
      return 0;
    }
};

class CMultiplication : public Constraint {
  public:
    CMultiplication(int min, int max) : Constraint(min, max) {}
    
    int func(Problem* problem) override {
      const TopicProblem* prob = dynamic_cast<const TopicProblem*>(problem);
      if (prob->getTopic() == "multiplication") {
          return 1;
      }
      return 0;
    }
};

class CDivision : public Constraint {
  public:
    CDivision(int min, int max) : Constraint(min, max) {}
    
    int func(Problem* problem) override {
      const TopicProblem* prob = dynamic_cast<const TopicProblem*>(problem);
      if (prob->getTopic() == "division") {
          return 1;
      }
      return 0;
    }
};

class CDifficulty : public Constraint {
  public:
    CDifficulty(int min, int max) : Constraint(min, max) {}
    
    int func(Problem* problem) override {
        const DifficultyProblem* prob = dynamic_cast<const DifficultyProblem*>(problem);
        return prob->getDifficulty();
    } 
};
