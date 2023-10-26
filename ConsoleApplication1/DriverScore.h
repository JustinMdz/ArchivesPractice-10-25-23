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

	void function1(ifstream&);
	void function2(int, string&, int&, vector<int>&);

public:
	DriverScore();
	void loadPuntuation();
	void printPuntuation();
};