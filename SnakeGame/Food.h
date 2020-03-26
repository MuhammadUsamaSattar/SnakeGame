#pragma once
#include<SFML/System.hpp>

class Food
{
private:
	sf::Vector2i _coordinates;
	
public:
	sf::Vector2i getCoordinates();
	void setCoordinates();
};