#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "GameBoardObject.h"
#include "GameMap.h"

#pragma once
class GameBoard
{
public:
	GameBoard();
	~GameBoard();

	void Draw();

private:
	GameMap _gameMap;
};

#endif // !GAME_BOARD_H