#include "Metar.h"

#include <fstream>



Metar::Metar(std::string station_id)
{
	this->station_id = station_id;
}


Metar::~Metar()
{
}

void Metar::downloadMetarData(bool refresh)
{
	std::string filename = station_id + ".html";

	if (refresh)
	{
		// Download Data
		std::string cmd;
		cmd.append("resources\\curl.exe ");
		cmd.append("--max-time 5 ");
		cmd.append("\"http://aviationweather.gov/metar/data?ids=");
		cmd.append(station_id);
		cmd.append("&format=raw&hours=0&taf=off&layout=on&date=0\"");
		cmd.append(" > temp\\data\\");
		cmd.append(filename);

		std::system(cmd.c_str());
	}

	// Read HTML File
	std::ifstream station_file("temp\\data\\" + filename);
	if (station_file.is_open())
	{
		// Find METAR Data

		std::string line;
		std::string find_id = station_id + " ";

		while (std::getline(station_file, line))
		{
			if (line.find(find_id) != std::string::npos)
			{
				cleanup(line);
				data = line;
				station_file.close();
				return;
			}
		}
		station_file.close();
	}

	data = station_id + "(NO_DATA) 000000Z 00000KT 00SM CAVOK 00/00 A0000 RMK SLP000";
}

std::string Metar::getData() const
{
	return data;
}

void Metar::cleanup(std::string & string)
{
	int pos = string.find("<");
	if(pos != std::string::npos) string.erase(pos);

	pos = string.find("AUTO");
	if(pos != std::string::npos) string.erase(pos, 5);
}
