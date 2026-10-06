#include "Enviroment.hpp"
#include <iostream>

Enviroment::Enviroment(Agent* agent, std::vector<Arm*> arms) : agent(agent), arms(arms)
{
    this->agent->initializeArmsData(arms.size());
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
        std::cout << "--- [Iteration: " << i << "] ArmId: " << armId << " Reward: " << reward << std::endl;
    }
}