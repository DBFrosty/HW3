#pragma once
#include <vector>
#include "problem.h"
#include "test_algorithm.h"
#include "validate.h"

//testGenerator would not need specfic versions
class TestGenerator {
public:
    TestGenerator(Validate* validator, SelectionMethod* algorithm) : validator(validator), algorithim(algorithm) {}
    
    std::vector<Problem*> generateTest(
      std::vector<Problem*> bank, 
      std::vector<Constraint*> constraints, 
      int numProblems) {
      //Topics must now be individually added as constraints
    
        while (true) {
          std::vector<Problem*> testCandidate = algorithim->select(bank, numProblems);//select problems from bank
          if (validator->valid(testCandidate, constraints)) {//is valid
              return testCandidate;
          }
        }
      };
private://derived classes can use protected variables
    Validate* validator;
    SelectionMethod* algorithim;
};

//test generator should not care about a v1 problem or whatever