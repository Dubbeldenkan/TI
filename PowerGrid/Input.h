#ifndef INPUT_H
#define INPUT_H

#include <Windows.h>

/*#include <stdlib.h>
#include <string.h>
#include <stdio.h>*/

#include "Player.h"

class Input
{
	//buttons
	const int PASS_ID = 0;
	const int BID_ID = 1;
	const int POWER_PLANT_1_ID = 10;
	const int POWER_PLANT_2_ID = 11;
	const int POWER_PLANT_3_ID = 12;
	const int POWER_PLANT_4_ID = 13;

	//static int _selectedPowerPlant;
	static Player _currentPlayer;

public:
	Input();
	~Input() {};

	static LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);
};

void InitWinMain(HINSTANCE*, char*, Input*);

HWND InitWindow(HINSTANCE*, char*, Input*);

#endif // !CONTROL_H