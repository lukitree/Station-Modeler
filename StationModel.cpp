#include "StationModel.h"

#include <iostream>

#include "WindBarb.h"


StationModel::StationModel(Weather& w)
	: weather(w)
{
	famirids.loadFromFile("resources/Famirids.ttf");
	expressway_rg.loadFromFile("resources/expressway-rg.ttf");

	texture.create(station_model_size, station_model_size - 75);
	center = sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2);
	texture.clear(sf::Color::White);
	draw_sky_cover();
	draw_temp();
	draw_dewpoint();
	draw_sea_level_pressure();
	draw_timestamp();
	draw_raw();
	draw_wind();
	texture.display();

	std::string filename = "temp\\images\\" + weather.stationId.substr(0,4) + ".png";

	texture.getTexture().copyToImage().saveToFile(filename);

	//sf::RenderWindow window(sf::VideoMode(texture.getSize().x, texture.getSize().y), "Preview");
	//window.clear(sf::Color::Black);
	//window.draw(sf::Sprite(texture.getTexture()));
	//window.display();

	//while (window.isOpen())
	//{
	//	sf::Event ev;
	//	while (window.pollEvent(ev))
	//	{
	//		if (ev.type == sf::Event::Closed)
	//			window.close();
	//		if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
	//			window.close();
	//	}
	//}
}

void StationModel::draw_sky_cover()
{
	int coverage = weather.visibility.coverage;
	sf::Color color = sf::Color::Blue;
	unsigned int points = 60;

	//  Outline
	sf::CircleShape cover_outline(sky_cover_radius, points);
	cover_outline.setOrigin(sky_cover_radius, sky_cover_radius);
	cover_outline.setPosition(center);
	cover_outline.setFillColor(sf::Color::Transparent);
	cover_outline.setOutlineThickness(3.f);
	cover_outline.setOutlineColor(color);

	// Draw Coverage
	sf::CircleShape fill = cover_outline;
	fill.setFillColor(color);
	texture.draw(fill);

	sf::RectangleShape cut(sf::Vector2f(sky_cover_radius, sky_cover_radius));
	cut.setFillColor(sf::Color::White);
	cut.setOrigin(cut.getSize());
	cut.setPosition(center);

	switch (coverage)
	{
		case 0:
			texture.draw(cut);
			cut.rotate(-90);
		case 1:
			texture.draw(cut);
			cut.rotate(-90);
		case 2:
			texture.draw(cut);
			cut.rotate(-90);
		case 3:
			texture.draw(cut);
			break;
	}

	// Draw Outline
	texture.draw(cover_outline);
}

void StationModel::draw_temp()
{
	sf::Text text(weather.temperature, famirids);
	text.setFillColor(sf::Color::Black);
	text.setPosition(center);
	text.move(-100, -60);

	texture.draw(text);
}

void StationModel::draw_dewpoint()
{
	sf::Text text(weather.dewpoint, famirids);
	text.setFillColor(sf::Color::Black);
	text.setPosition(center);
	text.move(-100, 20);

	texture.draw(text);
}

void StationModel::draw_sea_level_pressure()
{
	sf::Text text(weather.seaLevelPressure, famirids);
	text.setFillColor(sf::Color::Black);
	text.setPosition(center);
	text.move(50, -60);

	texture.draw(text);
}

void StationModel::draw_wind()
{
	WindBarb wind_barb = WindBarb(weather.wind.speed, sky_cover_radius * 4);
	wind_barb.setPosition(center);
	wind_barb.setRotation(weather.wind.direction);

	texture.draw(wind_barb);
}

void StationModel::draw_timestamp()
{
	sf::Text text(weather.stationId + "\nDay: " + weather.time.day + " Time: " + weather.time.timestamp, famirids);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color::Black);
	text.setPosition(5, 0);

	texture.draw(text);
}

void StationModel::draw_raw()
{
	int length = weather.raw.length() / 2;
	sf::Text text(weather.raw.substr(0, length) + '\n' + weather.raw.substr(length, length), expressway_rg);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(10);
	text.setPosition(5, texture.getSize().y - 30);

	texture.draw(text);
}
