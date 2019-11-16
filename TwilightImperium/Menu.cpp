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

Menu::MenuState Menu::GetMenuState() const
{
	return _menuState;
}

void Menu::SetUnitStackPointer(UnitStack* sourceUnitStack, UnitStack* destUnitStack)
{
	_sourceUnitStack = sourceUnitStack;
	_destUnitStack = destUnitStack;
}

void Menu::DrawObject()
{
	switch (_menuState)
	{
	case NoMenu:
		break;
	case MoveUnits:
	{
		_movingUnitStack = UnitStack::UnitStack();

		_g->DrawRectangle(_graphicalPos.GetX() - _frameSize, _graphicalPos.GetY() - _frameSize, 
			_imageSize.GetX() + 2*_frameSize, _imageSize.GetY() + 2*_frameSize, GraphicsNS::Graphics::WHITE);
		
		_g->DrawRectangle(_graphicalPos.GetX(), _graphicalPos.GetY(), _imageSize.GetX()/3 - _frameSize, 
			_imageSize.GetY(), GraphicsNS::Graphics::BLACK);
		_g->PrintText15("Source system:", _graphicalPos.GetX(), _graphicalPos.GetY(), GraphicsNS::Graphics::WHITE);
		DrawUnitStack(_sourceUnitStack, _graphicalPos.GetX(), _graphicalPos.GetY());

		_g->DrawRectangle(_graphicalPos.GetX() + _imageSize.GetX() / 3 + _frameSize, _graphicalPos.GetY(), 
			_imageSize.GetX() / 3 - _frameSize, _imageSize.GetY(), GraphicsNS::Graphics::BLACK);
		_g->PrintText15("Moving units:", _graphicalPos.GetX() + _imageSize.GetX() / 3 + _frameSize, 
			_graphicalPos.GetY(), GraphicsNS::Graphics::WHITE);
		DrawUnitStack(&_movingUnitStack, _graphicalPos.GetX() + _imageSize.GetX() / 3 + _frameSize, _graphicalPos.GetY());

		_g->DrawRectangle(_graphicalPos.GetX() + 2*_imageSize.GetX() / 3 + _frameSize, _graphicalPos.GetY(), 
			_imageSize.GetX() / 3 - _frameSize, _imageSize.GetY(), GraphicsNS::Graphics::BLACK);
		_g->PrintText15("Destination system:", _graphicalPos.GetX() + 2*_imageSize.GetX() / 3 + _frameSize,
			_graphicalPos.GetY(), GraphicsNS::Graphics::WHITE);
		DrawUnitStack(_destUnitStack, _graphicalPos.GetX() + 2*_imageSize.GetX() / 3 + _frameSize, _graphicalPos.GetY());
		
		_g->DrawRectangle(_graphicalPos.GetX() + _frameSize, _graphicalPos.GetY() + _imageSize.GetY() - _frameSize - _yDist,
			_imageSize.GetX() / 3 - 3*_frameSize, _yDist, GraphicsNS::Graphics::GREEN);
		_g->PrintText15("OK", _graphicalPos.GetX() + _frameSize, _graphicalPos.GetY() + _imageSize.GetY() - _frameSize - _yDist,
			GraphicsNS::Graphics::WHITE);

		break;
	}
	default:
		break;
	}
}

void Menu::DrawUnitStack(UnitStack* unitStack, int xPos, int yPos) const
{
	yPos += _yDist;
	for (int unitTypeInt = 0; unitTypeInt < unitStack->GetNumberOfUnitsTypes(); unitTypeInt++)
	{
		yPos += _yDist;
		UnitStack::UnitType unitType = static_cast<UnitStack::UnitType>(unitTypeInt);
		int numberOfUnits = unitStack->GetAmountOfAUnitType(unitType);
		_g->PrintText15(unitStack->GetUnitString(unitType) + ":   " + std::to_string(numberOfUnits), 
			xPos, yPos, GraphicsNS::Graphics::WHITE);
	}
}

void Menu::Pressed(TupleInt clickedPos)
{
	int yPos = _graphicalPos.GetY() + _frameSize + 2*_yDist;
	int xPos = _graphicalPos.GetY() + _frameSize;
	if (((_graphicalPos.GetX() + _frameSize) < clickedPos.GetX()) &&
		((_graphicalPos.GetY() + _imageSize.GetY() - _frameSize - _yDist) < clickedPos.GetY()) &&
		( clickedPos.GetX() < _graphicalPos.GetX() + _imageSize.GetX()) &&
		(clickedPos.GetY() < _graphicalPos.GetY() + _imageSize.GetY() - _frameSize))
	{
		_destUnitStack->AddUnits(&_movingUnitStack);
		_movingUnitStack.Reset();
		_menuState = NoMenu;
	}
	else
	{
		for (int unitTypeInt = 0; unitTypeInt < _destUnitStack->GetNumberOfUnitsTypes(); unitTypeInt++)
		{
			if (yPos < clickedPos.GetY() && clickedPos.GetY() < yPos + _yDist)
			{
				if (xPos < clickedPos.GetX() && clickedPos.GetX() < (xPos + +_imageSize.GetX() / 3))
				{
					if (_sourceUnitStack->AddUnits(static_cast<UnitStack::UnitType>(unitTypeInt), -1))
					{
						_movingUnitStack.AddUnits(static_cast<UnitStack::UnitType>(unitTypeInt), 1);
					}
				}
				else if ((xPos < clickedPos.GetX() + _imageSize.GetX() / 3) && clickedPos.GetX() < (xPos + +2 * _imageSize.GetX() / 3))
				{
					if (_movingUnitStack.AddUnits(static_cast<UnitStack::UnitType>(unitTypeInt), -1))
					{
						_sourceUnitStack->AddUnits(static_cast<UnitStack::UnitType>(unitTypeInt), 1);
					}
				}
				break;
			}
			yPos += _yDist;
		}
	}
}