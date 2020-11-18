#include <iostream>
#include <armadillo>
#include "../headers/poly.h"
#include "../headers/basis.h"
#include "../headers/nuclear.h"

int
main()
{
    std::cout << "       -=-=[ Testing new class layout ]=-=-" << std::endl;
    Poly pol;
    arma::vec z({1, 2, 3, 4, 5, 6});
    arma::vec r({1, 2, 3, 4, 5, 6});

    Nuclear nuclear(r, z, 1.935801664793151, 2.829683956491218, 14, 1.3);


    arma::wall_clock timer;
    timer.tic();
    arma::mat res = nuclear.naiveCalc();
    std::cout << timer.toc() << " secondes pour l'algorithme naif" << std::endl;
    res.print("Res");
    return 0;
}
