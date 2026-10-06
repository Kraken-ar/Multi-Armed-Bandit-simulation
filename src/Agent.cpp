#include "Agent.hpp"
Agent::Agent(double epslon, double alpha) : epslon(epslon), alpha(alpha)
{
  
}


Agent::~Agent()
{
}

void Agent::initializeArmsData(int numberOfArms)
{
    for (int i = 0; i < numberOfArms; i++)
    {
        ArmData armData;
        armData.armId = i;
        armData.lastEstimatedValue = 0;
        armData.timesPlayed = 0;
        armsData.push_back(armData);
    }
}

double Agent::generateRandomNumber(double min, double max)
{
   
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}
int Agent::generateRandomArmId()
{
   
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, armsData.size() - 1);
    return dis(gen);
}
ArmId Agent::makeAction()
{
    if (generateRandomNumber() < epslon)
    {
       return generateRandomArmId(); 
    }
    ArmId BiggestRewardArmId = 0;
    for(ArmId i = 1; i < armsData.size(); i++)
    {
        if (armsData.at(i).lastEstimatedValue > armsData.at(BiggestRewardArmId).lastEstimatedValue)
        {
            BiggestRewardArmId = i;
        }
    }
    return BiggestRewardArmId;
    
}


void Agent::updateArmData(ArmId armId, double reward)
{
    ArmData& arm = armsData.at(armId);

    arm.timesPlayed++;
    arm.lastEstimatedValue = arm.lastEstimatedValue + (alpha*(reward - arm.lastEstimatedValue));

    
}
std::vector<double> Agent::getArmsEstimatedValues()
 {
        std::vector<double> estimatedValues;
        for (const auto& arm : armsData)
        {
            estimatedValues.push_back(arm.lastEstimatedValue);
        }
        return estimatedValues;
    }

