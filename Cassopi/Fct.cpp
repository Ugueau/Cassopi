#pragma once
#include <iostream>
#include <string>
#include<SDL.h> //ne pas oublier
#include<SDL_ttf.h> //ne pas oublier
#include <fstream>
#include "Fct.h"
using namespace std;

Palette::Palette() {
	SDL_Color tmp;
	char recup[20];
	ifstream reader("default_color.txt", ios::in);
	if (!reader) {
		cout << "erreur ouverture du fichier couleur" << endl;
	}
	reader.getline(recup, 20);
	colorCount = atoi(recup);
	for (int i = 0; i < colorCount; i++) {
		reader.getline(recup, 20, ',');
		tmp.r = atoi(recup);
		reader.getline(recup, 20, ',');
		tmp.g = atoi(recup);
		reader.getline(recup, 20, ';');
		tmp.b = atoi(recup);
		tmp.a = 255;
		colorTable.push_back(tmp);
	}
	reader.close();

}

Palette::Palette(const string& colorFile) {
	SDL_Color tmp;
	char recup[20];
	ifstream reader(colorFile, ios::in);
	if (!reader) {
		cout << "erreur ouverture du fichier couleur" << endl;
	}
	reader.getline(recup, 20);
	colorCount = atoi(recup);
	colorTable.reserve(colorCount);
	for (int i = 0; i < colorCount; i++) {
		reader.getline(recup, 20, ',');
		tmp.r = atoi(recup);
		reader.getline(recup, 20, ',');
		tmp.g = atoi(recup);
		reader.getline(recup, 20, ';');
		tmp.b = atoi(recup);
		tmp.a = 255;
		colorTable.push_back(tmp);
	}
	reader.close();
}

Palette::~Palette(){

}

const SDL_Color* Palette::getPalette( int i) const{
	return &colorTable[i];
}

const int Palette::getPaletteColorNumber() const{
	return colorCount;
}

void Palette::setNewColor(Uint8 rouge, Uint8 vert, Uint8 bleu) {
	SDL_Color ajout = { rouge,vert,bleu,255 };
	colorCount++;
	colorTable.push_back(ajout);
}

void Palette::paletteSave(const string& colorFile) {
	ofstream save(colorFile, ios::out);

}

const SDL_Color* Pixel::getPixelColor() const {
	return color;
}

const SDL_Color* Pixel::getPixelBorder() const {
	return *borderColor;
}

void Pixel::setPixelColor(SDL_Color* newColor){
	color = newColor;
}

void Pixel::setPixelTopBorder(SDL_Color* newBorderColor){
	borderColor[0] = newBorderColor;
}

void Pixel::setPixelBottomBorder(SDL_Color* newBorderColor)
{
	borderColor[1] = newBorderColor;
}

void Pixel::setPixelRightBorder(SDL_Color* newBorderColor)
{
	borderColor[2] = newBorderColor;
}

void Pixel::setPixelLeftBorder(SDL_Color* newBorderColor)
{
	borderColor[3] = newBorderColor;
}

void Pixel::setPixelSize(int height, int width){
	pixelArea.h = height;
	pixelArea.w = width;
}

void Pixel::setPixelCoordinate(int x, int y){
	pixelArea.x = x;
	pixelArea.y = y;
}
