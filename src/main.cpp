#include <iostream>
#include <armadillo>
#include <utility>
#include "../headers/phi.h"
#include "../headers/poly.h"
#include "../headers/schrodingerVerificator.h"
#include "../headers/phiplotter.h"


/**
 * Checks the energy levels and prints the progressive results of the Energy calculations
 */
void
energyLevels()
{
    int min = -8, max = 8, n_vals = 100000, n_iter = 9;
    Phi p(min, max, n_vals, n_iter);
    p.fill_Z();

    p.setHermite(Poly::getPolFromZVec(p.getZ(), n_iter));
    p.calculateAll();

    for (int i = 0; i < n_iter; i++) {
        double correctEn = i + 0.5;
        arma::vec en = SchrodingerVerificator::getEn(p, i);
        double maxGen = en.max();
        double minGen = en.min();

        double threshold = 0.004;

        std::cout << ((maxGen < correctEn + threshold
                       && minGen > correctEn - threshold) ? "PASS !" : "FAILED !") << " n=" << i << "  theoric=" <<
                  correctEn << "  average_calculated=" << arma::mean(en) << "  min=" << minGen << "  max=" << maxGen <<
                  std::endl;
    }
}

/**
 * Runs the complete calculations of the wave Function and exports the results
 * @param phi name of the first csv file containing the data of phi
 * @param z name of the second csv file containing all the points (a linspace)
 */
void
waveFunctions(std::string phi, std::string z)
{
    int min = -8, max = 8, n_vals = 250, n_iter = 10;
    Phi p(min, max, n_vals, n_iter);
    p.fill_Z();
    p.setHermite(Poly::getPolFromZVec(p.getZ(), n_iter));
    p.calculateAll();
    PhiPlotter resultsExport(p);
    resultsExport.exportResults(std::move(phi), std::move(z));
}

int
main()
{
    std::string phiCsv = "results";
    std::string zVecCsv = "points";
    std::cout << "       -=-=[ Generating wave functions ]=-=-" << std::endl;
    waveFunctions(phiCsv, zVecCsv);
    std::cout << "Wave functions generated ! (phi_plot=" << phiCsv << ".csv   z_vec=" << zVecCsv <<
              ".csv)" <<
              std::endl;
    std::cout << "       -=-=[ Checking energy levels ]=-=-" << std::endl;
    energyLevels();
    std::cout << "       -=-=[ Checking ortogonality ]=-=-" << std::endl;
    SchrodingerVerificator::orthogonality(15);
    return 0;
}
