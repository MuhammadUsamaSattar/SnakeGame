#pragma once
#include<SFML/System.hpp>

class snake
{
private:
	sf::Vector2i _direction = {0,1};
	int _snakeLength;
	sf::Vector2i _bodycoordinates[64];

public:
	void initialize();
	void setDirection();
	sf::Vector2i getDirection();
	void setLength(int i);
	int getLength();
	void setCoordinates();
	sf::Vector2i getCoordinates(int i);
	void reset();
	bool deathCondition();
};