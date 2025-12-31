#include <iostream>
#include <vector>
#include <string>

#include "CSVReader.hpp"
#include "Returns.hpp"
#include "Statistics.hpp"
#include "ParallelCovariance.hpp"
#include "PortfolioRisk.hpp"
#include "Annualization.hpp"
#include "Timer.hpp"

int main() {
    try {
        // ================================
        // 1. Read price data
        // ================================
        CsvReader reader("close_prices.csv");
        PriceData priceData = reader.readData();

        std::cout << "Loaded data for "
                  << priceData.closePrices.size()
                  << " assets\n";

        // ================================
        // 2. Compute returns for each asset
        // ================================
        std::vector<std::string> assetNames;
        std::vector<std::vector<double>> returns;

        for (const auto& [asset, prices] : priceData.closePrices) {
            assetNames.push_back(asset);
            returns.push_back(
                Returns::calculateReturns(prices)
            );
        }

        // ================================
        // 3. Asset-level statistics
        // ================================
        std::cout << "\nAsset statistics (daily):\n";
        for (size_t i = 0; i < returns.size(); ++i) {
            double mean = Statistics::calculateMean(returns[i]);
            double vol  = Statistics::calculateVolatility(returns[i]);

            std::cout << assetNames[i]
                      << " | mean: " << mean
                      << " | vol: " << vol
                      << "\n";
        }

        // ================================
        // 4. Covariance (parallel)
        // ================================
        Matrix covariance;
        {
            Timer t("Parallel covariance computation");
            covariance =
                ParallelCovariance::calculateCovarianceMatrix(returns);
        }

        // ================================
        // 5. Annualize covariance
        // ================================
        Matrix annualCov =
            Annualization::annualizeCovarianceMatrix(covariance);

        // ================================
        // 6. Portfolio risk
        // ================================
        size_t n = returns.size();
        std::vector<double> weights(n, 1.0 / n); // equal-weighted

        double portVol = PortfolioRisk::calculatePortfolioVolatility(weights, annualCov);

        std::cout << "\nPortfolio annualized volatility: "
                  << portVol << "\n";

        std::cout << "\nProgram completed successfully.\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
