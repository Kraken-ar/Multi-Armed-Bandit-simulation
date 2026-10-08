#include <string>
#include <fstream>
#include <vector>
#include "plotting/LinePlotter.hpp"
class RewardHistoryTracker
{
private:
    /* data */
    std::ofstream* file;
    std::vector<double> rewardHistory;
    std::vector<int> SelectedArmHistory;
    LinePlotter* linePlotter;

     void inisializeFile( const std::string& filename);
     void inisializeHistoryContainer();
     void copyHistoryToFile();
    
public:
    RewardHistoryTracker();
    ~RewardHistoryTracker();
    void inisialize(const std::string& filename);
    void addReward(int selected_arm,double reward);
    void saveToFile(const std::string& filename);

    
    void drawLinePlot();
};



