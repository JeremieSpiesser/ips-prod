//
// Created by nostra on 03/10/2020.
//

#ifndef IPS_CLIPARSER_TEST_PHI_H
#define IPS_CLIPARSER_TEST_PHI_H

#include <cxxtest/TestSuite.h>
#include <armadillo>
#include "../headers/phi.h"

class TestPhi : public CxxTest :: TestSuite
{
public :

    void
    testFill_Z() {
        int min = -10, max = 10, n_vals = 150, n_iter = 9;
        Phi p(min, max, n_vals, n_iter);
        p.fill_Z();
        TS_ASSERT(p.getZ().size() != 0);
        TS_ASSERT(p.getZ()(0) >= min);
        TS_ASSERT(p.getZ()(p.getZ().size() - 1) <= max);

        for (int i = 1; i < n_vals - 1; i++)
            TS_ASSERT(min < p.getZ()(i) && p.getZ()(i) < max);

        TS_TRACE("Test Fill_Z() accomplished!");
    }

    void
    testFirstTerm() {
        int min = -10, max = 10, n_vals = 150, n_iter = 9;
        Phi p(min, max, n_vals, n_iter);
        p.fill_Z();
        double s = (sqrt(pow(2, 1)) * p.factorial(1));
        double a = (1.0 / s);
        double res = p.firstTerm(1);
        TS_ASSERT(a == res);
        TS_TRACE("Test firstTerm() accomplished!");
    }

    void
    testSecondTerm() {
        int min = -10, max = 10, n_vals = 150, n_iter = 9;
        Phi p(min, max, n_vals, n_iter);
        p.fill_Z();
        int index = rand() % n_vals - 1;
        double value = exp(((-1.0 / 2.0) * std::pow(p.getZ()(index), 2)));
        TS_ASSERT( p.secondTerm()(index) == value);
        TS_TRACE("Test secondTerm() accomplished!");
    }

    void
    testCalculateAll() {
        int min = -10, max = 10, n_vals = 150, n_iter = 9;
        Phi p(min, max, n_vals, n_iter);
        p.fill_Z();
        int index_vals = rand() % n_vals;
        int index_iter = rand() % n_iter;
        double x = p.getZ()(index_vals);
        x = std::exp(((-1.0 / 2.0) * std::pow(x, 2)));
        x = p.firstTerm(index_iter) * x;
        p.calculateAll();
        TS_ASSERT( p.getM()(index_iter, index_vals) == x);
        TS_TRACE("Test calculateAll() accomplished!");
    }

    void
    testFactorial() {
        int min = -10, max = 10, n_vals = 150, n_iter = 9;
        Phi p(min, max, n_vals, n_iter);
        //    TS_ASSERT(p.factorial(5) == 120);
        TS_ASSERT(p.factorial(1) == 1);
        TS_ASSERT(p.factorial(0) == 1);
        TS_TRACE("Test factorial() accomplished!");
    }

};
#endif //IPS_CLIPARSER_TEST_PHI_H
