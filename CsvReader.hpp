#pragma once

#include <string>
#include <vector>
#include <unordered_map>

struct PriceData {
    std::vector<std::string> dates;
    std::unordered_map<std::string, std::vector<double>> closePrices;
};

class CsvReader{
    public:
        explicit CsvReader(const std::string& filename);
        PriceData readData();
    private:
        std::string filename_;
};