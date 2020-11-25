//
// Created by Nitorac on 15/11/2020.
//

#include "../headers/basis.h"
#include "../headers/poly.h"
#include "../headers/utils.h"

using namespace std;

Basis::Basis(double br, double bz, double N, double Q) : br(br), bz(bz), N(N), Q(Q) {
    // mMax
    mMax = 0;
    while (calcn_zMax(mMax + 1) >= 1.0) {
        mMax++;
    }

    // nMax
    arma::vec m = arma::regspace(0, mMax - 1);
    nMax = arma::floor(0.5 * ((arma::ones(mMax) * mMax) - m - 1) + 1);

    // n_zMax
    n_zMax = arma::zeros(mMax, nMax(0));
    for (int i = 0; i < mMax; i++) {
        for (int j = 0; j < nMax[i]; j++) {
            n_zMax(i, j) = (int) calcn_zMax(i + 2*j + 1);
        }
    }
    
    //Selon les formules, ce sont les maximums
    rhoIndex = arma::cube(mMax, nMax(0), n_zMax(0, 0));
    uint i = 0;
    for (int m = 0; m < mMax; m++)
        for (int n = 0; n < nMax(m); n++)
            for (int n_z = 0; n_z < n_zMax(m, n); n_z++)
            {
                rhoIndex(m, n, n_z) = i++;
            }
}

double Basis::calcn_zMax(int i) const {
    return (N + 2) * pow(Q, 2.0/3.0) + 0.5 - (i * Q);
}

arma::mat
Basis::basisFunc(int m, int n, int n_z, arma::vec& zVals, arma::vec& rVals) const {
    return rPart(rVals, m, n) * zPart(zVals, n_z).t();
}

arma::vec
Basis::zPart(arma::vec& z, int n_z) const {
    Poly poly;
    poly.calcHermite(n_z + 1, z / bz);

    // Small hack for 2^(n_z) : 1 << n_z is an offset of n_z bytes long so it's equal to 2^(n_z)
    double factor = 1.0 / std::sqrt(bz * (1 << n_z) * std::sqrt(M_PI) * Utils::fact(n_z));
    arma::vec expo = arma::exp(arma::square(z) / (-2 * bz * bz));

    return factor * expo % poly.hermite(n_z);
}

arma::vec
Basis::rPart(arma::vec& rr, int m, int n) const {
    Poly poly;
    poly.calcLaguerre(m+1, n+1, arma::square(rr) / (br * br));

    // Small hack for 2^(n_z) : 1 << n_z is an offset of n_z bytes long so it's equal to 2^(n_z)
    double factor = std::sqrt(Utils::fact(n)) / (br * std::sqrt(M_PI * Utils::fact(m + n)));
    arma::vec expo = arma::exp(arma::square(rr) / (-2 * br * br));
    return factor * expo % arma::pow(rr / br, m) % poly.laguerre(m, n);
}