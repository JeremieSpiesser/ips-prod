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

    void testNuclearIsCorrect(void) {
        arma::vec XorR{2.903226, -4.838710, -2.258065, 6.774194};
        arma::vec Z{5.396825, -6.666667, 0.952381, 7.301587};

        Nuclear nuclear(XorR, Z, 1.935801664793151, 2.829683956491218, 14, 1.3);

        arma::mat opti = nuclear.optiCalc();

        TS_ASSERT_DELTA(opti(0, 0), 0.149483, 1e-5);
        TS_ASSERT_DELTA(opti(1, 1), 0.042846, 1e-5);
        TS_ASSERT_DELTA(opti(2, 2), 0.146820, 1e-5);
        TS_ASSERT_DELTA(opti(3, 3), 0.001511, 1e-5);
    }
};