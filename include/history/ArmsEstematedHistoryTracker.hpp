#include <fstream>
#include <vector>

class ArmsEstematedHistoryTracker
{
private:
    std::ofstream* file;
    int numberOfArms;

     void inisialize(int numberOfArms, const std::string& filename);
public:
    ArmsEstematedHistoryTracker(int numberOfArms, const std::string& filename);
    ~ArmsEstematedHistoryTracker();
   
    void addArmsEstemated(int step, std::vector<double> armsData);
    void saveFile();
};

