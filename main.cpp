#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>

#include "Weather.h"
#include "Metar.h"
#include "StationModel.h"
#include "PageGenerator.h"


int main()
{
	// Create working directories
	std::system("mkdir temp\\data temp\\images");
	std::system("cls");

	std::cout << std::endl << "    Station Modeler v1.0" << std::endl << "      Edward Jenco" << std::endl << std::endl;
	for (int i = 0; i < 80; ++i)
		std::putchar('-');

	// Load list of station IDs
	std::vector<std::string> station_ids;
	bool load_new_data = false;
	std::ifstream ids_file("station.cfg");
	if (!ids_file.is_open())
		station_ids.push_back("KSLC");
	else
	{
		std::string line;
		std::getline(ids_file, line);
		int val = stoi(line);

		if (val == 0) load_new_data = false;
		else if (val == 1) load_new_data = true;

		while (std::getline(ids_file, line))
			station_ids.push_back(line);
	}

	ids_file.close();

	// Download METAR data and
	std::vector<Metar> metars;

	for (const auto& station : station_ids)
	{
		Metar metar(station);
		metar.downloadMetarData(load_new_data);
		metars.push_back(metar);
	}

	std::cout << std::endl << std::endl;

	// Generate station model images
	for (auto& m : metars)
	{
		Weather weather(m.getData());
		StationModel model(weather);
		std::cout << std::endl;
	}

	// Generate webpage to display images
	PageGenerator pg("temp\\gen.html", station_ids);
	std::system("start temp\\gen.html");
	std::system("pause");

	return 0;
}