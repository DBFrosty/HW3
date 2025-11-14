#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "problem.h"


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