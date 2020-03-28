#pragma once
#include<SFML/System.hpp>

class Food
{
private:
	sf::Vector2f _coordinates;
	
public:
	sf::Vector2f getCoordinates();
	void setCoordinates();
};