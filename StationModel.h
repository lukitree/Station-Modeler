#pragma once

#include <SFML/Graphics.hpp>
#include "Weather.h"

class StationModel
{
public:
								StationModel(Weather& w);

private:
	void						draw_sky_cover();
	void						draw_temp();
	void						draw_dewpoint();
	void						draw_sea_level_pressure();
	void						draw_wind();
	void						draw_timestamp();
	void						draw_raw();

private:
	sf::RenderTexture			texture;
	Weather						weather;

	sf::Vector2f				center;

	sf::Font					famirids;
	sf::Font					expressway_rg;

	const int					station_model_size = 300;
	const float					sky_cover_radius = 15.f;
};

