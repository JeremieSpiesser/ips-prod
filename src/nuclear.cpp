#include "../headers/nuclear.h"

//
// Created by Nitorac on 18/11/2020.
//

/**
 * Create a class ready to calculate the nuclear density (which loads the rho.arma matrix)
 *
 * @param r The \f$X\f$ vector (which is the same as the \f$R\f$ because \f$\theta = 0\f$)
 * @param z The \f$Z\f$ vector
 * @param br \f$r_\perp\f$ Basis deformation
 * @param bz \f$z\f$ Basis deformation
 * @param N Basis truncation param
 * @param Q Basis truncation param
 */
Nuclear::Nuclear(arma::vec r, arma::vec z, double br, double bz, double N, double Q): r(r), z(z),
                                                                                      basis(Basis(br, bz, N, Q))
{
    rhoMat.load("rho.arma", arma::arma_ascii);
}

/**
 * Returns the \f$\rho_{ab}\f$ value using quantum integers instead of a and b
 *
 * @param m first quantum number for a
 * @param n second quantum number for a
 * @param n_z third quantum number for a
 *
 * @param mp first quantum number for b
 * @param np second quantum number for b
 * @param n_zp third quantum number for b
 */
double
Nuclear::rho(int m, int n, int n_z, int mp, int np, int n_zp)
{
    return rhoMat(basis.rhoIndex(m, n, n_z), basis.rhoIndex(mp, np, n_zp));
}

/**
 * Returns the \f$\rho_{ab}\f$ value using raw a and b indexes
 *
 * @param a First raw index
 * @param b Second raw index
 */
double
Nuclear::rho(int a, int b)
{
    return rhoMat(a, b);
}

/**
 * Calculates the nuclear density in a naive way and return the result
 *
 * @return The matrix with the nuclear density with \f$R\f$ by rows and \f$Z\f$ by columns
 */
arma::mat
Nuclear::naiveCalc()
{
    arma::mat result = arma::zeros(r.n_elem, z.n_elem); // number of points on r- and z- axes
    for (int m = 0; m < basis.mMax; m++) {
        for (int n = 0; n < basis.nMax(m); n++) {
            for (int n_z = 0; n_z < basis.n_zMax(m, n); n_z++) {
                for (int mp = 0; mp < basis.mMax; mp++) {
                    for (int np = 0; np < basis.nMax(mp); np++) {
                        for (int n_zp = 0; n_zp < basis.n_zMax(mp, np); n_zp++) {
                            arma::mat funcA = basis.basisFunc( m,  n,  n_z, z, r);
                            arma::mat funcB = basis.basisFunc(mp, np, n_zp, z, r);
                            result += funcA % funcB * rho(m, n, n_z, mp, np, n_zp); // mat += mat % mat * double
                        }
                    }
                }
            }
        }
    }
    return result;
}

/**
 * Calculates the nuclear density in a optimized way and return the result
 *
 * @return The matrix with the nuclear density with \f$R\f$ by rows and \f$Z\f$ by columns
 */
arma::mat
Nuclear::optiCalc()
{
    //First, we precalculate the basisFuncs

    arma::mat Zparts(basis.n_zMax(0, 0), z.n_elem); // Z a la taille maximum en n_zMax(0)
    for (uint n_z = 0; n_z < Zparts.n_rows; n_z++) {
        Zparts.row(n_z) = basis.zPart(z, n_z).t();
    }

    uint i = 0;
    arma::cube basisFuncs(r.n_elem, z.n_elem, basis.mMax * basis.nMax(0) * basis.n_zMax(0, 0) /* Valeur maximale */);
    for (int m = 0; m < basis.mMax; m++) {
        for (int n = 0; n < basis.nMax(m); n++) {
            arma::vec R = basis.rPart(r, m, n);
            for (uint n_z = 0; n_z < basis.n_zMax(m, n); n_z++) {
                basisFuncs.slice(i) = R * Zparts.row(n_z);
                ++i;
            }
        }
    }

    arma::mat result = arma::zeros(r.n_elem, z.n_elem); // number of points on r- and z- axes
    for (int m = 0; m < basis.mMax; m++) {
        for (int n = 0; n < basis.nMax(m); n++) {
            for (int n_z = 0; n_z < basis.n_zMax(m, n); n_z++) {
                // Now, we're using the symetry : rho(a,b) = rho(b,a)
                int a = basis.rhoIndex(m, n, n_z);

                for (int b = basis.rhoIndex(m, 0, 0); b < a; b++) {
                    result += basisFuncs.slice(a) % basisFuncs.slice(b) * rho(a, b) * 2.0;
                }
                result += rho(a, a) * basisFuncs.slice(a) % basisFuncs.slice(a);
            }
        }
    }
    return result;
}
