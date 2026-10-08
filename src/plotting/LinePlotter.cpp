#include "plotting/LinePlotter.hpp"



LinePlotter::LinePlotter(/* args */)
{
}

LinePlotter::~LinePlotter()
{
}



void LinePlotter::draw(std::vector<std::vector<double>> records ,std::string plotTitle,std::string xLabelTitle,std::string yLabelTitle){

    using namespace matplot;
    for(int i = 0; i < records.size(); i++){
        plot(records.at(i));
        hold(on);
    }
    title(plotTitle);
    xlabel(xLabelTitle);
    ylabel(yLabelTitle);
    show();



}