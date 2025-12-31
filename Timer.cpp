#include "Timer.hpp"

#include<iostream>

Timer::Timer(const std::string& label)
    : label_(label),
      start_(std::chrono::high_resolution_clock::now()) {}
Timer::~Timer() {
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start_);

    std::cout << label_ << " took "<< duration.count() << " ms\n";
}