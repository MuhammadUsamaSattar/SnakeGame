#include"Snake.h"
#include<SFML/Window/Keyboard.hpp>
#include<SFML/System.hpp>

void snake::initialize()
{
	_bodycoordinates[0] = { 24,13 };
}

void snake::setDirection()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		_direction = { 0,-1 };
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		_direction = { 0,1 };
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

int snake::getLength()
{
	return _snakeLength;
}

void snake::setCoordinates()
{
	for (int i = _snakeLength-1; i > 0; i--)
		_bodycoordinates[i] = _bodycoordinates[i-1];
	_bodycoordinates[0] += _direction;
}

sf::Vector2i snake::getCoordinates(int i)
{
	return _bodycoordinates[i];
}

void snake::reset()
{
	_snakeLength = 1;
	_bodycoordinates[0] = { 24,13 };
	_direction = { 0,-1 };
}

bool snake::deathCondition()
{
	bool a = false;
	for (int i = 0; i < _snakeLength - 3; i++)
		if (_bodycoordinates[0] == _bodycoordinates[i+3])
			a = true;
	return a;
}