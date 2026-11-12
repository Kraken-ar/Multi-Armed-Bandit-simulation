#include "config/ConfigReader.hpp"
#pragma once
class SimulationBuilder
{
private:
    ConfigReader *configReader;
public:
    SimulationBuilder(const std::string &configFilePath);
    ~SimulationBuilder();

    Agent* getAgent();
    Enviroment* getEnviroment();
};

