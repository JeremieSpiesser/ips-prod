//
// Created by Nitorac on 15/11/2020.
//

#ifndef IPS_PROD_BASIS_H
#define IPS_PROD_BASIS_H

#include <armadillo>

/**
 * Basis class
 */
class Basis
{
public:
    Basis(double, double, double, double);

    /** The \f$m^\textrm{max} \equiv \textrm{sup}\left\{i:n_z^\textrm{max}(i)\ge 1\right\}\f$ */
    int mMax;
    /** The matrix \f$n_z^{\textrm{max}}\f$ in which \f$n_z^{max}(m, n) = n_z^\textrm{max}(m+2n+1)\f$ */
    arma::mat n_zMax;
    /** The matrix \f$n^{\textrm{max}}\f$ in which \f$n^{max}(n) = \frac{1}{2}(m^\textrm{max}-m-1) + 1\f$ */
    arma::vec nMax;

    arma::vec zPart(arma::vec &, int) const;
    arma::vec rPart(arma::vec &, int, int) const;
    arma::mat basisFunc(int, int, int, arma::vec&, arma::vec&) const;

    /** The matrix \f$\rho_{ab}\f$ */
    arma::cube rhoIndex;
    
private:
    /** Basis deformation param */
    double br;
    /** Basis deformation param */
    double bz;
    /** Basis truncation param */
    double N;
    /** Basis truncation param */
    double Q;

    double calcn_zMax(int) const;
};

#endif //IPS_PROD_BASIS_H
