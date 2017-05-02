#include "Weather.h"

#include <regex>
#include <iostream>
#include <map>


Weather::Weather(std::string weather)
{
	raw = weather;
	std::cout << weather << std::endl << "-------------------------" << std::endl;
	std::vector<std::string> values = split(weather, "\\s+");

	stationId = values[0];
	time.set(values[1]);
	wind.set(values[2]);

	std::vector<std::string> cloud_vis_list;

	for (auto& el : values)
	{
		if (el == "CAVOK" ||
			el.substr(0, 2) == "VV" ||
			el.substr(0, 3) == "CLR" ||
			el.substr(0, 3) == "SKC" ||
			el.substr(0, 3) == "FEW" ||
			el.substr(0, 3) == "SCT" ||
			el.substr(0, 3) == "BKN" ||
			el.substr(0, 3) == "OVC")
		{
			cloud_vis_list.push_back(el);
		}
	}

	for (auto& el : cloud_vis_list)
	{
		visibility.set(el);
	}

	for (const auto& el : values)
	{
		if (el.find("SLP") != std::string::npos)
		{
			seaLevelPressure = el.substr(3, 3);
			std::cout << "SLP  | " << seaLevelPressure << std::endl;
		}
		else if (int pos = el.find("/") != std::string::npos)
		{
			temperature = el.substr(0, pos + 1);
			dewpoint = el.substr(pos + 2, 3);

			std::cout << "TEMP | " << temperature << std::endl;
			std::cout << "DEWP | " << dewpoint << std::endl;
		}
	}
}

int Weather::Time::set(const std::string & v)
{
	if (v.length() != 7)
	{
		std::cout << "Time Length: " << v.length() << " " << v << std::endl;
		return -1;
	}

	day = v.substr(0, 2);

	std::string hh = v.substr(2, 2);
	std::string mm = v.substr(4, 2);

	timestamp = hh + ":" + mm + v[6];

	std::cout << "TIME | " << day << " " << timestamp << std::endl;

	return 0;
}

int Weather::Wind::set(const std::string & v)
{
	if (v.length() == 7)
	{
		gust = false;
		gustSpeed = -1;
		unit = v.substr(5, 2);
	}
	else if (v.length() == 10 && v[5] == 'G')
	{
		std::string gstspd = v.substr(6, 2);
		gust = true;
		gustSpeed = stoi(gstspd);
		unit = v.substr(8, 2);
	}
	else return -1;

	std::string dir = v.substr(0, 3);
	std::string spd = v.substr(3, 2);

	if (dir == "VRB")
	{
		direction = 0;
		speed = 0;
	}
	else
	{
		direction = stoi(dir);
		speed = stoi(spd);
	}

	std::cout << "WIND | " << direction << " " << speed << unit;
	if (gust) std::cout << " (" << gustSpeed << unit << ")";
	std::cout << std::endl;

	return 0;
}

int Weather::Visibility::set(const std::string & v)
{
	if (v.length() < 2 || v.length() > 6) return -1;

	std::string cov = v.substr(0, 3);
	std::string hgt = v.substr(3, 3);

	std::cout << "VISI | ";

	if (v == "CAVOK")
	{
		coverage = 0;
		height = -1;

		std::cout << "CAVOK" << std::endl;
	}
	else if (v.substr(0, 2) == "VV")
	{
		coverage = -1;
		height = -1;

		std::cout << "VV" << std::endl;
	}
	else if (v == "CLR" || v == "SKC")
	{
		coverage = 0;
		height = 0;

		std::cout << "CLR" << std::endl;
	}
	else
	{
		if(hgt.length() > 0)
			height = stoi(hgt) * 100;

		int c = 0;

		if (cov == "FEW") c = 1;
		else if (cov == "SCT") c = 2;
		else if (cov == "BKN") c = 3;
		else if (cov == "OVC") c = 4;
		else return -2;

		if (c > coverage) coverage = c;

		std::cout << cov << " " << height << "FT" << std::endl;
	}


	return 0;
}

std::vector<std::string> Weather::split(const std::string& input, const std::string& regex)
{
	std::regex re(regex);
	std::sregex_token_iterator
		first { input.begin(), input.end(), re, -1 },
		last;

	return { first, last };
}
