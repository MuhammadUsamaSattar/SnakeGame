#include<iostream>
#include"GameState.h"
#include"Snake.h"

int main()
{
	snake snake;
	snake.bodycoordinates[0] = { 3,5 };
	snake.bodycoordinates[1] = { 5,7 };
	snake.bodycoordinates[0] = snake.bodycoordinates[1];
	std::cout << "The coordiantes are " << snake.bodycoordinates[0].x << snake.bodycoordinates[0].y << std::endl;
	return 0;
}