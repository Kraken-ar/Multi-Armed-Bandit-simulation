#include <iostream>
#include <vector>
// #include "reward/GaussianRewardModel.hpp"
#include "reward/StaticRewardModel.hpp"
#include "Arm.hpp"
#include "Enviroment.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
   
    vector<Arm*> arms = {
      new Arm(new StaticRewardModel(0,true,true,0,0.1)),
       new Arm( new StaticRewardModel(0,true,true,0,0.1)),
       new Arm( new StaticRewardModel(0,true,true,-3,2)),
       new Arm( new StaticRewardModel(0,true,true,0,0.1)),
       new Arm( new StaticRewardModel(0,true,true,0,0.1)),
    };
   
    Agent* agent = new Agent(0.1,0.1);

    Enviroment* env = new Enviroment(agent,arms);

    env->fit(10000);
    
   
   
    return 0;
}
