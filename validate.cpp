#include <string>
#include <vector>
#include <set>
#include <map>
#include <random>
#include "problem.h"
#include "validate.h"

ValidateV1::ValidateV1(int minDifficulty, int maxDifficulty, int minTopic, int maxTopic) {
    MIN_DIFFICULTY = minDifficulty;
    MAX_DIFFICULTY = maxDifficulty;
    MIN_TOPIC = minTopic;
    MAX_TOPIC = maxTopic;
}

bool ValidateV1::valid (std::vector<Problem*> test, std::set<std::string> topics) {
  //valid method code copied over for now
    // Initialize metrics
    int difficulty = 0;
    std::map<std::string, int> topicCounts;
    for (std::string topic : topics) {
        topicCounts[topic] = 0;
    }

    // Calculate the metrics
    for (Problem* p : test) {
        ProblemV1* pv1 = static_cast<ProblemV1*>(p);
        difficulty += pv1->getDifficulty();
        topicCounts[pv1->getTopic()] += 1;
    }

    // Check the metrics
    if (difficulty < MIN_DIFFICULTY || difficulty > MAX_DIFFICULTY) {
        return false;
    }
    for (std::string topic : topics) {
        int count = topicCounts[topic];
        if (count < MIN_TOPIC || count > MAX_TOPIC) {
            return false;
        }
    }
    return true;
}