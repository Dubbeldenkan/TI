#include "GameBoard.h"

GameBoard::GameBoard()
{
	_gameMap = GameMap();
	_gameMap.CreateGameMap();
	_passButton = PassButton();
}

void GameBoard::CleanUpGameBoard()
{
	_gameMap.CleanUpMap();
}

GameBoard::~GameBoard()
{
}

void GameBoard::Draw()
{
	GameBoardObject::DrawAllObjects();
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

void GameBoard::Run(Player* currentPlayer)
{
	_passButton.SetGraphicalPosBasedOnPlayer(currentPlayer->GetPosInPlayerOrder());
}

TIParserNS::ListNode* GameBoard::Save() const
{
	TIParserNS::ListNode* gameBoardNode = new TIParserNS::ListNode("GameBoard");

	//Map
	TIParserNS::ListNode* gameMapNode = _gameMap.Save();
	gameBoardNode->SetChild(gameMapNode);
	
	return gameBoardNode;
}

void GameBoard::Load(TIParserNS::ListNode* gameBoardNode)
{
	TIParserNS::ListNode* gameMapNode = NULL;
	gameBoardNode->GetChild(&gameMapNode);
	_gameMap.Load(gameMapNode);
}

const GameMap* GameBoard::GetGameMap() const
{
	return &_gameMap;
}