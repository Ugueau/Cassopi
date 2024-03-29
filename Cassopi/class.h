#pragma once
#include <iostream>
#include<SDL.h> //ne pas oublier
#include<SDL_ttf.h> //ne pas oublier
#include <string>
#include <vector>
#include <thread>
#include <Windows.h>
using namespace std;
/////////////////////////////
#define XXS 300
#define XS 150
#define S 100
#define M 75
#define L 50
#define XL 30
#define XXL 25
#define Giant 10
#define Huge 5
#define Titan 2 
#define God 1
const int zoomTable[11] = { XXS, XS, S, M, L, XL, XXL, Giant, Huge, Titan, God };
////////////////////////////

class Palette {
protected:
	vector<SDL_Color> colorTable;
public :
	Palette();
	Palette(const string& colorFile);
	~Palette();
	const SDL_Color* getPalette(int numColor) const; 
	const int getPaletteSize();
	void setNewColor(Uint8 red, Uint8 green, Uint8 blue);
	void paletteSave(const string& colorFile);
	void drawPalette(SDL_Renderer* rendu);
};

class Pixel {
private:
	SDL_Color* color;
	SDL_Color* borderColor[4] = { nullptr,nullptr,nullptr,nullptr }; //0 = top, 1 = bottom, 2 = right, 3 = left
	SDL_Rect pixelArea = { 0,0,0,0 };
public :
	const SDL_Color* getPixelColor() const;
	const SDL_Color* getPixelBorder() const;
	const SDL_Rect* getPixelArea();
	void setPixelColor(SDL_Color* color);
	void setPixelTopBorder(SDL_Color* newBorderColor);
	void setPixelBottomBorder(SDL_Color* newBorderColor);
	void setPixelRightBorder(SDL_Color* newBorderColor);
	void setPixelLeftBorder(SDL_Color* newBorderColor);
	void setPixelSize(int height);
	void setPixelCoordinate(int x, int y);
};


class Sheet {
private:
	vector<vector<Pixel>> grid;
	int zoomSize = God;
public:
	Sheet();
	Sheet(int size);
	//Sheet(Sheet* sheet_, int size); a faire plus tard pour le changement de taille 
	//void setSheetSize();
	void setSelectedPixel(SDL_Color* color, int xSelectedPixel, int ySelectedPixel);
	void setZoomSize(int newZoomSize);
	const int getZoomSize() const;
	Pixel* getPixel(int x, int y);
	void sheetToSVG(const string& fileName);
	void sheetReset();
	void DrawSheet(SDL_Renderer* rendu);
	void DrawPixel(SDL_Renderer* rendu, int x, int y);
};
