#include <iostream>
#include <armadillo>
#include "../headers/poly.h"
#include "../headers/basis.h"
#include "../headers/nuclear.h"
#include "../headers/exporter.h"

int main()
{
        std::cout << "       -=-=[ Testing new class layout ]=-=-" << std::endl;
        Poly pol;
        arma::vec XorR = arma::linspace(-10, 10, 32);
        arma::vec Y = arma::linspace(-10, 10, 32);
        arma::vec Z = arma::linspace(-20, 20, 64);

        Nuclear nuclear(XorR, Z, 1.935801664793151, 2.829683956491218, 14, 1.3);

        arma::wall_clock timer;
        timer.tic();
        arma::mat res = nuclear.optiCalc();
        std::cout << timer.toc() << " secondes pour l'algorithme naif" << std::endl;


        Exporter exporter(res, XorR, Y, Z);
        exporter.toDf3("pres/visu/visu.df3");
        exporter.toRaw("pres/visu/visu.raw");

        // Exportation pour la visualisation 2d, avec un maillage plus fin
        arma::vec XorR_plotly = arma::linspace(-10, 10, 64);
        arma::vec Y_plotly = arma::linspace(-10, 10, 64);
        arma::vec Z_plotly = arma::linspace(-20, 20, 128);

        Nuclear nuclear_plotly(XorR_plotly, Z_plotly, 1.935801664793151, 2.829683956491218, 14, 1.3);
        arma::mat res_plotly = nuclear_plotly.optiCalc();
        Exporter exporter_plotly(res_plotly, XorR_plotly, Y_plotly, Z_plotly);
        exporter_plotly.toCsv("pres/visu/visu.csv");

        return 0;
}
