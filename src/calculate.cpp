// calculate.cpp

#include "Calculate.h"
#include "location.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <iomanip>
#include <locale>
#include <codecvt>

int count;
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double EarthRadius = 6371000.0; // Earth's radius in meters

    // Convert latitude and longitude from degrees to radians
    lat1 = lat1 * M_PI / 180.0;
    lon1 = lon1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;
    lon2 = lon2 * M_PI / 180.0;

    // Haversine formula
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    // Calculate the distance
    double distance = EarthRadius * c;
    return distance;
}

void findClosePoints(const std::vector<Location>& locations, double targetX, double targetY) {
    int left = 0;
    int right = locations.size() - 1;

    // Use binary search to find the approximate midpoint
    while (left < right) {
        int mid = left + (right - left) / 2;
        const Location& midLoc = locations[mid];

        // Check if midLoc.Easting is greater than targetY
        if (std::stod(midLoc.Easting) > targetY) {
            right = mid - 1; // Adjust the right boundary
        }
        else {
            left = mid + 1;  // Adjust the left boundary
        }
    }

    // Now, 'left' points to the approximate midpoint

    // Search the lower half of the CSV
    for (int i = 0; i <= left; ++i) {
        const Location& loc = locations[i];
        double distance = calculateDistance(std::stod(loc.Northing), std::stod(loc.Easting), targetX, targetY);

        if (distance < 20.0) { // Check if the distance is less than 20 meters
            count++;
            std::cout << "Point (" << loc.Northing << ", " << loc.Easting << ") is close to the target point." << std::endl;
        }
    }

    // Search the upper half of the CSV
    for (int i = left + 1; i < locations.size(); ++i) {
        const Location& loc = locations[i];
        double distance = calculateDistance(std::stod(loc.Northing), std::stod(loc.Easting), targetX, targetY);

        if (distance < 20.0) { // Check if the distance is less than 20 meters
            count++;
            std::cout << "Point (" << loc.Northing << ", " << loc.Easting << ") is close to the target point." << std::endl;
        }
    }
}

 std::string MyCalculator::CalculateArea(const std::string& lat, const std::string& lon, std::vector<Location> loc) {
        // Implement area calculation logic here
        // You can use the provided latitude (lat) and longitude (lon) strings
        findClosePoints(loc, std::stod(lon), std::stod(lat));
        std::cout << "Hello from Calculate Area" << std::endl;
        std::cout << "latitude: " << lat << "Longitude" << lon << std::endl;
        // Example: Calculate area and return it
        
        return std::to_string(count);
    }

