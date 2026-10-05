#include "reward/RewardModel.hpp"
class GaussianRewardModel : public RewardModel
{
private:
    /* data */
    double mean;
    double std;
public:
    GaussianRewardModel(double mean, double std);
    ~GaussianRewardModel();
    double getSample() override;
};


