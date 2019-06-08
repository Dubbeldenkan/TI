#include "Menu.h"

const GameBoardObject::LayerEnum Menu::_layerValue = GameBoardObject::MenuLayer;
const TupleInt Menu::_imageSize = TupleInt(700, 500);

Menu::Menu() : 
	GameBoardObject(_menuPos, _imageSize, "", _layerValue)
{}

Menu& Menu::operator=(const Menu& menu)
{
	CopyMenu(menu);
	return *this;
}

Menu::Menu(const Menu &menu) :
	GameBoardObject(menu._graphicalPos, menu._image, _layerValue)
{
	CopyMenu(menu);
}

void Menu::CopyMenu(const Menu& menu)
{

}

Menu::~Menu()
{}

void Menu::SetMenuState(MenuState menuState)
{
	_menuState = menuState;
}

void Menu::DrawObject()
{
	switch (_menuState)
	{
	case NoMenu:
		break;
	case MoveUnits:
	{
		_g->DrawRectangle(_graphicalPos.GetX() - _frameSize, _graphicalPos.GetY() - _frameSize, _imageSize.GetX() + 2*_frameSize,
			_imageSize.GetY() + 2*_frameSize, GraphicsNS::Graphics::WHITE);
		_g->DrawRectangle(_graphicalPos.GetX(), _graphicalPos.GetY(), _imageSize.GetX(), _imageSize.GetY(), GraphicsNS::Graphics::BLACK);
		//TODO fortsätt med menyn här
		break;
	}
	default:
		break;
	}
}