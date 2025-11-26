#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>
#include <vector>

// Problem interface that ONLY promises question and answer capability
class Problem {
  public:
    virtual std::string getQuestion() const = 0;
    virtual std::string getAnswer() const = 0;
    virtual ~Problem() = default;
  protected:
    std::string question;
    std::string answer;
};

// Intermediate base classes that can promise specifc capabilities
class TopicProblem {
  public:
    virtual std::string getTopic() const = 0;
    virtual ~TopicProblem() = default;
};
class DifficultyProblem {
  public:
    virtual int getDifficulty() const = 0;
    virtual ~DifficultyProblem() = default;
};
class AuthorProblem {
  public:
    virtual std::string getAuthor() const = 0;
    virtual ~AuthorProblem() = default;
};
class IsLongProblem {
  public:
    virtual bool getIsLong() const = 0;
    virtual ~IsLongProblem() = default;
};

class ProblemV1 :
  public Problem, 
  public TopicProblem, 
  public DifficultyProblem 
  {
  public:
    std::string getQuestion() const override;
    std::string getAnswer() const override;
    std::string getTopic() const override;
    int getDifficulty() const override;
    ProblemV1(std::string rawProblem);
  private:
    std::string topic;
    int difficulty;
  };
  
class ProblemV2 :
  public Problem,
  public TopicProblem,
  public AuthorProblem,
  public IsLongProblem 
  {
  public:
    std::string getQuestion() const override;
    std::string getAnswer() const override;
    std::string getTopic() const override;
    std::string getAuthor() const override;
    bool getIsLong() const override;
    ProblemV2(std::string rawProblem);
  private:
    std::string topic;
    std::string author;
    bool isLong;
};

#endif