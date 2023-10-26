#include "DriverScore.h"

using namespace std;

int main()
{
	DriverScore* driversScore = new DriverScore();
	driversScore->loadPuntuation();
	driversScore->printPuntuation();
}