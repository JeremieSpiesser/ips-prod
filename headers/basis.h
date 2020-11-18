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

    int mMax;
    arma::mat n_zMax;
    arma::vec nMax;

    arma::vec zPart(arma::vec &, int) const;
    arma::vec rPart(arma::vec &, int, int) const;
    arma::mat basisFunc(int, int, int, arma::vec&, arma::vec&) const;

    arma::cube rhoIndex;
    
private:
    double br;
    double bz;
    double N;
    double Q;

    double calcn_zMax(int) const;
};

#endif //IPS_PROD_BASIS_H
