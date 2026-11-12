#pragma once
#include "Agent.hpp"
#include "Arm.hpp"
#include "history/RewardHistoryTracker.hpp"
#include "history/ArmsEstematedHistoryTracker.hpp"

#include <string>
#include <vector>

struct OutputPaths
{
    std::string directory = "results";
    std::string rewardHistoryFile = "rewardHistory.csv";
    std::string armsEstimateHistoryFile = "armsEstimatedHistory.csv";
};

class Enviroment
{
private:
    Agent* agent;
    std::vector<Arm*> arms;
    int steps;
    OutputPaths outputPaths;
    RewardHistoryTracker* rewardHistoryTracker;
    ArmsEstematedHistoryTracker* armsEstematedHistoryTracker;

public:
    Enviroment(Agent* agent, std::vector<Arm*> arms, int steps, const OutputPaths& outputPaths);
    ~Enviroment();
    void setAgent(Agent* agent);
    void fit();
};
