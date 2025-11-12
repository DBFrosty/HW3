#include <string>
#include <vector>
#include <set>
#include <map>
#include <random>
#include <algorithm>
#include "problem.h"
#include "test_validate.h"
#include "test_generator.h"
#include "test_algorithm.h"

TestGenerator::TestGenerator(Validate* validator, SelectionMethod* algorithm) {
    validator_ = validator;
    algorithim_ = algorithm;
}

std::vector<Problem*> TestGenerator::generateTest(std::vector<Problem*> bank, std::vector<Constraint> constraints, int numProblems) {
    //remove this v1.gettopic() specific bs

    //SWAPPABLE ALGO GO HERE
    
    while (true) {
        std::vector<Problem*> testCandidate = algorithim_->select(bank, numProblems);//select problems from bank
        if (validator_->valid(testCandidate, constraints)) {//is valid
            return testCandidate;
        }
    }
    
}