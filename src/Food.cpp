#include"Food.h"
#include<stdlib.h>
#include<time.h>


sf::Vector2f Food::getCoordinates()
{
	return _coordinates;
}

void Food::setCoordinates()
{
	srand(time(NULL()));
	_coordinates.x = (rand() % 48) + 1;
	_coordinates.y = (rand() % 27) + 1;
}