//
// Created by root_ on 07/10/2020.
//

#ifndef IPS_CLIPARSER_VERIFACATORSHRODINGER_H
#define IPS_CLIPARSER_VERIFACATORSHRODINGER_H

#include "../headers/phi.h"
#include <armadillo>

/**
 * The SchrodingerVerificator class
 */
class SchrodingerVerificator
{
public:
    static arma::vec getEn(Phi, int);
    static arma::mat computeIntegralOrthonormality(int);
    static arma::vec derivative(const arma::vec &, double);
    static void orthogonality(int);
};


#endif //IPS_CLIPARSER_VERIFACATORSHRODINGER_H
