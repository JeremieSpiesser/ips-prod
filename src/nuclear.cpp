#include "../headers/nuclear.h"
#include "../headers/basis.h"

//
// Created by Nitorac on 18/11/2020.
//

Nuclear::Nuclear(arma::vec r, arma::vec z, double br, double bz, double N, double Q): r(r), z(z), basis(Basis(br, bz, N, Q)) {
    rhoMat.load("rho.arma", arma::arma_ascii);
}

double
Nuclear::rho(int m, int n, int n_z, int mp, int np, int n_zp) {
    return rhoMat(basis.rhoIndex(m, n, n_z), basis.rhoIndex(mp, np, n_zp));
}

arma::mat
Nuclear::naiveCalc(){
    arma::mat result = arma::zeros(r.n_elem, z.n_elem); // number of points on r- and z- axes
    for (int m = 0; m < basis.mMax; m++)
    {
        for (int n = 0; n < basis.nMax(m); n++)
        {
            for (int n_z = 0; n_z < basis.n_zMax(m, n); n_z++)
            {
                for (int mp = 0; mp < basis.mMax; mp++)
                {
                    for (int np = 0; np < basis.nMax(mp); np++)
                    {
                        for (int n_zp = 0; n_zp < basis.n_zMax(mp, np); n_zp++)
                        {
                            arma::mat funcA = basis.basisFunc( m,  n,  n_z, z, r);
                            arma::mat funcB = basis.basisFunc(mp, np, n_zp, z, r);
                            result += funcA % funcB * rho(m, n, n_z, mp, np, n_zp); // mat += mat % mat * double
                        }
                    }
                }
            }
        }
    }
    return result;
}

arma::mat
Nuclear::opti1Calc(){
    arma::mat result = arma::zeros(r.n_elem, z.n_elem); // number of points on r- and z- axes
    for (int m = 0; m < basis.mMax; m++)
    {
        for (int n = 0; n < basis.nMax(m); n++)
        {
            arma::vec rpart1 = basis.rPart(r,m,n);
            for (int n_z = 0; n_z < basis.n_zMax(m, n); n_z++)
            {
                arma::vec zpart1 = basis.zPart(z,n_z) ;

                for (int np = 0; np < basis.nMax(m); np++)
                {
                    for (int n_zp = 0; n_zp < basis.n_zMax(m, np); n_zp++)
                    {
                        //arma::mat funcA = basis.basisFunc( m,  n,  n_z, zVals, rVals);
                        arma::mat funcA = zpart1 * rpart1.t();
                        //arma::mat funcB = basis.basisFunc(m, np, n_zp, zVals, rVals);
                        arma::mat funcB = basis.zPart(z,n_zp) * basis.rPart(r,m,np).t();
                        result += funcA % funcB * rho(m, n, n_z, m , np, n_zp); // mat += mat % mat * double
                    }
                }
            }
        }
    }
    return result;
}
