#include <cxxtest/TestSuite.h>
#include <armadillo>
#include "../headers/nuclear.h"

class TestNuclear : public CxxTest::TestSuite
{
public:
    void testOptiIsCorrect(void) {
        arma::vec XorR = arma::linspace(-5, 5, 16);
        arma::vec Z = arma::linspace(-10, 10, 16);

        Nuclear nuclear(XorR, Z, 1.935801664793151, 2.829683956491218, 14, 1.3);

        arma::mat witness = nuclear.naiveCalc();
        arma::mat opti = nuclear.optiCalc();

        TS_ASSERT_DELTA(arma::norm(opti - witness), 0.0, 1e-15);
    }
};