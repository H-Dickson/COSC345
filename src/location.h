#pragma once
#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>

struct Location {
    std::string Northing;
    std::string Easting;
    std::string CrashSeverity;
    std::string Region;
    std::string Weather;

    Location(
        const std::string& northing_X,
        const std::string& easting_Y,
        const std::string& crashSeverity,
        const std::string& region,
        const std::string& weatherA
    );

    void display();
};

std::vector<Location> readDataFromFile(const std::string& filename);

#endif // LOCATION_H
