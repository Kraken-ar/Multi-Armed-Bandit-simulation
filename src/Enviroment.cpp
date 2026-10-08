#include "Enviroment.hpp"
#include <iostream>

Enviroment::Enviroment(Agent* agent, std::vector<Arm*> arms) : agent(agent), arms(arms)
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


void Enviroment::fit(int it){
    ArmId armId; 
    double reward;
    std::vector<double> armsEstimatedValues;
    for (int i = 0;i<it;i++){
        armId = agent->makeAction();
        reward = arms.at(armId)->getReward();
       
        agent->updateArmData(armId,reward);
       
        rewardHistoryTracker->addReward(armId,reward);
        armsEstimatedValues = agent->getArmsEstimatedValues();
        armsEstematedHistoryTracker->addArmsEstemated(armsEstimatedValues);
      
     
        // std::cout << "--- [Iteration: " << i << "] ArmId: " << armId << " Reward: " << reward << std::endl;
    }
    
    rewardHistoryTracker->saveToFile("rewardHistory.csv");
    armsEstematedHistoryTracker->saveFile("EstematedArmsHistory");
    rewardHistoryTracker->drawLinePlot();
    armsEstematedHistoryTracker->drawLinePlot();
    
    
}