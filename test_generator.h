#include <vector>
#include "problem.h"
#include "test_algorithm.h"
#include "test_validate.h"


//testGenerator would not need specfic versions
class TestGenerator {
public:
    TestGenerator(Validate* validator, SelectionMethod* algorithm);
    std::vector<Problem*> generateTest(std::vector<Problem*> bank, std::vector<Constraint> constraints, int numProblems);
private://derived classes can use protected variables
    Validate* validator_;
    SelectionMethod* algorithim_;
};

//test generator should not care about a v1 problem or whatever