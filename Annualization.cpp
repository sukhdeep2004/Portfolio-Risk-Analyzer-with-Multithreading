#include "Annualization.hpp"
#include <cmath>

double Annualization::annualizeMean(double meanReturn, int periodsPerYear) {
    return meanReturn * periodsPerYear;
}
double Annualization::annualizeVolatility(double volatility, int periodsPerYear) {
    return volatility * std::sqrt(periodsPerYear);
}

Matrix Annualization::annualizeCovarianceMatrix(const Matrix& covarianceMatrix, int periodsPerYear) {

    Matrix annualizedMatrix = covarianceMatrix;

    for(auto& row : annualizedMatrix) {
        for(auto& value : row) {
            value *= periodsPerYear;
        }
    }

    return annualizedMatrix;
}