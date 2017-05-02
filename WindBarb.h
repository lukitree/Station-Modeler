#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class WindBarb : public sf::Drawable, public sf::Transformable
{
public:
	WindBarb(int speed, float size);

private:
	virtual void draw(sf::RenderTarget& rt, sf::RenderStates states)const;

private:
	sf::RectangleShape					staff;
	std::vector<sf::RectangleShape>		barbs;
};

