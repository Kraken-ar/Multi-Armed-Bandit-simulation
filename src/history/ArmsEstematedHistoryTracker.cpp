#include "history/ArmsEstematedHistoryTracker.hpp"



ArmsEstematedHistoryTracker::ArmsEstematedHistoryTracker(int numberOfArms, const std::string& filename): numberOfArms(numberOfArms)
{
    this->inisialize(numberOfArms, filename);
}

ArmsEstematedHistoryTracker::~ArmsEstematedHistoryTracker()
{
}

void ArmsEstematedHistoryTracker::inisialize(int numberOfArms, const std::string& filename){
    this->file = new std::ofstream(filename);
    *file<<"Step";
    for (int i = 0; i < numberOfArms; i++)
    {
        *file << ",Q_" << i;
    }
    *file << "\n";
    
}

void ArmsEstematedHistoryTracker::addArmsEstemated(int step, std::vector<double> armsData){
    *file << step;
    for (int i = 0; i < numberOfArms ; i++)
    {
        *file << "," << armsData.at(i);
    }
    *file << "\n";
}


void ArmsEstematedHistoryTracker::saveFile(){
    file->close();
}