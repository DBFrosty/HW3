#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>
#include <vector>

class Problem {
public:
    std::string getQuestion();
    std::string getAnswer();
    std::string getTopic();
    int getDifficulty();
    Problem(std::string rawProblem);
    static std::vector<Problem> problemList(std::string filename);
private:
    std::string question;
    std::string answer;
    std::string topic;
    int difficulty;
};

#endif