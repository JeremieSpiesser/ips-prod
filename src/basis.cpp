//
// Created by Nitorac on 15/11/2020.
//

#include "../headers/basis.h"
#include "../headers/poly.h"
#include "../headers/utils.h"

Basis::Basis(double br, double bz, double N, double Q) : br(br), bz(bz), N(N), Q(Q){}

arma::vec
Basis::zPart(arma::vec& z, int n_z) {
    Poly poly;
    poly.calcHermite(n_z + 1, z / bz);

    // Small hack for 2^(n_z) : 1 << n_z is an offset of n_z bytes long so it's equal to 2^(n_z)
    double factor = 1.0 / std::sqrt(bz * (1 << n_z) * std::sqrt(M_PI) * Utils::fact(n_z));
    arma::vec expo = arma::exp(arma::square(z) / (-2 * bz * bz));

    return factor * expo % poly.hermite(n_z);
}

arma::vec
Basis::rPart(arma::vec& rr, int m, int n) {
    Poly poly;
    poly.calcLaguerre(m+1, n+1, arma::square(rr) / (br * br));

    // Small hack for 2^(n_z) : 1 << n_z is an offset of n_z bytes long so it's equal to 2^(n_z)
    double factor = std::sqrt(Utils::fact(n)) / (br * std::sqrt(M_PI * Utils::fact(m + n)));
    arma::vec expo = arma::exp(arma::square(rr) / (-2 * br * br));
    return factor * expo % arma::pow(rr / br, m) % poly.laguerre(m, n);
}