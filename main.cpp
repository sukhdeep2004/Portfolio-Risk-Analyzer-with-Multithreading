#include "CsvReader.hpp"
#include "Returns.hpp"
#include <iostream>
int main()
{
    CsvReader reader("close_prices.csv");
    PriceData data = reader.readData();
    for (const auto& [asset, prices] : data.closePrices) {
        auto returns = Returns::calculateReturns(prices);
        std::cout << "Returns size for " << asset << ":\n";
        std::cout << "Number of returns calculated: " << returns.size() << "\n";
    }
    return 0;
}
