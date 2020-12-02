/**
 * @file basis.cpp
 */
#include "../headers/basis.h"
#include "../headers/poly.h"
#include "../headers/utils.h"

/**
 * Constructor with basis deformation and basis truncation
 *
 * @param br \f$r_\perp\f$ Basis deformation
 * @param bz \f$z\f$ Basis deformation
 * @param \f$N\f$ Basis truncation param
 * @param \f$Q\f$ Basis truncation param
 */
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
    
    //According to the mathematic formulas, it's the maximums
    rhoIndex = arma::cube(mMax, nMax(0), n_zMax(0, 0));
    uint i = 0;
    for (int mi = 0; mi < mMax; mi++)
        for (int n = 0; n < nMax(mi); n++)
            for (int n_z = 0; n_z < n_zMax(mi, n); n_z++)
            {
                rhoIndex(mi, n, n_z) = i++;
            }
}

/**
 * Calculate the \f$n_z^{max}\f$ for a given \f$m + 2n + 1\f$
 *
 * @param Value calculated with \f$m + 2n + 1\f$
 * @return The \f$n_z^{max}\f$
 */
double Basis::calcn_zMax(int i) const {
    return (N + 2) * pow(Q, 2.0/3.0) + 0.5 - (i * Q);
}

/**
 * Return the basis func \f$\psi_{m,n,n_z}(r_\perp, \theta, z) \equiv Z(z, n_z) . R(r_\perp, m, n)\f$
 *
 * @param m The m param
 * @param n The n param
 * @param n_z The \f$n_z\f$ param
 * @param zVals The \f$z\f$ vector
 * @param rVals The \f$r_\perp\f$ vector
 * @return The \f$\psi_{m,n,n_z}(r_\perp, \theta, z)\f$
 */
arma::mat
Basis::basisFunc(int m, int n, int n_z, arma::vec& zVals, arma::vec& rVals) const {
    return rPart(rVals, m, n) * zPart(zVals, n_z).t();
}

/**
 * Calculate the \f$Z(z, n_z)\f$ part of the basis function
 *
 * @param z The \f$z\f$ vector
 * @param n_z The \f$n_z\f$ param
 * @return \f$Z(z, n_z)\f$
 */
arma::vec
Basis::zPart(arma::vec& z, int n_z) const {
    Poly poly;
    poly.calcHermite(n_z + 1, z / bz);

    // Small hack for 2^(n_z) : 1 << n_z is an offset of n_z bytes long so it's equal to 2^(n_z)
    double factor = 1.0 / std::sqrt(bz * (1 << n_z) * std::sqrt(M_PI) * Utils::fact(n_z));
    arma::vec expo = arma::exp(arma::square(z) / (-2 * bz * bz));

    return factor * expo % poly.hermite(n_z);
}

/**
 * Calculate the \f$R(r_\perp, m, n)\f$ part of the basis function
 *
 * @param rr The \f$r_\perp\f$ vector
 * @param m The \f$m\f$ param
 * @param n The \f$n\f$ param
 * @return \f$Z(z, n_z)\f$
 */
arma::vec
Basis::rPart(arma::vec& rr, int m, int n) const {
    Poly poly;
    poly.calcLaguerre(m+1, n+1, arma::square(rr) / (br * br));

    // Small hack for 2^(n_z) : 1 << n_z is an offset of n_z bytes long so it's equal to 2^(n_z)
    double factor = std::sqrt(Utils::fact(n)) / (br * std::sqrt(M_PI * Utils::fact(m + n)));
    arma::vec expo = arma::exp(arma::square(rr) / (-2 * br * br));
    return factor * expo % arma::pow(rr / br, m) % poly.laguerre(m, n);
}