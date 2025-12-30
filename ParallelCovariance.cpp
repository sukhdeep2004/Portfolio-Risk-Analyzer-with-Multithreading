#include "ParallelCovariance.hpp"
#include "Statistics.hpp"

#include <thread>
#include <vector>
#include <stdexcept>
Matrix ParallelCovariance::calculateCovarianceMatrix(const std::vector<std::vector<double>>& returns) {
    // Placeholder for parallel correlation matrix calculation
    size_t n = returns.size();
    Matrix covMatrix(n, std::vector<double>(n, 0.0));
    if(n == 0) {
        throw std::runtime_error("Empty return set");
    }
    auto worker =[&](size_t i){
        double mean_i = Statistics::calculateMean(returns[i]);
        for(size_t j=i;j<n;j++){
            double mean_j = Statistics::calculateMean(returns[j]);
            double accum = 0.0;
            for (size_t k = 0; k < returns[i].size(); ++k) {
                accum += (returns[i][k] - mean_i) *
                         (returns[j][k] - mean_j);
            }

            double value = accum / (returns[i].size() - 1);
            covMatrix[i][j] = value;
            covMatrix[j][i] = value; // symmetry
        }
    };\
    std::vector<std::thread> threads;
    threads.reserve(n);
    for(size_t i=0;i<n;i++){
        threads.emplace_back(worker,i);
    }
    for(auto& t: threads){
        t.join();
    }
    return covMatrix;
}