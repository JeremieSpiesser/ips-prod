#include <iostream>
#include <armadillo>
#include <utility>
#include "../headers/poly.h"

int
main()
{
    std::cout << "       -=-=[ Testing new class layout ]=-=-" << std::endl;
    Poly pol;
    arma::vec z({1, 2, 3, 4, 5, 6});
    pol.calcHermite(10, z);
    pol.hermite(2).print("A");
    return 0;
}
