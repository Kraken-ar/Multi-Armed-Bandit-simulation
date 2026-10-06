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
      new Arm(new StaticRewardModel(1,true,true,0,0.1)),
       new Arm( new StaticRewardModel(7,true,true,0,0.1)),
       new Arm( new StaticRewardModel(3,true,true,0,0.1)),
       new Arm( new StaticRewardModel(20,true,true,0,0.1)),
       new Arm( new StaticRewardModel(-5,true,true,0,0.1)),
    };
   
    Agent* agent = new Agent(0.1,0.1);

    Enviroment* env = new Enviroment(agent,arms);

    env->fit(1000);
    
   
   
    return 0;
}
