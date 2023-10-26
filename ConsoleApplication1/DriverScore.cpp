#include "DriverScore.h"
DriverScore::DriverScore() {}

void DriverScore::loadPuntuation()
{
	string fileName = "pilotos_clasificaciones.txt";
	ifstream fich(fileName);
	if (!fich.is_open())
	{
		cout << "Error al abrir " << fileName << "\n";
		exit(EXIT_FAILURE);
	}

	string n_carreras;
	getline(fich, n_carreras);//se lee del documento la primera línea y se convierte su valor de texto a entero con atoi (ANSI to integer)
	int num_carreras = atoi(n_carreras.c_str());

	string n_pilotos;
	getline(fich, n_pilotos);//baja a leer la segunda linea del archivo para obtener la cantidad de pilotos
	int num_pilotos = atoi(n_pilotos.c_str());

	drivers.clear();  // Por si vienen con datos a la función
	driversPoints.clear();

	for (int i = 0; i < num_pilotos; ++i)
	{
		string piloto;
		getline(fich, piloto);
		drivers.push_back(piloto);//agarra el piloto y lo sube al vector
		vector<int> puestos;

		int puesto;
		string s_puestos;

		getline(fich, s_puestos);
		for (int j = 0; j < num_carreras; ++j)
		{
			int pos = 0;
			while ((pos = s_puestos.find(" ") != string::npos) || (pos = s_puestos.find(";") != string::npos)) {//espacio entre carrera
				if (pos == string::npos)
					pos = s_puestos.find(";");//espacio para siguiente piloto
				if (pos != string::npos) {
					puesto = atoi(s_puestos.substr(0, pos).c_str());
					s_puestos.erase(0, pos + 1);//se elimina de la cadena de puestos el dato extraído
					puestos.push_back(puesto);
				}
			}
		}
		driversPoints.push_back(calculatePuntuation(puestos));
	}
}

int DriverScore::calculatePuntuation(const vector<int>& places)
{

	const vector<int> puntos{ 10, 8, 6, 5, 4, 3, 2, 1 };

	int sum = 0;
	for (auto place : places)
		if (place > 0 && place < puntos.size() + 1)
			sum += puntos[place - 1];
	return sum;
}


void DriverScore::printPuntuation()
{
	cout << "\nActual Drivers Puntuation:\n\n";
	for (int index = 0; index < drivers.size(); ++index)
		cout << drivers[index] << ":" << driversPoints[index] << endl;
	cout << endl << endl;
}