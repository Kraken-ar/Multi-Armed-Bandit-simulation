#include "Plotter.hpp"
#pragma once
class LinePlotter : public Plotter<std::vector<double>>
{
private:
    /* data */
public:
    LinePlotter(/* args */);
    ~LinePlotter();

    void draw(std::vector<std::vector<double>> records ,std::string plotTitle , std::string xLabelTitle,std::string yLabelTitle) override;
};


template <typename RecordType>
Plotter<RecordType>::Plotter(/* args */)
{
}
template <typename RecordType>
Plotter<RecordType>::~Plotter()
{
}





