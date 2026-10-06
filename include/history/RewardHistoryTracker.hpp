#include <string>
#include <fstream>
class RewardHistoryTracker
{
private:
    /* data */
    std::ofstream* file;
public:
    RewardHistoryTracker(const std::string& filename);
    ~RewardHistoryTracker();
    void inisialize(const std::string& filename);
    void addReward(int step,int selected_arm,double reward);
    void saveToFile();
};



