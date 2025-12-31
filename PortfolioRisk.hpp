#pragma once
#include <vector>

using Matrix = std::vector<std::vector<double>>;
class PortfolioRisk {
    public:
        static double calculatePortfolioVariance(const std::vector<double>& weights, const Matrix& covMatrix);
        static double calculatePortfolioVolatility(const std::vector<double>& weights, const Matrix& covMatrix);
};