#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <d3d9.h>
#include <Windows.h>
#include "Image.h"
#include <stdio.h>
#include <D3dx9math.h>
#include <vector>
#include <string>
#include <math.h>

namespace GraphicsNS
{
	struct DrawStruct
	{
		float scale = 1.0f;
		RECT* rect = 0;
		D3DXVECTOR3* position = 0;
		D3DXVECTOR3* tilePosition = 0;
		D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255);
		D3DXMATRIX transformMatrix;

		DrawStruct();
	};

	class Graphics
	{
	public:
		const static int FONT_SIZE_SMALL = 8;
		const static int FONT_SIZE_BIG = 15;
		const static D3DCOLOR WHITE = D3DCOLOR_XRGB(255, 255, 255);
		const static D3DCOLOR BLACK = D3DCOLOR_XRGB(0, 0, 0);
		const static D3DCOLOR RED = D3DCOLOR_XRGB(255, 0, 0);
		const static D3DCOLOR BLUE = D3DCOLOR_XRGB(0, 0, 255);
		const static D3DCOLOR GREEN = D3DCOLOR_XRGB(0, 255, 0);
		const static D3DCOLOR YELLOW = D3DCOLOR_XRGB(255, 255, 0);
		const static D3DCOLOR PURPLE = D3DCOLOR_XRGB(255, 0, 255);

	private:
		LPDIRECT3D9 _d3d;
		LPDIRECT3DDEVICE9 _d3dDevice;
		LPD3DXFONT _font8;
		LPD3DXFONT _font15;
		HDC _hdc;
		LPD3DXSPRITE _sprite = 0;
		std::vector<Image*> imageVector;
		std::string imagePath;

		Image* whitePixel;

	public:
		Graphics(HWND hWnd);
		~Graphics();

		void Flip(bool waitRetrace = true);
		void Clear(DWORD color = 0);
		void StartDrawing();
		void StopDrawing();

		//Används då man bara har en bild, dvs inte flera tiles
		Image* LoadImageFromFile(std::string);
		//Används då man bara har en bild, dvs inte flera tiles och definierad storlek
		Image* LoadImageFromFile(std::string, int, int);
		//Används då man har flera tiles
		Image* LoadImageFromFile(std::string, int, int, int, int);

		void Draw(Image*, int, int, float);
		void DrawWithColor(Image*, int, int, D3DCOLOR);
		void DrawTile(Image*, int, int, int, int);
		void DrawAnimation(Image*, int, int, int, int);
		void DrawRotateImage(Image*, int, int, double, int);

		void PrintText8(std::string, int, int, D3DCOLOR);
		void PrintText15(std::string, int, int, D3DCOLOR);
		void PrintText8(int, int, int, D3DCOLOR);
		void PrintText15(int, int, int, D3DCOLOR);

		void DrawRectangle(int, int, int, int, D3DCOLOR);

	private:
		void Draw(DrawStruct, Image*);
	};
}

#endif