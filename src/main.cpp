#include <iostream>

#include "SimulationBuilder.hpp"

int main(int argc, char const* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <config_file_path>" << std::endl;
        return 1;
    }

    SimulationBuilder* simulationBuilder = new SimulationBuilder(argv[1]);
    Enviroment* enviroment = simulationBuilder->getEnviroment();
    enviroment->fit();

    return 0;
}
