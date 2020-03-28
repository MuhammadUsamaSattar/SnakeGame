#pragma once
#include<SFML/System.hpp>

class snake
{
private:
	sf::Vector2f _direction, _bodycoordinates[64];
	int _snakeLength;

public:
	void initialize();
	void setDirection();
	sf::Vector2f getDirection();
	void setLength(int i);
	int getLength();
	void setCoordinates();
	sf::Vector2f getCoordinates(int i);
	void reset();
	bool deathCondition();
};