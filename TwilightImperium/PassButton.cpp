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

void PassButton::SetGraphicalPosBasedOnPlayer(int playerPos)
{
	_graphicalPos = TupleInt(_passButtonPos.GetX(), _passButtonPos.GetY() + _playerSheetSize.GetY()*playerPos);
}