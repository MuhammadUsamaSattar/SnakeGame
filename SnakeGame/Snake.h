#pragma once
#include<SFML/System.hpp>

class snake
{
private:
	sf::Vector2i _direction = {0,1};
	int _snakeLength;
	sf::Vector2i _bodycoordinates[64];

public:
	void setDirection();
	sf::Vector2i getDirection();
	void setLength(int i);
	void setCoordinates();
};