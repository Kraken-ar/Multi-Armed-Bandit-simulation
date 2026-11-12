#include "SimulationBuilder.hpp"

SimulationBuilder::SimulationBuilder(const std::string &configFilePath) : configReader(new ConfigReader(configFilePath))
{
    
}

SimulationBuilder::~SimulationBuilder()
{
}


Agent* SimulationBuilder::getAgent()
{
    
    return configReader->getAgent();
}


Enviroment* SimulationBuilder::getEnviroment()
{
    return configReader->getEnviroment();
}