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
      const ProblemV1* pV1 = dynamic_cast<const ProblemV1*>(problem);
      if (pV1->getTopic() == "addition") {
          return 1;
      }
      return 0;
    }
};

class CSubtraction : public Constraint {
  public:
    CSubtraction(int min, int max) : Constraint(min, max) {}
    
    int func(Problem* problem) override {
      const ProblemV1* pV1 = dynamic_cast<const ProblemV1*>(problem);
      if (pV1->getTopic() == "subtraction") {
          return 1;
      }
      return 0;
    }
};

class CMultiplication : public Constraint {
  public:
    CMultiplication(int min, int max) : Constraint(min, max) {}
    
    int func(Problem* problem) override {
      const ProblemV1* pV1 = dynamic_cast<const ProblemV1*>(problem);
      if (pV1->getTopic() == "multiplication") {
          return 1;
      }
      return 0;
    }
};

class CDivision : public Constraint {
  public:
    CDivision(int min, int max) : Constraint(min, max) {}
    
    int func(Problem* problem) override {
      const ProblemV1* pV1 = dynamic_cast<const ProblemV1*>(problem);
      if (pV1->getTopic() == "division") {
          return 1;
      }
      return 0;
    }
};

class CDifficulty : public Constraint {
  public:
    CDifficulty(int min, int max) : Constraint(min, max) {}
    
    int func(Problem* problem) override {
        const ProblemV1* pV1 = dynamic_cast<const ProblemV1*>(problem);
        return pV1->getDifficulty();
    } 
};
