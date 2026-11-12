#include <iostream>
#include <vector>
// #include "reward/GaussianRewardModel.hpp"
#include "reward/StaticRewardModel.hpp"
#include "Arm.hpp"
#include "Enviroment.hpp"
#include "SimulationBuilder.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
    // take the config file path from the command line arguments

    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <config_file_path>" << std::endl;
        return 1;
    }

    std::string configFilePath = argv[1];

    SimulationBuilder* simulationBuilder = new SimulationBuilder(configFilePath);
    Agent* agent = simulationBuilder->getAgent();
    Enviroment* env = simulationBuilder->getEnviroment();
    env->fit(10000);
    




    // vector<Arm*> arms = {
    //   new Arm(new StaticRewardModel(5,true,true,0,0.1)),
    //    new Arm( new StaticRewardModel(10,true,true,0,0.1)),
    //    new Arm( new StaticRewardModel(20,true,true,0,0.1)),
    //    new Arm( new StaticRewardModel(7,true,true,0,0.1)),
    //    new Arm( new StaticRewardModel(0,true,true,0,0.1)),
    // };
   
    // Agent* agent = new Agent(0.1,0.1);

    // Enviroment* env = new Enviroment(agent,arms);

    // env->fit(10000);
    
   
   
    return 0;
}
