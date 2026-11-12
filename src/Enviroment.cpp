#include "Enviroment.hpp"

#include <filesystem>

Enviroment::Enviroment(Agent* agent, std::vector<Arm*> arms, int steps, const OutputPaths& outputPaths)
    : agent(agent), arms(arms), steps(steps), outputPaths(outputPaths)
{
    this->agent->initializeArmsData(arms.size());
    this->rewardHistoryTracker = new RewardHistoryTracker();
    this->armsEstematedHistoryTracker = new ArmsEstematedHistoryTracker(arms.size());
}

Enviroment::~Enviroment()
{
    free(rewardHistoryTracker);
    free(armsEstematedHistoryTracker);
}

void Enviroment::setAgent(Agent* agent)
{
    this->agent = agent;
    this->agent->initializeArmsData(arms.size());
}

void Enviroment::fit()
{
    std::filesystem::create_directories(outputPaths.directory);

    ArmId armId;
    double reward;
    std::vector<double> armsEstimatedValues;

    for (int step = 0; step < steps; step++)
    {
        armId = agent->makeAction();
        reward = arms.at(armId)->getReward();

        agent->updateArmData(armId, reward);

        rewardHistoryTracker->addReward(armId, reward);
        armsEstimatedValues = agent->getArmsEstimatedValues();
        armsEstematedHistoryTracker->addArmsEstemated(armsEstimatedValues);
    }

    const std::filesystem::path directory = outputPaths.directory;
    rewardHistoryTracker->saveToFile((directory / outputPaths.rewardHistoryFile).string());
    armsEstematedHistoryTracker->saveFile((directory / outputPaths.armsEstimateHistoryFile).string());
    rewardHistoryTracker->drawLinePlot();
    armsEstematedHistoryTracker->drawLinePlot();
}
