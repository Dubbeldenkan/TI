#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "GameBoardObject.h"
#include "GameMap.h"
#include "PassButton.h"
#include "Player.h"

class GameBoard
{
private:
	GameMap _gameMap;
	PassButton _passButton;

public:
	GameBoard();
	~GameBoard();

	void CleanUpGameBoard();
	void Draw();
	void Run(Player*);
	TIParserNS::ListNode* Save() const;
	void Load(TIParserNS::ListNode*);

	const GameMap* GetGameMap() const;

	static std::vector<GameBoardObject*> GetGameBoardObjectByPosition(TupleInt);
};

#endif // !GAME_BOARD_H