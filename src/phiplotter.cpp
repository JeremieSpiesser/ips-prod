/**
 *  @file phiplotter.cpp
 */


#include <string>
#include "../headers/phiplotter.h"


/**
 * The Object PhiPlotter exports the results of the computations, done by the Phi passed as argument
 * @param p: The Phi function which has done all the computations
 */

PhiPlotter::PhiPlotter(Phi p) : phi(p)
{
}
/**
 * Exports the results of the calculations done by the Phi object given when constructing the object
 *
 * @param results name of the csv file containing the results (if unsure put "results")
 * @param points name of the csv file containing all the z points (if unsure put "points")
 * @return
 */
void
PhiPlotter::exportResults(std::string results = "results",
                          std::string points = "points")
{
    arma::mat resultsMatrix = phi.getResults();
    resultsMatrix.save(results + ".csv", arma::csv_ascii);
    arma::mat z = phi.getZ();
    z.save(points + ".csv", arma::csv_ascii);
}

