#include "MyApp.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
struct CrashData {
    int northing;
    int easting;
    std::string crashSeverity;
    int crashYear;
    std::string weatherA;
};
int main() {
    MyApp app; // Create an instance of MyApp
    app.Run();
    return 0;
}
