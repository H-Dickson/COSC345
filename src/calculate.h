#pragma once

#include <string>
#include <vector>
#include "location.h"
class MyCalculator {
public:
    // Function to calculate area based on latitude and longitude
    std::string CalculateArea(const std::string& lat, const std::string& lon, std::vector<Location> loc);
};
