#ifndef PHIPLOTTER_H
#define PHIPLOTTER_H
#include <iostream>
#include <armadillo>
#include "./polgen.h"
#include "./phi.h"


/**
 * The PhiPlotter class
 */
class PhiPlotter
{
public:
    PhiPlotter(Phi);
    void exportResults(std::string, std::string);
private:
    Phi phi;
};


#endif // PHIPLOTTER_H
