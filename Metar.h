#pragma once

#include <cstdlib>
#include <string>

class Metar
{
public:
							Metar(std::string station_id);
							~Metar();

public:
	void					downloadMetarData(bool refresh = true);

	std::string				getData()const;
	
private:
	void					cleanup(std::string& string);

private:
	std::string				data;
	std::string				station_id;

};

