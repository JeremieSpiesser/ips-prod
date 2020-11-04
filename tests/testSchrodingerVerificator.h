//
// Created by user on 13/10/2020.
//

#ifndef IPS_CLIPARSER_TESTSCHRODINGERVERIFICATOR_H
#define IPS_CLIPARSER_TESTSCHRODINGERVERIFICATOR_H

#include "../headers/schrodingerVerificator.h"


class TestSchrodingerVerificator : public CxxTest::TestSuite
{
public:
    arma::vec a = {1., 2., 3., 4.};
    arma::vec da = {1., 1., 1.};
    arma::vec d2a = {0., 0.};


    arma::vec b = {1., 2., 4., 8.};
    arma::vec db = {1., 4., 4.};
    arma::vec d2b = {1., 8.};

    void
    testFirstDerivative(void) {
        TS_TRACE("Checking First Derivative");
        TS_ASSERT(arma::norm( SchrodingerVerificator::derivative(a, 1) - da) < 0.0000001 );
        TS_ASSERT(arma::norm( SchrodingerVerificator::derivative(b, 1) - db) > 0.0000001 );
    }

    void
    testSecondDerivative(void) {
        TS_TRACE("Checking second Derivative");
        TS_ASSERT(arma::norm( SchrodingerVerificator::derivative(SchrodingerVerificator::derivative(a, 1),
                              1) - d2a) < 0.0000001 );
        TS_ASSERT(arma::norm( SchrodingerVerificator::derivative(SchrodingerVerificator::derivative(b, 1),
                              1) - d2b) > 0.0000001 );
    }

};



#endif //IPS_CLIPARSER_TESTSCHRODINGERVERIFICATOR_H
