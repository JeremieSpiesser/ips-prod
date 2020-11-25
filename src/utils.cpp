//
// Created by Nitorac on 15/11/2020.
//

#include "../headers/utils.h"

/**
 * Computes a factorial
 *@param n : the nth factorial
 *@returns n!
 */
double
Utils::fact(int n) {
    double res = 1.0;
    for(int i = 1; i <= n; i++){
        res *= i;
    }
    return res;
}
