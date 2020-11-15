//
// Created by Nitorac on 15/11/2020.
//

#include "../headers/basisFunc.h"
#include "../headers/poly.h"
#include "../headers/utils.h"

BasisFunc::BasisFunc(double bt, double bz) : bt(bt), bz(bz){}

arma::vec
BasisFunc::calcZ(arma::vec& z, int n_z) const {
    Poly poly;
    poly.calcHermite(n_z + 1, z / bz);

    // Small hack for 2^(n_z) : 1 << n_z is an offset of n_z bytes long so it's equal to 2^(n_z)
    double factor = 1.0 / std::sqrt(bz * (1 << n_z) * std::sqrt(M_PI) * Utils::fact(n_z));
    arma::vec expo = arma::exp(arma::square(z) / (-2 * bz * bz));

    return factor * expo % poly.hermite(n_z);
}

arma::vec
BasisFunc::calcR(arma::vec& rt, int m, int n) {
    Poly poly;
    poly.calcLaguerre(m+1, n+1, arma::square(rt) / (bt * bt));

    // Small hack for 2^(n_z) : 1 << n_z is an offset of n_z bytes long so it's equal to 2^(n_z)
    double factor = std::sqrt(Utils::fact(n)) / (bt * std::sqrt(M_PI * Utils::fact(m + n)));
    arma::vec expo = arma::exp(arma::square(rt) / (-2 * bt * bt));
    return factor * expo % arma::pow(rt / bt, m) % poly.laguerre(m, n);
}