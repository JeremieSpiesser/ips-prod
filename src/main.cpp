#include <iostream>
#include <armadillo>
#include "../headers/poly.h"
#include "../headers/basis.h"

int
main()
{
    std::cout << "       -=-=[ Testing new class layout ]=-=-" << std::endl;
    Poly pol;
    arma::vec z({1, 2, 3, 4, 5, 6});
    pol.calcHermite(10, z);
    pol.hermite(2).print("A");
    Basis bFunc(5.0, 4.0, 1.0, 1.0);

    bFunc.zPart(z, 4).print("Z");

    std::cout << std::endl << "       -=-=[ Testing basis truncation ]=-=-" << std::endl;
    Basis b(1.935801664793151, 2.829683956491218, 14, 1.3);

    return 0;
}
