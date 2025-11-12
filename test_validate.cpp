#include <string>
#include <vector>
#include <set>
#include <map>
#include <random>
#include "problem.h"
#include "test_validate.h"


bool Validate::valid (std::vector<Problem*> test, std::vector<Constraint> constraints) {
  for (Constraint c : constraints) {
    int total = 0;
    for (Problem* p : test) {
      total += c.strategy->func(p);//call the function defined for the current constraint being evaluated
    }
    if (total < c.min || total > c.max) {
      return false;
    }
  }
  return true;
}