
#include "Agent.hpp"
#include "Arm.hpp"
#include "history/RewardHistoryTracker.hpp"
#include <vector>
class Enviroment
{
private:
    Agent* agent;
    std::vector<Arm*> arms;
    RewardHistoryTracker* rewardHistoryTracker;

public:
    Enviroment(Agent* agent, std::vector<Arm*> arms);
    ~Enviroment();
    void fit(int it);
};

