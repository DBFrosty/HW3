#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "problem.h"

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

std::string ProblemV1::getQuestion() const {return question;}
std::string ProblemV1::getAnswer() const {return answer;}
std::string ProblemV1::getTopic() const {return topic;}
int ProblemV1::getDifficulty() const {return difficulty;}

ProblemV1::ProblemV1(std::string rawProblem) {//parse and construct
    std::string FORMAT = "^([\\s\\S]*)\\\\answer\\{([\\s\\S]*)\\}[\\s\\S]*\\\\topic\\{(.*)\\}[\\s\\S]*\\\\difficulty\\{(.*)\\}";
    std::regex re(FORMAT);
    std::smatch match;
    if (!std::regex_search(rawProblem, match, re) == true) {
      std::cerr << "Invalid problem: " << rawProblem;
      throw std::runtime_error("Invalid problem");
  }
  question = match.str(1);
  answer = match.str(2);
  topic = match.str(3);
  difficulty = std::stoi(match.str(4));
}
std::vector<Problem*> ProblemV1Loader::problemList(std::string filename) {//return vector of objects at LEAST of type Problem
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
      ProblemV1* problem = new ProblemV1(problemString);
      problems.push_back(problem);
  }
  return problems;
}