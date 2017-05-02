#pragma once

#include <string>
#include <vector>

struct Weather
{
public:
						Weather(std::string weather);

public:
	std::string			stationId;

	struct Time
	{
		int set(const std::string& v);
		std::string day;
		std::string timestamp;
	}time;

	struct Wind
	{
		int set(const std::string& v);
		int direction;
		int speed;
		bool gust;
		int gustSpeed;
		std::string unit;
	}wind;

	struct Visibility
	{
		int set(const std::string& v);
		int coverage;
		unsigned int height;
	}visibility;

	std::string temperature;
	std::string dewpoint;
	std::string seaLevelPressure;
	std::string raw;

private:
	std::vector<std::string>	split(const std::string& input, const std::string& regex);
};
