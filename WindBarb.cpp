#include "WindBarb.h"

WindBarb::WindBarb(int speed, float size)
{
	//speed = 3;
	staff = sf::RectangleShape(sf::Vector2f(2, size));
	staff.setOrigin(staff.getSize().x / 2, staff.getSize().y);
	staff.setFillColor(sf::Color::Black);

	sf::RectangleShape barb(sf::Vector2f(10, 2));
	barb.setOrigin(0, barb.getSize().y / 2);
	barb.setFillColor(sf::Color::Black);
	barb.move(0, -staff.getSize().y);

	int barb_count = speed / 5;
	if (speed % 5 >= 2.5) barb_count += 1;

	if (barb_count < 1)
	{
		staff.setFillColor(sf::Color::Transparent);
	}
	else if (barb_count == 1)
	{
		barb.move(0, 10);
		barbs.push_back(barb);
	}
	else
	{
		for (int i = 1; i <= barb_count; ++i)
		{
			barbs.push_back(barb);
			if (i % 2 == 0) barb.move(-10, 10);
			else barb.move(10, 0);
		}
	}
}

void WindBarb::draw(sf::RenderTarget & rt, sf::RenderStates states) const
{
	states.transform *= getTransform();
	rt.draw(staff, states);
	for (int i = 0; i < barbs.size(); ++i)
	{
		rt.draw(barbs[i], states);
	}
}
