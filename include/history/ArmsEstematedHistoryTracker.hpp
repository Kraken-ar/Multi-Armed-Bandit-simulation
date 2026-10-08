#include <fstream>
#include <vector>
#include "plotting/LinePlotter.hpp"

using ArmsEstematedHistory = std::vector<std::vector<double>>;


class ArmsEstematedHistoryTracker
{
private:
    std::ofstream* file;
    int numberOfArms;
    ArmsEstematedHistory* armsEstematedHistory;
    Plotter<std::vector<double>>* linePlotter;

     void inisializeFile( const std::string& filename);
     void inisializeHistoryContainer(int numberOfArms);
     void copyHistoryToFile();
public:
    ArmsEstematedHistoryTracker(int numberOfArms);
    ~ArmsEstematedHistoryTracker();
   
    void addArmsEstemated( std::vector<double> armsData);
    void saveFile( const std::string& filename);
    void drawLinePlot();
};

