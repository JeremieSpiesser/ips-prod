#include <iostream>
#include <armadillo>
#include "../headers/poly.h"
#include "../headers/basis.h"
#include "../headers/nuclear.h"
#include "../headers/exporter.h"

int main()
{
    std::string df3Path = "pres/visu/visu.df3";
    std::string rawPath = "pres/visu/visu.raw";
    std::string csvPath = "pres/visu/visu.csv";


    std::cout << "    -=-=[ Launching computation of a local nuclear density ]=-=-" << std::endl;
    Poly pol;
    arma::vec XorR = arma::linspace(-10, 10, 32);
    arma::vec Y = arma::linspace(-10, 10, 32);
    arma::vec Z = arma::linspace(-20, 20, 64);

    Nuclear nuclear(XorR, Z, 1.935801664793151, 2.829683956491218, 14, 1.3);

    arma::wall_clock timer;
    timer.tic();
    arma::mat res = nuclear.naiveCalc();
    std::cout << std::endl << timer.toc() << " seconds for the naive computation" << std::endl;

    timer.tic();
    arma::mat res2 = nuclear.optiCalc();
    std::cout << timer.toc() << " seconds for the optimized computation" << std::endl << std::endl;

    std::cout << "Exporting to " << df3Path << " and " << rawPath << std::endl;
    Exporter exporter(res, XorR, Y, Z);
    exporter.toDf3(df3Path);
    exporter.toRaw(rawPath);

    std::cout << std::endl <<
              "    -=-=[ Launching a second computation more precise for the 2D display ]=-=-" << std::endl;
    // Exportation pour la visualisation 2d, avec un maillage plus fin
    arma::vec XorR_plotly = arma::linspace(-10, 10, 64);
    arma::vec Y_plotly = arma::linspace(-10, 10, 64);
    arma::vec Z_plotly = arma::linspace(-20, 20, 128);

    Nuclear nuclear_plotly(XorR_plotly, Z_plotly, 1.935801664793151, 2.829683956491218, 14, 1.3);
    arma::mat res_plotly = nuclear_plotly.optiCalc();
    std::cout << "Exporting to " << csvPath << std::endl;

    Exporter exporter_plotly(res_plotly, XorR_plotly, Y_plotly, Z_plotly);
    exporter_plotly.toCsv(csvPath);

    std::cout << std::endl << "Computation successfully ended !" << std::endl;
    std::cout << "Exported files are :" << std::endl;
    std::cout << " - DF3: " << df3Path << std::endl;
    std::cout << " - RAW: " << rawPath << std::endl;
    std::cout << " - CSV: " << csvPath << std::endl;
    return 0;
}
