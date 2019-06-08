#ifndef MENU_H
#define MENU_H

#include "GameBoardObject.h"

class Menu : public GameBoardObject
{
public:
	static const GameBoardObject::LayerEnum _layerValue;

	enum MenuState { NoMenu, MoveUnits };

private:
	static const TupleInt _imageSize;
	const int _frameSize = 5;

	MenuState _menuState = NoMenu;

public:
	Menu();
	Menu& operator=(const Menu&);
	Menu(Menu const&);

	~Menu();

	void SetMenuState(MenuState);

private:
	void CopyMenu(Menu const&);
	void DrawObject();
};

#endif // !MENU_H