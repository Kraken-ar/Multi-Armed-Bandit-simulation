#include "history/RewardHistoryTracker.hpp"


RewardHistoryTracker::RewardHistoryTracker()
{
    this->inisializeHistoryContainer();
    linePlotter = new LinePlotter();
}

RewardHistoryTracker::~RewardHistoryTracker()
{
}

void RewardHistoryTracker::inisializeFile(const std::string& filename){
    file = new std::ofstream(filename);
    *file << "Step,SelectedArm,Reward\n";

}


void RewardHistoryTracker::inisializeHistoryContainer(){
    this->rewardHistory = {};
    this->SelectedArmHistory = {};
}



void RewardHistoryTracker::addReward(int selected_arm,double reward){
    
    this->rewardHistory.push_back(reward);
    this->SelectedArmHistory.push_back(selected_arm);

}

void RewardHistoryTracker::copyHistoryToFile(){
    for (int i = 0; i < rewardHistory.size(); i++)
    {
       *file << i+1 << "," << SelectedArmHistory.at(i) << "," << rewardHistory.at(i) << "\n";
    }
    
}

void RewardHistoryTracker::saveToFile(const std::string& filename){
    this->inisializeFile(filename);
    this->copyHistoryToFile();
    file->close();
}


void RewardHistoryTracker::drawLinePlot(){
    this->linePlotter->draw({this->rewardHistory},"Reward History","Step","Reward");
}