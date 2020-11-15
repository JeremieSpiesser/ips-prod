//
// Created by Nitorac on 15/11/2020.
//

#ifndef IPS_PROD_BASISFUNC_H
#define IPS_PROD_BASISFUNC_H

#include <armadillo>

/**
 * BasisFunc class
 */
class BasisFunc
{
public:
    // Constructor with basis deformation and polynom generator params
    BasisFunc(double, double);

    arma::vec calcZ(arma::vec &, int) const;
    arma::vec calcR(arma::vec &, int, int);
private:
    double bt;
    double bz;
};

#endif //IPS_PROD_BASISFUNC_H
