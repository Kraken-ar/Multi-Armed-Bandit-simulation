#include "RewardModel.hpp"
class StaticRewardModel : public RewardModel
{
private:
    double rewardValue;
    bool isNoisy;
    bool addableNoise;
    double noiseMean = 0;
    double noiseStd = 0.1;
public:
    double getSample() override;
    double getNoise();
   
    StaticRewardModel(double rewardValue);
    StaticRewardModel(double rewardValue, bool isNoisy, bool addableNoise);
    StaticRewardModel(double rewardValue, bool isNoisy, bool addableNoise, double noiseMean, double noiseStd);
    void setNoiseParameters(double noiseMean, double noiseStd);
    void setIsNoisy(bool isNoisy);
    void setAddableNoise(bool addableNoise);
    ~StaticRewardModel();
};


