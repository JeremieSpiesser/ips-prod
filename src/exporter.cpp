/**
 * @file exporter.cpp
 */

#include "../headers/exporter.h"

/**
 * Construct the Exporter with a calculated nuclear density and 3 vectors \f$X, Y, Z\f$
 * corresponding to the linspace
 * @attention It requires the nuclear density to have been calculated with the same \f$X\f$ and \f$Z\f$ vector
 *
 * @param nuclearDensity The calculated nuclear density calculated with the Basis class
 * @param XorR The \f$X\f$ vector (which is the same as the \f$R\f$ because \f$\theta = 0\f$)
 * @param Y The \f$Y\f$ vector
 * @param Z The \f$Z\f$ vector
 */
Exporter::Exporter(const arma::mat& nuclearDensity, const arma::vec& XorR, const arma::vec& Y, const arma::vec& Z): XorR(XorR), Y(Y), Z(Z), nuclearDensity(nuclearDensity), euclidianDensity(arma::cube(XorR.size(), Y.size(), Z.size())){
    //On fait la révolution du plan (R=X,Z) nuclearDensity autour de l'axe Z dans le cube euclidianDensity
    //A partir de X et Y, on en déduit le rayon correspondant
    for (arma::uword i = 0 ; i < XorR.size() ; i++) {
        double x = XorR(i);
        for (arma::uword j = 0; j < Y.size(); j++) {
            double y = Y[j];

            // Le rayon qui correspond au X, Y
            double r = std::sqrt(x * x + y * y);

            // La recherche de l'indice de r
            // On cherche l'indice du rayon le plus proche des coordonnées X et Y
            euclidianDensity.tube(i, j) = nuclearDensity.row(arma::index_min(arma::abs(XorR - r)));
        }
    }
}

/**
 * Translates a cube in a df3 string readable by POV-Ray
 *
 * @param m The cube to translate
 * @return A string with contains the data to be written in a file
 */
std::string Exporter::cubeToDf3(const arma::cube &m)
{
    std::stringstream ss(std::stringstream::out | std::stringstream::binary);
    int nx = m.n_rows;
    int ny = m.n_cols;
    int nz = m.n_slices;
    ss.put(nx >> 8);
    ss.put(nx & 0xff);
    ss.put(ny >> 8);
    ss.put(ny & 0xff);
    ss.put(nz >> 8);
    ss.put(nz & 0xff);
    double theMin = 0.0;
    double theMax = m.max();
    for (uint k = 0; k < m.n_slices; k++)
    {
        for (uint j = 0; j < m.n_cols; j++)
        {
            for (uint i = 0; i < m.n_rows; i++)
            {
                uint v = 255 * (fabs(m(i, j, k)) - theMin) / (theMax - theMin);
                ss.put(v);
            }
        }
    }
    return ss.str();
}

/**
 * Translates a cube in a raw string readable by Blender
 *
 * @param m The cube to translate
 * @return A string with contains the data to be written in a file
 */
std::string Exporter::cubeToRaw(const arma::cube &m)
{
    std::stringstream ss(std::stringstream::out | std::stringstream::binary);
    double theMin = 0.0;
    double theMax = m.max();
    for (uint k = 0; k < m.n_slices; k++)
    {
        for (uint j = 0; j < m.n_cols; j++)
        {
            for (uint i = 0; i < m.n_rows; i++)
            {
                uint v = 255 * (fabs(m(i, j, k)) - theMin) / (theMax - theMin);
                ss.put(v);
            }
        }
    }
    return ss.str();
}

/**
 * Exports the 3D nuclear density into a .df3 file
 *
 * @param path The file path to be written
 */
void Exporter::toDf3(const std::string& path){
    std::ofstream file;
    file.open(path);
    file << cubeToDf3(euclidianDensity);
    file.close();
}

/**
 * Exports the 3D nuclear density into a .raw file
 *
 * @param path The file path to be written
 */
void Exporter::toRaw(const std::string& path){
    std::ofstream file;
    file.open(path);
    file << cubeToRaw(euclidianDensity);
    file.close();
}

/**
 * Exports the 2D nuclear density into a .csv file which is the concatenation of 3 csv separated with ';' on empty lines :
 *   - X vector
 *   - Z vector
 *   - Nuclear density matrix
 *
 * @param path The file path to be written
 */
void Exporter::toCsv(const std::string& path){
    std::ofstream file;
    file.open(path);
    XorR.save(file, arma::csv_ascii);
    file << ";" << std::endl;
    Z.save(file, arma::csv_ascii);
    file << ";" << std::endl;
    nuclearDensity.save(file, arma::csv_ascii);
    file.close();
}