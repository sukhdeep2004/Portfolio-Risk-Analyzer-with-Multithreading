#include "CsvReader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

CsvReader::CsvReader(const std::string& filename) : filename_(filename) {}

PriceData CsvReader::readData() {
    PriceData data;
    std::ifstream file(filename_);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename_);
    }
    std::string line;

    // Read 
    std::getline(file, line);
    std::stringstream header(line);
    std::string column;
    std::vector<std::string> assetNames;
    // Skip date column
    std::getline(header, column, ',');
    while (std::getline(header, column, ',')) {
        assetNames.push_back(column);
        data.closePrices[column] = std::vector<double>();
    }
    
    // Read data rows
    while (std::getline(file, line)) {
        std::stringstream row(line);
        std::string date;
        std::getline(row, date, ',');
        data.dates.push_back(date);
        for (const auto& asset : assetNames) {
            std::string priceStr;
            std::getline(row, priceStr, ',');
            if(priceStr.empty()){
                throw std::runtime_error("Missing price data for asset: " + asset + " on date: " + date);
            }  
            data.closePrices[asset].push_back(std::stod(priceStr));      
        }
    }
    return data;
}

