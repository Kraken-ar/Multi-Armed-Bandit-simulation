#include "history/RewardHistoryTracker.hpp"


RewardHistoryTracker::RewardHistoryTracker(const std::string& filename)
{
    this->inisialize(filename);
}

RewardHistoryTracker::~RewardHistoryTracker()
{
}

void RewardHistoryTracker::inisialize(const std::string& filename){
    file = new std::ofstream(filename);
    *file << "Step,SelectedArm,Reward\n";

}

void RewardHistoryTracker::addReward(int step,int selected_arm,double reward){
    *file << step << "," << selected_arm << "," << reward << "\n";
}

void RewardHistoryTracker::saveToFile(){
    file->close();
}