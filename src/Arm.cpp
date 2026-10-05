#include "Arm.hpp"


Arm::Arm()
{
}

Arm::Arm(RewardModel* rewardModel) : rewardModel(rewardModel)
{
}

Arm::~Arm()
{
}

void Arm::setRewardModel(RewardModel* rewardModel)
{
    this->rewardModel = rewardModel;
}

double Arm::getReward()
{
    return rewardModel->getSample();
}
