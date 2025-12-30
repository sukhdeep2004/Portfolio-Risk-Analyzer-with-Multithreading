#include "Statistics.hpp"
#include <iostream>

int main() {
    std::vector<std::vector<double>> returns = {
        {0.01, -0.02, 0.015},
        {0.008, -0.01, 0.02},
        {0.012, -0.025, 0.01}
    };

    Matrix cov = Statistics::calculateCovarianceMatrix(returns);
    Matrix corr = Statistics::calculateCorrelationMatrix(returns);

    std::cout << "Covariance[0][1]: " << cov[0][1] << "\n";
    std::cout << "Correlation[0][1]: " << corr[0][1] << "\n";
}
