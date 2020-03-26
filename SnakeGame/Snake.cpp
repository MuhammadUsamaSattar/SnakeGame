#include"Snake.h"
#include<SFML/Window/Keyboard.hpp>
#include<SFML/System.hpp>

void snake::setDirection()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		_direction = { 0,1 };
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		_direction = { 0,-1 };
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_direction = { 1,0 };
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_direction = { -1,0 };
}

sf::Vector2i snake::getDirection()
{
	return _direction;
}

void snake::setLength(int i)
{
	_snakeLength = i;
}

void snake::setCoordinates()
{
	for (int i = 0; i < _snakeLength; i++)
		_bodycoordinates[i + 1] = _bodycoordinates[i];
	_bodycoordinates[0] += _direction;
}