#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct location {
public:
	location(
		string northing_X,
		string easting_Y,
		string crashSeverity,
		string region,
		string weatherA) {
		Northing = northing_X;
		Easting = easting_Y;
		CrashSeverity = crashSeverity;
		Region = region;
		Weather = weatherA;

	}

	void display() {
		cout << "  Northing: " << Northing << endl;
		cout << "  Easting: " << Easting << endl;
		cout << "  CrashSeverity: " << CrashSeverity << endl;
		cout << "  Region: " << Region << endl;
		cout << "  Weather: " << Weather << endl;
	}

	string Northing;
	string Easting;
	string CrashSeverity;
	string Region;
	string Weather;


};



int main() {
	//ifstream myFile("scorpts_crash_data.csv");
//	cout << "file exists";
//	if (myFile.fail()) {
		//File does not exist code here
//		cout << "file exists";
//	}
//	else {
//		cout << "file does not exist";
//	}
	ifstream inputFile;
	inputFile.open("../Nelson_updated.csv");
	vector<location> locations;
	string line = "";
	getline(inputFile, line);
	while (getline(inputFile, line)) {
		string northing_X;
		string easting_Y;
		string crashSeverity;
		string region;
		string weatherA;

		stringstream inputString(line);

		getline(inputString, northing_X,',');
		getline(inputString, easting_Y, ',');
		getline(inputString, crashSeverity, ',');
		getline(inputString, region, ',');
		getline(inputString, weatherA, ',');


		location loc(northing_X, easting_Y, crashSeverity, region, weatherA);
		locations.push_back(loc);


		line = "";

	}
	for (auto loc : locations) {
		loc.display();
	}
	return 0;
}