//
// Created by Nitorac on 18/11/2020.
//

#ifndef IPS_PROD_NUCLEAR_H
#define IPS_PROD_NUCLEAR_H

#include <armadillo>
#include "../headers/basis.h"

class Nuclear
{
public:
    Nuclear(arma::vec, arma::vec, double, double, double, double);
    arma::mat naiveCalc();
    arma::mat optiCalc();
private:
    arma::vec r;
    arma::vec z;
    Basis basis;
    arma::mat rhoMat;
    double rho(int, int, int, int, int, int);
    double rho(int, int);
};

#endif //IPS_PROD_NUCLEAR_H
