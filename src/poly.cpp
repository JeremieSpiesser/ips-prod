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
Poly::calcHermite(int n, const arma::vec z)
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
