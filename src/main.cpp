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

    return 0;
}
