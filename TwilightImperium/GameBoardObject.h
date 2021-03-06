#ifndef GAME_BOARD_OBJECT_H
#define GAME_BOARD_OBJECT_H

#include "Graphics.h"
#include "Image.h"
#include "TIParser.h"
#include "UtilityClasses.h"

#include <string>
#include <map>

class GameBoardObject
{

protected:
	enum LayerEnum { SystemLayer, PlanetLayer, PlayerLayer, CommandCounterLayer, MenuLayer};
	TupleInt _graphicalPos;
	float _scale = 1.0;
	GraphicsNS::Image* _image;
	const int _objectId;
	static GraphicsNS::Graphics* _g;

	static GameBoardObject* _selectedObject;
	static const int _numberOfLayers; //TODO s�tt denna beroende p� antalet i LayerEnum
	const LayerEnum _layer;

	//Objects graphical position
	static const TupleInt _gameMapPos;
	static const TupleInt _unitPosInTile;
	static const TupleInt _passButtonPos;
	static const TupleInt _menuPos;
	
	static const TupleInt _playerSheetPos;
	static const TupleInt _playerSheetSize;

private:
	static int _latestObjectId;
	static std::map<int, GameBoardObject*> _gameBoardObjects;
	const float _selectecObjectScalingFactor = 1.15f;

public:
	static void DrawAllObjects();
	void DrawSelectedObject();

	static void SetGraphics(HWND* hWnd);

	// Beskriver var kartan �r p� sk�rmen
	static TupleInt GetGameMapPos();

	TupleInt GetGraphicalPos() const;
	int GetObjectID() const;

	void SetGraphicalPos(TupleInt);
	void SetImageScale(float);
	void Save(TIParserNS::ListNode**) const;

	//TODO ska denna funktion vara s� l�tt att n�? Beh�vs funktionen?
	//static void CleanUpGameObjectMap(); 

protected:
	GameBoardObject();
	GameBoardObject(TupleInt, GraphicsNS::Image*, LayerEnum);
	GameBoardObject(TupleInt, TupleInt, std::string, LayerEnum);
	virtual ~GameBoardObject();

	void SetImage(std::string, TupleInt);
	virtual void DrawObject();

private:
	bool PosInObject(TupleInt);

	friend class GameBoard;
};

#endif // ! GAME_BOARD_OBJECT_H

