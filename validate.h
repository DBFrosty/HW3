#ifndef VALIDATE_H
#define VALIDATE_H
#pragma once
#include <string>
#include <vector>
#include <functional>
#include "problem.h"
#include "constraint.h"

//validator would not need specfic versions
class Validate {
  public:
  
  //for each constraint, sum the attrubute values for each problem and check if in range
  bool valid (std::vector<Problem*> test, std::vector<Constraint*> constraints) {
    for (Constraint* c : constraints) {
      int total = 0;
      for (Problem* p : test) {
        total += c->func(p);//call the function defined for the current constraint being evaluated
      }
      if (total < c->min || total > c->max) {
        return false;
      }
    }
  return true;
  }
};
  

#endif