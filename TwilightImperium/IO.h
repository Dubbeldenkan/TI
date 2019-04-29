#ifndef IO_H
#define IO_H

#include <Windows.h>

#include "Game.h"
#include "UtilityClasses.h"

class IO
{
#define SCREENXSIZE 1200
#define SCREENYSIZE 800

private:
	static Game* _game;

public:
	IO();
	~IO() {};

	void InitIO(Game*);
	void EndGame();

	static LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);
	static void SetKeyAction(Game* game, bool keyDown, WPARAM);

private:
	static void MouseClick(int, int);
	static void MouseMove(int, int);
};

void InitWinMain(HINSTANCE*, std::string, IO*);

HWND InitWindow(HINSTANCE*, std::string, IO*);

#endif // !CONTROL_H