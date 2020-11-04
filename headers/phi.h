//
// Created by Soufiane AMMY DRISS on 16/09/2020.
//

#ifndef IPS_CLIPARSER_PHI_H
#define IPS_CLIPARSER_PHI_H

#include <armadillo>

/**
 * The Phi class
 */
class Phi
{
public:
    Phi(int, int, int, int);
    virtual ~Phi();

    //setters
    void setHermite(const arma::mat &);
    //getters
    arma::mat getResults();
    arma::mat getM();
    double getMin() const;
    double getMax() const;
    int getNVals() const;
    arma::vec getZ();
    //methods
    void fill_Z();
    static double firstTerm(int);
    arma::vec secondTerm();
    void calculateAll();
    static double factorial(int);

private:
    arma::vec Z;
    arma::mat M;
    arma::mat hermite;
    double min;
    double max;
    int n_vals;
    int n_iter;
};

#endif //IPS_CLIPARSER_PHI_H
