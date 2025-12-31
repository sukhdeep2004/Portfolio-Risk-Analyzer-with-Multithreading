#pragma once
#include <vector>

using Matrix = std::vector<std::vector<double>>;

class Annualization {
    public:
        static double  annualizeMean(double meanReturn, int periodsPerYear=252);
        static Matrix annualizeCovarianceMatrix(const Matrix& covarianceMatrix, int periodsPerYear=252);
        static double  annualizeVolatility(double volatility, int periodsPerYear=252);
};