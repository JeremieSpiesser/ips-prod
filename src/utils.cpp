//
// Created by Nitorac on 15/11/2020.
//

#include "../headers/utils.h"

int
Utils::fact(int n) {
    int res = 1;
    for(int i = 1; i <= n; i++){
        res *= i;
    }
    return res;
}