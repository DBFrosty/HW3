#ifndef VALIDATE_H
#define VALIDATE_H

#include <string>
#include <vector>
#include <set>
#include <map>
#include "problem.h"

class Validate {
  public:
    virtual bool valid (std::vector<Problem*> test, std::set<std::string> topics) = 0;
    
    virtual ~Validate() = default;
};
class ValidateV1 : public Validate {
  public:
    ValidateV1(int minDifficulty, int maxDifficulty, int minTopic, int maxTopic);
    bool valid (std::vector<Problem*> test, std::set<std::string> topics) override;
  private:
    int MIN_DIFFICULTY;
    int MAX_DIFFICULTY;
    int MIN_TOPIC;
    int MAX_TOPIC;
};

#endif