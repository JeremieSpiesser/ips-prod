/**
 * @file phi.cpp
 */

#include "../headers/phi.h"

/**
 * The Object Phi is responsable of calculating the formula of Scrondinger.
 * The constructor method takes three paramaters that are mainly used to create the vector Z.
 *
 * @param min: Indicates the value of the lower bound of the vector.
 * @param max: Indicates the value of the upper bound of the vector.
 * @param n_vals: Number of value between min and max
 * @param n_iter: Number of iterations of wave function
 */
Phi::Phi(int min, int max, int n_vals, int n_iter): min(min), max(max), n_vals(n_vals),
    n_iter(n_iter) {}

/**
 * The Destructor is a special method that de-allocate the memory when the object is destroyed.
 */
Phi::~Phi() = default;


/**
 * Z getter
 * @return Z
 */
arma::vec
Phi::getZ()
{
    return Z;
}

/**
 * Results getter
 * @return Results
 */
arma::mat
Phi::getResults()
{
    return M % hermite;
}

/**
 * M getter
 * @return M
 */
arma::mat
Phi::getM()
{
    return M;
}

/**
 * Min getter
 * @return Min
 */
double
Phi::getMin() const
{
    return min;
}

/**
 * Max getter
 * @return Max
 */
double
Phi::getMax() const
{
    return max;
}

/**
 * n_vals getter
 * @return n_vals
 */
int
Phi::getNVals() const
{
    return n_vals;
}

//methods
/**
 * This method creates a vector Z which an attribute of The Class Phi of n real that are in the interval min and max.
 * (n, min and max are Class Phi attributes).
 */
void
Phi::fill_Z()
{
    Z = arma::linspace(min, max, n_vals);
}

/**
 * The first term method consist in calculating the first part of our formula wich is a composition of 3 functions: Power, Sqrt and factorial.
 * @param i The iteration to compute
 * @return Returns the result calculated of the 1/sqrt(pow(2, n) * factorial(n)) where n is a Class Phi attribute.
 */
double
Phi::firstTerm(int i)
{
    return 1.0 / (sqrt(pow(2, i)) * factorial(i));
}

/**
 * This method applies the squared and exponential functions to each element of our vector Z.
 */
arma::vec
Phi::secondTerm()
{
    return arma::exp((-1.0 / 2.0) * arma::square(Z));
}

/**
 * Multiplies each value of the Z vector with the result of firstTerm method.
 */
void
Phi::calculateAll()
{
    M = arma::mat(n_iter, n_vals);
    arma::vec temp;

    for (int i = 0; i < n_iter; i++ )
        M.row(i) = firstTerm(i) * secondTerm().t();
}

/**
 * Set the Hermite Polynomial in cache
 *
 * @param herm Represents the result of Polgen class (Hermite polynomial).
 * @return Returns the multiplication of Phi result and Polgen result.
 */
void
Phi::setHermite(const arma::mat &herm)
{
    hermite = herm;
}

/**
 * Calculates the factorial of the given parameter
 * @param n The given value to which we want to calculate the factorial.
 * @return The result of factorial computation.
 */
double
Phi::factorial(int n)
{
    double res = 1;

    for (int i = 1 ; i <= n ; ++i)
        res *= i;

    return res;
}