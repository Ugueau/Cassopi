#pragma once
#include <iostream>
#include<SDL.h> //ne pas oublier
#include<SDL_ttf.h> //ne pas oublier
#include <string>
#include <vector>
using namespace std;

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
};

class Pixel {
private:
	SDL_Color* color;
	SDL_Color* borderColor[4] = { nullptr,nullptr,nullptr,nullptr }; //0 = top, 1 = bottom, 2 = right, 3 = left
	SDL_Rect pixelArea = { 0,0,0,0 };
public :
	const SDL_Color* getPixelColor() const;
	const SDL_Color* getPixelBorder() const;
	void setPixelColor(SDL_Color* color);
	void setPixelTopBorder(SDL_Color* newBorderColor);
	void setPixelBottomBorder(SDL_Color* newBorderColor);
	void setPixelRightBorder(SDL_Color* newBorderColor);
	void setPixelLeftBorder(SDL_Color* newBorderColor);
	void setPixelSize(int height, int width);
	void setPixelCoordinate(int x, int y);
};


//class Sheet {
//private:
//	vector<Pixel> grid;
//public:
//	Sheet();
//	Sheet(int size);
//	//Sheet(Sheet* sheet_, int size); a faire plus tard pour le changement de taille 
//	void sheetSave(const string& fileName);
//	void sheetReset();
//	
//
//};
