#include "MyApp.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
struct CrashData {
    int northing;
    int easting;
    std::string crashSeverity;
    int crashYear;
    std::string weatherA;
};
int main() {
    AllocConsole();

    // Redirect standard input and output to the console
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);

    // Output a message to the console
    std::cout << "Console message: Starting the application..." << std::endl;

    // Create an instance of MyApp
    MyApp app;

    // Run the app
    app.Run();

    // Free the console and close it
    FreeConsole();

    // Output a message to the standard console (not the redirected one)
    std::cout << "Program finished" << std::endl;

    return 0;
}
