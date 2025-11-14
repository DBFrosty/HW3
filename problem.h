#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>
#include <vector>

class Problem {//PRODUCT INTERFACE
  public:
    virtual std::string getQuestion() const = 0;
    virtual std::string getAnswer() const = 0;
    virtual ~Problem() = default;
  protected:
    std::string question;
    std::string answer;
};

class ProblemV1 : public Problem {//CONCRETE PRODUCT
  public:
    std::string getQuestion() const override;
    std::string getAnswer() const override;
    std::string getTopic() const;
    int getDifficulty() const;
    ProblemV1(std::string rawProblem);
  private:
    std::string topic;
    int difficulty;
  };
     

#endif