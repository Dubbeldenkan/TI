#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <d3d9.h>
#include <Windows.h>
#include "Image.h"
#include <stdio.h>
#include <D3dx9math.h>
#include <vector>
#include <string>

class Graphics
{
public:
	const static int FONT_SIZE = 8;
	const static D3DCOLOR WHITE = D3DCOLOR_XRGB(255, 255, 255);
	const static D3DCOLOR BLACK = D3DCOLOR_XRGB(0, 0, 0);
	const static D3DCOLOR RED = D3DCOLOR_XRGB(255, 0, 0);
	const static D3DCOLOR BLUE = D3DCOLOR_XRGB(0, 0, 255);

	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3dDevice;
	LPD3DXFONT _font;
	HDC _hdc;
	LPD3DXSPRITE _sprite = 0;
	std::vector<Image*> imageVector;
	char imagePath[MAX_PATH];

public:
	Graphics();
	Graphics(HWND hWnd);
	~Graphics();

	void Flip(bool waitRetrace = true); 

	void Clear(DWORD color = 0);

	Image LoadImage(const char* filename);

	void StartDrawing();

	void StopDrawing();

	void Draw(Image*, int, int, float);

	void PrintText(char*, int, int, D3DCOLOR);

	void PrintText(char*, int, int, D3DCOLOR, int);

	void PrintText(int, int, int, D3DCOLOR, int);

	void SetTextSize(int);
};

#endif