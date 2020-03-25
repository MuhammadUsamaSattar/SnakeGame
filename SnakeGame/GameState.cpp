#include"GameState.h"


void gameState::setState(std::string a)
{
	if (a == "menu")
		state = 0;
	else if (a == "game")
		state = 1;
	else state = -1;
}

int gameState::getState()
{
	return state;
}