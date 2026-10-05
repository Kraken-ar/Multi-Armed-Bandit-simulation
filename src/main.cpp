#include <iostream>
#include "reward/GaussianRewardModel.hpp"
#include "reward/StaticRewardModel.hpp"
#include "Arm.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
    RewardModel* rewardModel = new StaticRewardModel(5,true,true,0,0.2);
    Arm* arm = new Arm(rewardModel);
    
    for (size_t i = 0; i < 100; i++)
    {
        cout<<arm->getReward()<<endl;
    }
    
   
   
    return 0;
}
