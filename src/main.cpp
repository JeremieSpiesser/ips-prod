#include <iostream>
#include <armadillo>
#include "../headers/poly.h"
#include "../headers/basis.h"
#include "../headers/nuclear.h"
#include "../headers/exporter.h"

int
main()
{
    std::cout << "       -=-=[ Testing new class layout ]=-=-" << std::endl;
    Poly pol;
    arma::vec XorR = arma::linspace(-10, 10, 32);
    arma::vec Y = arma::linspace(-10, 10, 32);
    arma::vec Z = arma::linspace(-20, 20, 64);

    Nuclear nuclear(XorR, Z, 1.935801664793151, 2.829683956491218, 14, 1.3);

    std::cout << std::endl << "       -=-=[ Testing basis truncation ]=-=-" << std::endl;
    Basis b(1.935801664793151, 2.829683956491218, 14, 1.3);

    arma::wall_clock timer;
    timer.tic();
    arma::mat res = nuclear.naiveCalc();
    std::cout << timer.toc() << " secondes pour l'algorithme naif" << std::endl;


    Exporter exporter(res, XorR, Y, Z);
    exporter.toDf3("visu/visu.df3");
    exporter.toRaw("visu/visu.raw");
    exporter.toCsv("visu/visu.csv");
    return 0;
}
