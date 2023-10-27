#pragma once
#include <fstream> 
#include <iostream> 
#include <vector>
#include <string>
using namespace std;

class DriverScore
{
private:
	vector<string> drivers;
	vector<int> driversPoints;

	int calculatePuntuation(const vector<int>&);

public:
	DriverScore();
	void loadPuntuation();
	void loadDriverData(int, ifstream&, int);
	void parseRaceResults(string&, int&, vector<int>&);
	void printPuntuation();
};