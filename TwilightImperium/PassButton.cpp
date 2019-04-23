#include "PassButton.h"

std::string PassButton::_imagePath = "GameBoard/PassButton.png";
const TupleInt PassButton::_imageSize = TupleInt(66, 20);

PassButton::PassButton() :
	GameBoardObject(_passButtonPos, _imageSize, _imagePath)
{}

PassButton& PassButton::operator=(const PassButton& passButton)
{
	return *this;
}

PassButton::~PassButton()
{};

void PassButton::Action(GameBoardObject* gbo)
{
	Player* activePlayer = static_cast<Player*>(gbo);
	activePlayer->SetToPassed();
}

void PassButton::SetGraphicalPosBasedOnPlayer(Player* currentPlayer)
{
	_graphicalPos = TupleInt(_passButtonPos.GetX(), _passButtonPos.GetY() + _playerSheetSize.GetY()*currentPlayer->GetPosInPlayerOrder());
}