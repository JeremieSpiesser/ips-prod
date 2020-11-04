#include <cxxtest/TestSuite.h>
#include "../headers/polgen.h"

class PolgenTest : public CxxTest::TestSuite
{
public:
    arma::vec z = {1., 2., 3., 4.};
    arma::mat correct = {
        {1., 1., 1., 1.},
        {2., 4., 6., 8.},
        {2., 14., 34., 62.},
        {-4., 40., 180., 464.},
    };
    arma::mat gen = Polgen::getPolFromZVec(z, 4);

    void
    testN0(void) {
        TS_TRACE("Checking Hermite polynom for n=0");
        TS_ASSERT(arma::norm(gen.row(0) - correct.row(0)) < 0.0000000001);
    }

    void
    testN1(void) {
        TS_TRACE("Checking Hermite polynom for n=1");
        TS_ASSERT(arma::norm(gen.row(1) - correct.row(1)) < 0.0000000001);
    }

    void
    testN(void) {
        TS_TRACE("Checking Hermite polynom for n=2 et n=3");
        TS_ASSERT(arma::norm(gen.row(2) - correct.row(2)) < 0.0000000001);
        TS_ASSERT(arma::norm(gen.row(3) - correct.row(3)) < 0.0000000001);
    }
};