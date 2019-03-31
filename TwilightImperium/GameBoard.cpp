#include "GameBoard.h"

GameBoard::GameBoard()
{
	_gameMap = GameMap();
	_gameMap.CreateGameMap();
}

GameBoard::~GameBoard()
{
}

void GameBoard::Draw()
{
	GameBoardObject::DrawAllObjects();
}

std::map<TupleInt, MapTile> GameBoard::GetMapMap()
{
	return _gameMap.GetMap();
}