
#include <iostream>
#include <string>
#include<SDL.h> //ne pas oublier
#include<SDL_ttf.h> //ne pas oublier
#include <fstream>
#include "class.h"
#include "color.h"
using namespace std;
SDL_Color defaultColor = { 255,255,255,255 };
SDL_Color defaultColorBorder = { 190,190,190,255 };

Palette::Palette() {
	SDL_Color tmp;
	int colorLoadCounter;
	char recup[20];
	ifstream reader("default_color.txt", ios::in);
	if (!reader) {
		cout << RED << "erreur ouverture du fichier couleur" << endl;
		return;
	}
	reader.getline(recup, 20);
	colorLoadCounter = atoi(recup);
	for (int i = 0; i < colorLoadCounter; i++) {
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
	int colorLoadCounter;
	char recup[20];
	ifstream reader(colorFile, ios::in);
	if (!reader) {
		cout << RED << "erreur ouverture du fichier couleur" << endl;
		return;
	}
	reader.getline(recup, 20);
	colorLoadCounter = atoi(recup);
	colorTable.reserve(colorLoadCounter);
	for (int i = 0; i < colorLoadCounter; i++) {
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
	vector<SDL_Color>::const_iterator it = colorTable.begin() + i;
	return &(*it);
}


const int Palette::getPaletteSize()
{
	return colorTable.size();
}

void Palette::setNewColor(Uint8 rouge, Uint8 vert, Uint8 bleu) {
	SDL_Color ajout = { rouge,vert,bleu,255 };
	colorTable.push_back(ajout);
}

void Palette::paletteSave(const string& colorFile) {
	ofstream save(colorFile, ios::out);
	if (!save) {
		cout << RED << "Erreur sauvegarde impossible" << endl;
		return;
	}
	save << (int)colorTable.size() << '\n';
	for (vector<SDL_Color>::const_iterator it = colorTable.begin(); it < colorTable.end(); ++it) {
		save << (int) it->r << "," << (int) it->g << "," << (int) it->b << ";";
	}
}

void Palette::drawPalette(SDL_Renderer* rendu)
{
	int count = 0;
	int r, g, b;
	for (int i = -1; i < this->getPaletteSize() / 15; i++) {
		for (int j = 0; j < 15; j++) {
			SDL_Rect paintColor = { (1325 + j * 30),(355 + i * 30),30,30 };
			r = this->getPalette(count)->r;
			g = this->getPalette(count)->g;
			b = this->getPalette(count)->b;
			if (r == 0 && g == 0 && b == 0) {
				SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
				SDL_RenderDrawRect(rendu, &paintColor);
			}
			else {
				SDL_SetRenderDrawColor(rendu, r, g, b, 255);
				SDL_RenderFillRect(rendu, &paintColor);
			}
			count++;
			if (count >= this->getPaletteSize()) {
				return;
			}
		}
	}
}

const SDL_Color* Pixel::getPixelColor() const {
	return color;
}

const SDL_Color* Pixel::getPixelBorder() const {
	return *borderColor;
}

const SDL_Rect* Pixel::getPixelArea()
{
	return &pixelArea;
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

void Pixel::setPixelSize(int height){
	pixelArea.h = height;
	pixelArea.w = height;
}

void Pixel::setPixelCoordinate(int x, int y){
	pixelArea.x = x;
	pixelArea.y = y;
}

Sheet::Sheet()
{
	grid.resize(16);
	for (int i = 0; i < 16; i++)
	{
		grid[i].resize(12);
	}

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 12; j++){
			grid[i][j].setPixelColor(&defaultColor);
			grid[i][j].setPixelSize(M);
			grid[i][j].setPixelCoordinate(M * i + 50, M * j + 25);
			grid[i][j].setPixelBottomBorder(&defaultColorBorder);
			grid[i][j].setPixelTopBorder(&defaultColorBorder);
			grid[i][j].setPixelRightBorder(&defaultColorBorder);
			grid[i][j].setPixelLeftBorder(&defaultColorBorder);
		}
	}
}

Sheet::Sheet(int size)
{
	sheetPixelSize = size;
	grid.resize(1200 / size);
	for (int i = 0; i < 1200 / size; i++)
	{
		grid[i].resize(900 / size);
	}
	for (int i = 0; i < 1200 / size; i++) {
		for (int j = 0; j < 900 / size; j++) {
			grid[i][j].setPixelColor(&defaultColor);
			grid[i][j].setPixelSize(size);
			grid[i][j].setPixelCoordinate((size * i + 50), (size * j + 25));
			grid[i][j].setPixelBottomBorder(&defaultColorBorder);
			grid[i][j].setPixelTopBorder(&defaultColorBorder);
			grid[i][j].setPixelRightBorder(&defaultColorBorder);
			grid[i][j].setPixelLeftBorder(&defaultColorBorder);
		}
	}
}

void Sheet::DrawSheet(SDL_Renderer* rendu)
{
	for (int i = 0; i < 1200 / sheetPixelSize; i++) {
		for (int j = 0; j < 900 / sheetPixelSize; j++) {
			SDL_SetRenderDrawColor(rendu,this->getPixel(i,j)->getPixelColor()->r, this->getPixel(i, j)->getPixelColor()->g, this->getPixel(i, j)->getPixelColor()->b,255);
			SDL_RenderFillRect(rendu, grid[i][j].getPixelArea());
			SDL_SetRenderDrawColor(rendu, this->getPixel(i,j)->getPixelBorder()[0].r, this->getPixel(i, j)->getPixelBorder()[0].g, this->getPixel(i, j)->getPixelBorder()[0].b, 255);
			SDL_RenderDrawLine(rendu, grid[i][j].getPixelArea()->x, grid[i][j].getPixelArea()->y, grid[i][j].getPixelArea()->x+ grid[i][j].getPixelArea()->w, grid[i][j].getPixelArea()->y);
			SDL_RenderDrawLine(rendu, grid[i][j].getPixelArea()->x, grid[i][j].getPixelArea()->y, grid[i][j].getPixelArea()->x, grid[i][j].getPixelArea()->y + grid[i][j].getPixelArea()->h);
		}
	}
}

void Sheet::setSelectedPixel(SDL_Color * color, int xSelectedPixel, int ySelectedPixel)
{
	grid[xSelectedPixel][ySelectedPixel].setPixelColor(color);
	grid[xSelectedPixel][ySelectedPixel].setPixelBottomBorder(color);
	grid[xSelectedPixel][ySelectedPixel].setPixelTopBorder(color);
	grid[xSelectedPixel][ySelectedPixel].setPixelRightBorder(color);
	grid[xSelectedPixel][ySelectedPixel].setPixelLeftBorder(color);
}

const int Sheet::getSheetSize() const
{
	return sheetPixelSize;
}

Pixel* Sheet::getPixel(int x, int y)
{
	return &(grid[x][y]);
}
