#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>
#include <vector>

class IProblem {
public:
  virtual std::string getQuestion() const = 0;
  virtual std::string getAnswer() const = 0;
  virtual ~IProblem() = default;
};


class Problem : public IProblem { //Problem class only defines the data structure and nothing else
  public:
  std::string getQuestion() const override;
  std::string getAnswer() const override;
  std::string getTopic() const;
  int getDifficulty() const;
  
  //parsing responsibility moved to loader class
  Problem(std::string question, std::string answer, std::string topic, int difficulty);
  //list moved to loader class
  private:
  std::string question;
  std::string answer;
  std::string topic;
  int difficulty;
};

class ProblemLoader {
  public:
    static Problem problemParse(std::string rawProblem);
    static std::vector<Problem> problemList(std::string filename);
};
#endif