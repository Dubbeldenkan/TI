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