//
// Created by Nitorac on 25/11/2020.
//

#ifndef IPS_PROD_EXPORTER_H
#define IPS_PROD_EXPORTER_H

#include "../headers/nuclear.h"

class Exporter
{
public:
    Exporter(const arma::mat &, const arma::vec &, const arma::vec &, const arma::vec &);
    void toCsv(const std::string &);
    void toDf3(const std::string &);
    void toRaw(const std::string &);

private:
    const arma::vec &XorR;
    const arma::vec &Y;
    const arma::vec &Z;
    const arma::mat &nuclearDensity;
    arma::cube euclidianDensity;

    static std::string cubeToDf3(const arma::cube &);
    static std::string cubeToRaw(const arma::cube &);
};

#endif //IPS_PROD_EXPORTER_H
