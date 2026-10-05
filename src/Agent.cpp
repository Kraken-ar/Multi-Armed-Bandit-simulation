#include "Agent.hpp"
#include <random>
Agent::Agent(double epslon, double alpha,int numberOfArms) : epslon(epslon), alpha(alpha)
{
    this->initializeArmsData(numberOfArms);
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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}
int Agent::generateRandomArmId()
{
    std::random_device rd;
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

    return BiggestRewardArmId;
    
}


void Agent::updateArmData(ArmId armId, double reward)
{
    ArmData& arm = armsData[armId];

    arm.timesPlayed++;
    arm.lastEstimatedValue = arm.lastEstimatedValue + (alpha*(reward - arm.lastEstimatedValue));

    if (reward > armsData[BiggestRewardArmId].lastEstimatedValue)
    {
        BiggestRewardArmId = armId;
    }
    
    
}
