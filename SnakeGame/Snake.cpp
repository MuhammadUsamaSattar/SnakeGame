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

sf::Vector2f snake::getDirection()
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
	for (int i = _snakeLength; i > 0; i--)
		_bodycoordinates[i] = _bodycoordinates[i - 1];
	_bodycoordinates[0] = _bodycoordinates[0] + _direction;
	if (_bodycoordinates[0].x > 48) _bodycoordinates[0].x = 1;
	else if (_bodycoordinates[0].x < 1) _bodycoordinates[0].x = 48;
	else if (_bodycoordinates[0].y > 27) _bodycoordinates[0].y = 1;
	else if (_bodycoordinates[0].y < 1) _bodycoordinates[0].y = 27;
}

sf::Vector2f snake::getCoordinates(int i)
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
	for (int i = 1; i < _snakeLength; i++)
		if (_bodycoordinates[0] == _bodycoordinates[i])
			a = true;
	return a;
}