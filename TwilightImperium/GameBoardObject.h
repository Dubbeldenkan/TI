#ifndef GAME_BOARD_OBJECT_H
#define GAME_BOARD_OBJECT_H

#include "Image.h"
#include "UtilityClasses.h"
#include "Graphics.h"

#include <string>
#include <map>

class GameBoardObject
{
protected:
	TupleInt _graphicalPos;
	double _scale = 1.0;
	GraphicsNS::Image _image;
	const int _objectId;
	static GraphicsNS::Graphics* _g;

private:
	static int _latestObjectId;
	static std::map<int, GameBoardObject*> _gameBoardObjects;

	//Objects graphical position
	static const TupleInt _mapPos;

public:
	static void DrawAllObjects();

	static void SetGraphics(HWND* hWnd);

	// Beskriver var kartan är på skärmen
	static TupleInt GetMapPos();

	void SetGraphicalPos(TupleInt);
	void SetImageScale(double);

protected:
	GameBoardObject();
	GameBoardObject(TupleInt, GraphicsNS::Image);
	GameBoardObject(TupleInt, TupleInt, std::string);
	~GameBoardObject();

	virtual void DrawObject();
};

#endif // ! GAME_BOARD_OBJECT_H

