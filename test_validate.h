#ifndef VALIDATE_H
#define VALIDATE_H

#include <vector>
#include <functional>
#include "problem.h"
#include "test_constraint.h"

//validator would not need specfic versions
class Validate {
  public:
    bool valid (std::vector<Problem*> test, std::vector<Constraint> constraints);
};

#endif