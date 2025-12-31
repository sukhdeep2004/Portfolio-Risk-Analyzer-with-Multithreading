#pragma once

#include <chrono>
#include <string>

class Timer{
    public:
        explicit Timer(const std::string& label);
        ~Timer();
    private:
        std::string label_;
        std::chrono::high_resolution_clock::time_point start_;
};
