#include <vector>
#include <functional>
#include "problem.h"

class Constraint {
  public:
    int min;
    int max;
    ConstraintStrategy* strategy;//placeholder name for some func that takes problem and returns int
    Constraint(int min, int max, ConstraintStrategy* strat)
      : min(min), max(max), strategy(strat) {}
  };

class ConstraintStrategy {
  public:
    virtual int func(Problem* problem) = 0;
    virtual ~ConstraintStrategy() = default;
};
//extendable constraints
class CTopic : public ConstraintStrategy {
  public:
    CTopic(const std::string& topic) : topic(topic) {}
    int func(Problem* problem) override {
      const ProblemV1* pV1 = dynamic_cast<const ProblemV1*>(problem);
      if (pV1->getTopic() == topic) {
          return 1;
      }
      return 0;
    }
  private:
    std::string topic;
};
class CDifficulty : public ConstraintStrategy {
  public:
    int func(Problem* problem) override {
        const ProblemV1* pV1 = dynamic_cast<const ProblemV1*>(problem);//annoying af 
        return pV1->getDifficulty();
    }
};
