#ifndef MENU_H
#define MENU_H

#include "GameBoardObject.h"
#include "UnitStack.h"

class Menu : public GameBoardObject
{
public:
	static const GameBoardObject::LayerEnum _layerValue;

	enum MenuState { NoMenu, MoveUnits };

private:
	static const TupleInt _imageSize;
	const int _frameSize = 5;
	const int _yDist = 30;

	MenuState _menuState = NoMenu;
	UnitStack* _sourceUnitStack = NULL;
	UnitStack* _destUnitStack = NULL;
	UnitStack _movingUnitStack;

public:
	Menu();
	Menu& operator=(const Menu&);
	Menu(Menu const&);

	~Menu();

	void SetMenuState(MenuState);
	MenuState GetMenuState() const;

	void SetUnitStackPointer(UnitStack*, UnitStack*);
	void Pressed(TupleInt);

private:
	void CopyMenu(Menu const&);
	void DrawObject();

	void DrawUnitStack(UnitStack*, int, int) const;
};

#endif // !MENU_H