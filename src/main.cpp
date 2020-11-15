#include <iostream>
#include <armadillo>
#include "../headers/poly.h"
#include "../headers/basisFunc.h"

int
main()
{
    std::cout << "       -=-=[ Testing new class layout ]=-=-" << std::endl;
    Poly pol;
    arma::vec z({1, 2, 3, 4, 5, 6});
    pol.calcHermite(10, z);
    pol.hermite(2).print("A");
    BasisFunc bFunc(5.0, 4.0);

    bFunc.calcZ(z, 4).print("Z");

    return 0;
}
