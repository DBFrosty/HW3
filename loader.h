#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "problem.h"

//HELPER FUNCTION
// Split the string <s> at every occurence of the delimiter <del>.
std::vector<std::string> split(std::string s, std::string del) {
  std::vector<std::string> v;
  int start = 0;
  for (int end = s.find(del, start); end != std::string::npos; end = s.find(del, start)) {
      v.push_back(s.substr(start, end - start));
      start = end + del.size();
  }
  v.push_back(s.substr(start));
  return v;
}

class ProblemLoader {//CREATOR
  public:
  virtual Problem* createProblem(std::string rawProblem) = 0;
  std::vector<Problem*> problemList(std::string filename) {//return vector of objects at LEAST of type Problem
    // Read problems from file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening the problem list" << std::endl;
        throw std::runtime_error("Cannot open problem list");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string str = buffer.str();

    // Split into individual problems, throw out header at beginning
    std::vector<std::string> problemStrings = split(str, "\\item");
    problemStrings.erase(problemStrings.begin());

    // Convert strings to Problems
    std::vector<Problem*> problems = {};
    for (std::string problemString : problemStrings) {
        Problem* problem = createProblem(problemString);
        problems.push_back(problem);
    }
    return problems;
  }
};

class ProblemV1Loader : public ProblemLoader {
  public://actual use of factory method
  Problem* createProblem(std::string rawProblem) override {
      return new ProblemV1(rawProblem);
  }
};

class ProblemV2Loader : public ProblemLoader {
  public:
  Problem* createProblem(std::string rawProblem) override {
      return new ProblemV2(rawProblem);
  }
};