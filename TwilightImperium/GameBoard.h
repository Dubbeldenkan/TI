#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "GameBoardObject.h"
#include "GameMap.h"

#pragma once
class GameBoard
{
private:
	GameMap _gameMap;

public:
	GameBoard();
	~GameBoard();

	void Draw();

	const std::map<TupleInt, MapTile>* GetMapMap() const;
	static std::vector<GameBoardObject*> GetGameBoardObjectByPosition(TupleInt);
};

#endif // !GAME_BOARD_H