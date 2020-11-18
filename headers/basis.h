//
// Created by Nitorac on 15/11/2020.
//

#ifndef IPS_PROD_BASIS_H
#define IPS_PROD_BASIS_H

#include <armadillo>

/**
 * BasisFunc class
 */
class Basis
{
public:
    // Constructor with basis deformation and polynom generator params
    Basis(double, double, double, double);

    arma::vec zPart(arma::vec &, int);
    arma::vec rPart(arma::vec &, int, int);

    int mMax;
    arma::mat n_zMax;
    arma::vec nMax;

private:
    double br;
    double bz;
    double N;
    double Q;

    double calcn_zMax(int) const;
};

#endif //IPS_PROD_BASIS_H
