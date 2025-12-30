#pragma once
#include <vector>

using Matrix = std::vector<std::vector<double>>;

class ParallelCovariance {
    public:
        static Matrix calculateCovarianceMatrix(const std::vector<std::vector<double>>& returns);
};