/**
 *  @file polgen.cpp
 */

#include "../headers/poly.h"
#include <armadillo>

/**
 * Generates a matrix containing per row the iterations of the Hermite polynomial
 * and per column the points to be evaluated for each polynomial.
 *
 * @param z The vector of points to be evaluated
 * @param n The final iteration of the Hermite polynomial requested
 * @return A matrix of size (n, z.n_elem)
 */
void
Poly::calcHermite(int n, const arma::vec &z)
{
    arma::mat res(n, z.n_elem);
    arma::mat zt = z.t();

    // For each Hn
    for (int i = 0; i < n; i++) {
        // Case H0=1 handling
        if (0 == i) {
            res.row(i).fill(1);
            continue;
        }

        // For each given z
        if (1 == i)
            res.row(i) = 2.0 * zt;
        else
            res.row(i) = 2.0 * zt % res.row(i - 1) - 2.0 * (i - 1) * res.row(i - 2);
    }
    hermiteRes = res;
}

arma::vec
Poly::hermite(int n)
{
    return hermiteRes.row(n).t();
}

void
Poly::calcLaguerre(int m, int n, arma::vec z)
{
    //gerenating M matrix
    arma::vec reg = arma::regspace(0,m);
    //reg.print("Reg : ");
    arma::vec tmp1(z.n_elem,arma::fill::ones);
    //tmp1.print("TMP1 : ");
    arma::mat M = reg*tmp1.t();

    // Generating Z matrice
    arma::vec tmp2(m+1,arma::fill::ones);
    arma::mat Z = tmp2 * z.t();

    arma::cube L(m+1,z.n_elem,n+1);

    if (n >= 0){
        L.slice(0) = arma::mat(m+1,z.n_elem,arma::fill::ones);
    }
    if (n >=1){
        L.slice(1) = 1 + M - Z;
    }
    if (n >=2){
        for (int i=2 ; i<=n ; i = i+1){
            L.slice(i) = (2+(M-1-Z)/i)%L.slice(i-1) - (1+(M-1)/i)%L.slice(i-2);
        }
    }
    laguerreRes = L;
}

arma::vec
Poly::laguerre(int m, int n)
{
    return laguerreRes.slice(n).row(m).t();
}
