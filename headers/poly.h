//
// Created by Nitorac on 16/09/2020.
//

#ifndef SCHRODINGER_IPS_POLGEN_H
#define SCHRODINGER_IPS_POLGEN_H

#include <armadillo>

/**
 * Poly class
 */
class Poly
{
public:
    // Hermite related functions
    void calcHermite(int, const arma::vec &);
    arma::vec hermite(int);
    // Laguerre related functions
    void calcLaguerre(int, int, arma::vec);
    arma::vec laguerre(int, int);
private:
    arma::mat hermiteRes;
    arma::cube laguerreRes;
};

#endif //SCHRODINGER_IPS_POLGEN_H
