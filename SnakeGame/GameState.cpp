#include"GameState.h"


void gameState::setState(std::string a)
{
	if (a == "menu")
		_state = 0;
	else if (a == "game")
		_state = 1;
	else _state = -1;
}

int gameState::getState()
{
	return _state;
}