#include "PortfolioRisk.hpp"
#include <stdexcept>
#include <cmath>
#include <numeric>

double PortfolioRisk::calculatePortfolioVariance(const std::vector<double>& weights, const Matrix& covMatrix) {
    if (weights.size() != covMatrix.size()) {
        throw std::runtime_error("Weights size must match covariance matrix size");
    }
    double sumWeights =
        std::accumulate(weights.begin(), weights.end(), 0.0);

    if (std::abs(sumWeights - 1.0) > 1e-6) {
        throw std::runtime_error("Weights must sum to 1");
    }
    double variance = 0.0;
    for (size_t i = 0; i < weights.size(); ++i) {
        for (size_t j = 0; j < weights.size(); ++j) {
            variance += weights[i] * weights[j] * covMatrix[i][j];
        }
    }
    return variance;
}
double PortfolioRisk::calculatePortfolioVolatility(const std::vector<double>& weights, const Matrix& covMatrix) {
    return std::sqrt(calculatePortfolioVariance(weights, covMatrix));
}