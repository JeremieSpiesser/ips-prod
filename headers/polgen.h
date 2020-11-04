//
// Created by Nitorac on 16/09/2020.
//

#ifndef SCHRODINGER_IPS_POLGEN_H
#define SCHRODINGER_IPS_POLGEN_H

#include <armadillo>

/**
 * Polgen class
 */
class Polgen
{
public:
    static arma::mat getPolFromZVec(const arma::vec &, unsigned int);
};

#endif //SCHRODINGER_IPS_POLGEN_H
