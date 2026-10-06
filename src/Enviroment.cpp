#include "Enviroment.hpp"
#include <iostream>

Enviroment::Enviroment(Agent* agent, std::vector<Arm*> arms) : agent(agent), arms(arms)
{
    this->agent->initializeArmsData(arms.size());
    this->rewardHistoryTracker = new RewardHistoryTracker("reward_history.csv");
    this->armsEstematedHistoryTracker = new ArmsEstematedHistoryTracker(arms.size(),"arms_estimated_history.csv");
}

Enviroment::~Enviroment()
{
}


void Enviroment::fit(int it){
    ArmId armId; 
    double reward;
    for (int i = 0;i<it;i++){
        armId = agent->makeAction();
        reward = arms.at(armId)->getReward();
        agent->updateArmData(armId,reward);
        rewardHistoryTracker->addReward(i,armId,reward);
        armsEstematedHistoryTracker->addArmsEstemated(i+1,agent->getArmsEstimatedValues());
        // std::cout << "--- [Iteration: " << i << "] ArmId: " << armId << " Reward: " << reward << std::endl;
    }
    rewardHistoryTracker->saveToFile();
    armsEstematedHistoryTracker->saveFile();
}