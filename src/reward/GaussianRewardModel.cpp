#include "reward/GaussianRewardModel.hpp"
#include <random>

GaussianRewardModel::GaussianRewardModel(double mean, double std) : mean(mean), std(std)
{
}

GaussianRewardModel::~GaussianRewardModel()
{
}

double GaussianRewardModel::getSample()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(mean, std);
    double sample = d(gen);
    return sample;
}