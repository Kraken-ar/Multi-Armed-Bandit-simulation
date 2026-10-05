#include <vector>

using ArmId = std::size_t;

using ArmData = struct ArmData
{
    ArmId armId;
    double lastEstimatedValue;
    int timesPlayed = 0;
};



class Agent
{
private:
    double epslon;
    double alpha;
    ArmId BiggestRewardArmId = 0;
    std::vector<ArmData> armsData;

public:
    Agent(double epslon, double alpha,int numberOfArms);
  
    ~Agent();

    void initializeArmsData(int numberOfArms);
    ArmId makeAction();
    void updateArmData(ArmId armId, double reward);
    double generateRandomNumber(double min = 0.0, double max = 1.0);
    int generateRandomArmId();

    
};
