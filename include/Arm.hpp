#include "reward/RewardModel.hpp"
class Arm
{
private:
   RewardModel* rewardModel;
public:
    Arm(/* args */);
    Arm(RewardModel* rewardModel);
    ~Arm();
    void setRewardModel(RewardModel* rewardModel);
    double getReward();
    
  
};

