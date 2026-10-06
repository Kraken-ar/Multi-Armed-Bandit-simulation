
#include "Agent.hpp"
#include "Arm.hpp"
#include <vector>
class Enviroment
{
private:
    Agent* agent;
    std::vector<Arm*> arms;

public:
    Enviroment(Agent* agent, std::vector<Arm*> arms);
    ~Enviroment();
    void fit(int it);
};

