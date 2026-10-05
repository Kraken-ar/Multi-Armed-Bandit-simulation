#include "reward/StaticRewardModel.hpp"
#include <random>

StaticRewardModel::StaticRewardModel(double rewardValue) : rewardValue(rewardValue)
{
}

StaticRewardModel::StaticRewardModel(double rewardValue,
                                     bool isNoisy, 
                                     bool addableNoise) 
                                     : 
                                     rewardValue(rewardValue), 
                                     isNoisy(isNoisy), 
                                     addableNoise(addableNoise)
{
}

StaticRewardModel::StaticRewardModel(double rewardValue,
                                    bool isNoisy, 
                                    bool addableNoise, 
                                    double noiseMean, 
                                    double noiseStd) 
                                    :
                                    rewardValue(rewardValue),
                                    isNoisy(isNoisy), 
                                    addableNoise(addableNoise), 
                                    noiseMean(noiseMean), 
                                    noiseStd(noiseStd)
{
}

void StaticRewardModel::setNoiseParameters(double noiseMean, double noiseStd)
{
    this->noiseMean = noiseMean;
    this->noiseStd = noiseStd;
}

void StaticRewardModel::setIsNoisy(bool isNoisy)
{
    this->isNoisy = isNoisy;
}

void StaticRewardModel::setAddableNoise(bool addableNoise)
{
    this->addableNoise = addableNoise;
}   

StaticRewardModel::~StaticRewardModel()
{
}

double StaticRewardModel::getNoise()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(noiseMean, noiseStd);
    double noise = d(gen);
    return noise;
}

double StaticRewardModel::getSample()
{
    double noise = 0;
    if (isNoisy)
    {
        noise = getNoise();
    }

    double rewardValue = this->rewardValue + noise;

    if (addableNoise)
    {
       this->rewardValue = rewardValue;
    }
    
    
    return rewardValue;
}

