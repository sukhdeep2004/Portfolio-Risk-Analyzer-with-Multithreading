#include "Statistics.hpp"
#include <cmath>
#include <stdexcept>
double Statistics::calculateMean(const std::vector<double>& data) {
    if (data.empty()) {
        throw std::runtime_error("Cannot compute mean of empty data");
    }

    double sum = 0.0;
    for (const auto& value : data) {
        sum += value;
    }
    return sum / data.size();
}

double Statistics::calculateVariance(const std::vector<double>& data) {
   if (data.size() < 2) {
        throw std::runtime_error("Need at least two points for variance");
    }
   double mean = calculateMean(data);
   double sum = 0.0;
   for(const auto& value: data){
    sum+=std::pow(value-mean,2);
   }
   return sum / (data.size() - 1);
}

double Statistics::calculateVolatility(const std::vector<double>& data) {
    return std::sqrt(calculateVariance(data));
}

double Statistics::calculateCovariance(const std::vector<double>& x, const std::vector<double>& y) {
    if(x.size() != y.size() || x.size() < 2) {
        throw std::runtime_error("Vectors must be of same size and contain at least two elements");
    }
    double meanX = calculateMean(x);
    double meanY = calculateMean(y);
    double cov = 0.0;
    for(size_t i = 0; i < x.size(); ++i) {
        cov += (x[i] - meanX) * (y[i] - meanY);
    }
    return cov / (x.size() - 1);
}

Matrix Statistics::calculateCovarianceMatrix(const std::vector<std::vector<double>>& returns) {
    size_t n = returns.size();
    Matrix covMatrix(n, std::vector<double>(n, 0.0));
    for(size_t i = 0; i < n; ++i) {
        for(size_t j = i; j < n; ++j) {
            double cov = calculateCovariance(returns[i], returns[j]);
            covMatrix[i][j] = cov;
            covMatrix[j][i] = cov; // Symmetric matrix
        }
    }
    return covMatrix;
}
Matrix Statistics::calculateCorrelationMatrix(const std::vector<std::vector<double>>& returns) {
    size_t n = returns.size();
    Matrix corrMatrix(n, std::vector<double>(n, 0.0));
    for(size_t i = 0; i < n; ++i) {
        double volI = calculateVolatility(returns[i]);
        for(size_t j = i; j < n; ++j) {
            double volJ = calculateVolatility(returns[j]);
            double cov = calculateCovariance(returns[i], returns[j]);
            double corr = cov / (volI * volJ);
            corrMatrix[i][j] = corr;
            corrMatrix[j][i] = corr; // Symmetric matrix
        }
    }
    return corrMatrix;
}