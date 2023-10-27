#include "DriverScore.h"
DriverScore::DriverScore() {}

void DriverScore::loadPuntuation()
{
	try {
		string fileName = "pilotos_clasificaciones.txt";
		ifstream fich(fileName);
		if (!fich.is_open())
		{
			cout << "Error al abrir " << fileName << "\n";
			throw runtime_error("No se pudo abrir el archivo");
		}

		string n_carreras;
		getline(fich, n_carreras);
		int num_carreras = atoi(n_carreras.c_str());

		string n_pilotos;
		getline(fich, n_pilotos);
		int num_pilotos = atoi(n_pilotos.c_str());

		drivers.clear();
		driversPoints.clear();

		loadDriverData(num_pilotos, fich, num_carreras);
	}
	catch (const ifstream::failure& e) {
		cerr << "Error de lectura/escritura en el archivo: " << e.what() << endl;
	}
	catch (const runtime_error& e) {
		cerr << "Error: " << e.what() << endl;
	}
	catch (const exception& e) {
		cerr << "Error inesperado: " << e.what() << endl;
	}
}

void DriverScore::loadDriverData(int numOfDrivers, ifstream& fich, int numOfRaces)
{
	for (int index = 0; index < numOfDrivers; ++index)
	{
		string driver;
		getline(fich, driver);
		drivers.push_back(driver);//agarra el piloto y lo sube al vector
		vector<int> places;

		int place;
		string s_Place;

		getline(fich, s_Place);
		for (int index = 0; index < numOfRaces; ++index)
		{
			parseRaceResults(s_Place, place, places);
		}
		driversPoints.push_back(calculatePuntuation(places));
	}
}

void DriverScore::parseRaceResults(std::string& s_puestos, int& puesto, std::vector<int>& puestos)
{
	int positionInRace = 0;
	while ((positionInRace = s_puestos.find(" ") != string::npos) || (positionInRace = s_puestos.find(";") != string::npos)) {//espacio entre carrera
		if (positionInRace == string::npos)
			positionInRace = s_puestos.find(";");//espacio para siguiente piloto
		if (positionInRace != string::npos) {
			puesto = atoi(s_puestos.substr(0, positionInRace).c_str());
			s_puestos.erase(0, positionInRace + 1);//se elimina de la cadena de puestos el dato extraído
			puestos.push_back(puesto);
		}
	}
}

int DriverScore::calculatePuntuation(const vector<int>& places)
{

	const vector<int> points{ 10, 8, 6, 5, 4, 3, 2, 1 };

	int sum = 0;
	for (auto place : places)
		if (place > 0 && place < points.size() + 1)
			sum += points[place - 1];
	return sum;
}

void DriverScore::printPuntuation()
{
	cout << "\nActual Drivers Puntuation:\n\n";
	for (int index = 0; index < drivers.size(); ++index)
		cout << drivers[index] << ":" << driversPoints[index] << endl;
	cout << endl << endl;
}