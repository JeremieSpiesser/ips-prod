//
// Created by Nitorac on 25/11/2020.
//

#include "../headers/exporter.h"

/**
 *
 * @param nuclearDensity
 * @param XequalR
 * @param Y
 * @param Z
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

void Exporter::toDf3(const std::string& path){
    std::ofstream file;
    file.open(path);
    file << cubeToDf3(euclidianDensity);
    file.close();
}

void Exporter::toRaw(const std::string& path){
    std::ofstream file;
    file.open(path);
    file << cubeToRaw(euclidianDensity);
    file.close();
}

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