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

const std::map<TupleInt, MapTile>* GameBoard::GetMapMap() const
{
	return _gameMap.GetMap();
}

std::vector<GameBoardObject*> GameBoard::GetGameBoardObjectByPosition(TupleInt position)
{
	std::vector<GameBoardObject*> objectVector;
	std::map<int, GameBoardObject*>::iterator it;
	for (it = GameBoardObject::_gameBoardObjects.begin(); it != GameBoardObject::_gameBoardObjects.end(); it++)
	{
		if (it->second->PosInObject(position))
		{
			int test = 0;
			objectVector.push_back(it->second);
		}
	}
	return objectVector;
}