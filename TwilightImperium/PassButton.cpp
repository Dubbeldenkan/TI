#include "PassButton.h"

std::string PassButton::_imagePath = "GameBoard/PassButton.png";
const TupleInt PassButton::_imageSize = TupleInt(66, 20);
const GameBoardObject::LayerEnum PassButton::_layerValue = GameBoardObject::PlayerLayer;

PassButton::PassButton() :
	GameBoardObject(_passButtonPos, _imageSize, _imagePath, _layerValue)
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