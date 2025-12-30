#pragma once
#include <vector>

using Matrix = std::vector<std::vector<double>>;
class Statistics {
    public:
        static double calculateMean(const std::vector<double>& data);
        static double calculateVariance(const std::vector<double>& data);
        static double calculateVolatility(const std::vector<double>& data);

        static double calculateCovariance(const std::vector<double>& x, const std::vector<double>& y);
        static Matrix calculateCovarianceMatrix(const std::vector<std::vector<double>>& returns);

        static Matrix calculateCorrelationMatrix(const std::vector<std::vector<double>>& returns);
};