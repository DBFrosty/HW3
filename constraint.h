#pragma once
#include <vector>
#include <functional>
#include <set>
#include "problem.h"

class Constraint {
  public:
    int min;
    int max;
    Constraint(int min, int max) : min(min), max(max) {}
    virtual int func(Problem* problem) = 0;
    virtual ~Constraint() = default;
};


//extendable constraints
class CTopic : public Constraint {
  private:
  std::string currTopic;
  public:
  CTopic(int min, int max, const std::string& topic) : Constraint(min, max), currTopic(topic) {}
  
  int func(Problem* problem) override {
    const TopicProblem* prob = dynamic_cast<const TopicProblem*>(problem);
    // now this code works for ANY problem that promises a TopicProblem interface
    return prob->getTopic() == currTopic ? 1 : 0;
  }
};
//scans and inserts topic constraints
//dont like this solution
inline void insertTopicConstraints(
  const std::vector<Problem*>& bank, 
  std::vector<Constraint*>& constraints, 
  int min, int max) {
    
    std::set<std::string> collectTopics;
    
    for (Problem* prob : bank) {
        if (const TopicProblem* currProb = dynamic_cast<const TopicProblem*>(prob)) {
            collectTopics.insert(currProb->getTopic());
        }
    }
    for (const std::string& topic : collectTopics) {
        constraints.push_back(new CTopic(min, max, topic));
    }
}

class CDifficulty : public Constraint {
  public:
  CDifficulty(int min, int max) : Constraint(min, max) {}
  
  int func(Problem* problem) override {
    const DifficultyProblem* prob = dynamic_cast<const DifficultyProblem*>(problem);
    return prob->getDifficulty();
  } 
};

class CLongProblem : public Constraint {
  public:
  CLongProblem(int min, int max) : Constraint(min, max) {}
  
  int func(Problem* problem) override {
    const IsLongProblem* prob = dynamic_cast<const IsLongProblem*>(problem);
    return prob->getIsLong() ? 1 : 0;
  } 
};

class CAuthor : public Constraint {
  private:
  std::string currAuthor;
  public:
  CAuthor(int min, int max, const std::string& author) : Constraint(min, max), currAuthor(author) {}
  
  int func(Problem* problem) override {
    const AuthorProblem* prob = dynamic_cast<const AuthorProblem*>(problem);
    return prob->getAuthor() == currAuthor ? 1 : 0;
  } 
  
};
//scans and inserts author constraints
inline void insertAuthorConstraints(
  const std::vector<Problem*>& bank, 
  std::vector<Constraint*>& constraints, 
  int min, int max) {
    
    std::set<std::string> collectAuthors;
    
    for (Problem* prob : bank) {
        if (const AuthorProblem* currProb = dynamic_cast<const AuthorProblem*>(prob)) {
            collectAuthors.insert(currProb->getAuthor());
        }
    }
    for (const std::string& author : collectAuthors) {
        constraints.push_back(new CAuthor(min, max, author));
    }
}