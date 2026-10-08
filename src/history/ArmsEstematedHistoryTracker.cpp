#include "history/ArmsEstematedHistoryTracker.hpp"



ArmsEstematedHistoryTracker::ArmsEstematedHistoryTracker(int numberOfArms): numberOfArms(numberOfArms)
{
    this->inisializeHistoryContainer(numberOfArms);
    linePlotter = new LinePlotter();
}

ArmsEstematedHistoryTracker::~ArmsEstematedHistoryTracker()
{
}

void ArmsEstematedHistoryTracker::inisializeFile( const std::string& filename){
    this->file = new std::ofstream(filename);
    *file<<"Step";
    for (int i = 0; i < numberOfArms; i++)
    {
        *file << ",Q_" << i;
    }
    *file << "\n";
    
}

void ArmsEstematedHistoryTracker::inisializeHistoryContainer(int numberOfArms){
    this->armsEstematedHistory = new ArmsEstematedHistory();
    for (int i = 0; i < numberOfArms; i++)
    {
        armsEstematedHistory->push_back(std::vector<double>());
    }
}

void ArmsEstematedHistoryTracker::addArmsEstemated(std::vector<double> armsData){
    

    for(int i = 0; i<armsEstematedHistory->size();i++){
        armsEstematedHistory->at(i).push_back(armsData.at(i));
    }
}

void ArmsEstematedHistoryTracker::copyHistoryToFile(){
    for (int step = 0;step < armsEstematedHistory->at(0).size();step++){
        *file << step;
    for (int i = 0; i < numberOfArms ; i++)
    {
        *file << "," << armsEstematedHistory->at(i).at(step);
    }
    *file << "\n";
    }
}



void ArmsEstematedHistoryTracker::saveFile(const std::string& filename){
    this->inisializeFile(filename);
    this->copyHistoryToFile();
    file->close();
}

void ArmsEstematedHistoryTracker::drawLinePlot(){
    this->linePlotter->draw(*armsEstematedHistory,"Arms Estemation History","step","Estemation");
}