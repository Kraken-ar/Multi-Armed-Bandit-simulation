#include <vector>
#include <string>
#include <cmath>
#include <matplot/matplot.h>

#pragma once


template <typename RecordType>
class Plotter
{
private:
    std::vector<RecordType> records;
   
public:
    Plotter(/* args */);
    ~Plotter();
    virtual void draw(std::vector<RecordType> records,std::string plotTitle, std::string xLabelTitle,std::string yLabelTitle) = 0;
};

