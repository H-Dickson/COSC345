#include "location.h"
#include <fstream>
#include <sstream>
#include <iostream>

Location::Location(
    const std::string& northing_X,
    const std::string& easting_Y,
    const std::string& crashSeverity,
    const std::string& region,
    const std::string& weatherA
) : Northing(northing_X), Easting(easting_Y), CrashSeverity(crashSeverity), Region(region), Weather(weatherA) {}

void Location::display() {
    std::cout << "  Northing: " << Northing << std::endl;
    std::cout << "  Easting: " << Easting << std::endl;
    std::cout << "  CrashSeverity: " << CrashSeverity << std::endl;
    std::cout << "  Region: " << Region << std::endl;
    std::cout << "  Weather: " << Weather << std::endl;
}

std::vector<Location> readDataFromFile(const std::string& filename) {

    std::ifstream inputFile;
    inputFile.open(filename);
    std::vector<Location> locations;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file '" << filename << "'" << std::endl;
        return locations;
    }

    std::string line = "";
    getline(inputFile, line); // Read and discard the header line

    while (getline(inputFile, line)) {
        std::string northing_X;
        std::string easting_Y;
        std::string crashSeverity;
        std::string region;
        std::string weatherA;

        std::stringstream inputString(line);

        getline(inputString, northing_X, ',');
        getline(inputString, easting_Y, ',');
        getline(inputString, crashSeverity, ',');
        getline(inputString, region, ',');
        getline(inputString, weatherA, ',');

        Location loc(northing_X, easting_Y, crashSeverity, region, weatherA);
        locations.push_back(loc);

        line = "";
    }

    inputFile.close();
    return locations;
}
