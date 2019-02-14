#ifndef DRAW_H
#define DRAW_H

#include <vector>
#include <string>
#include <algorithm>

#include "Graphics.h"
//#include "Map.h"
#include "Player.h"

class Draw
{
public:
	struct DrawInput
	{
		//Map* map;
		Player* player;
	};
private:
	GraphicsNS::Graphics* _g;

public:
	Draw() {};
	Draw(HWND*);
	~Draw() {};

	void DrawScreen(DrawInput*);
	GraphicsNS::Graphics* GetGraphics();

private:
	//void DrawMap(Map*, Player*);	
};

#endif // !DRAW_H