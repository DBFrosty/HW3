#include <string>
#include <vector>
#include <set>
#include <map>
#include <random>
#include <algorithm>
#include "problem.h"
#include "validate.h"
#include "test_generator.h"

TestGenerator::TestGenerator(Validate* validator) {
    validator_ = validator;
}

TestGeneratorV1::TestGeneratorV1(Validate* validator, int numProblems) 
    : TestGenerator(validator), numProblems_(numProblems) {}

std::vector<Problem*> TestGeneratorV1::generateTest(std::vector<Problem*> bank) {
    // Determine the topics covered on the test
    std::set<std::string> topics;
    for (Problem* p : bank) {
        ProblemV1* pv1 = static_cast<ProblemV1*>(p);
        topics.insert(pv1->getTopic());
    }

    // Used for random generation
    std::random_device rd;
    std::mt19937 gen(rd());
    
    
    while (true) {
        std::shuffle(bank.begin(), bank.end(), gen);
        std::vector<Problem*> testCandidate(bank.begin(), bank.begin() + numProblems_);
        if (validator_->valid(testCandidate, topics)) {
            return testCandidate;
        }
    }
}