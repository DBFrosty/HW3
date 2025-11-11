#include "validate.h"
#include "problem.h"
#include <vector>
#include <set>

class TestGenerator {
public:
    TestGenerator(Validate* validator);
    virtual std::vector<Problem*> generateTest(std::vector<Problem*> bank) = 0;
protected://derived classes can use protected variables
    Validate* validator_;
};

class TestGeneratorV1 : public TestGenerator {
  public:
    TestGeneratorV1(Validate* validator, int numProblems);
    std::vector<Problem*> generateTest(std::vector<Problem*> bank) override;
  private:
    int numProblems_;
};