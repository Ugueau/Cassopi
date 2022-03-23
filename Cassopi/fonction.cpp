#include<SDL.h> //ne pas oublier
#include<SDL_ttf.h> //ne pas oublier
#include <iostream>
#include "class.h"
#include "color.h"
#include "fonction.h"

using namespace std;


void toolInterface(SDL_Renderer* rendu, Palette* colorPalette) {
	SDL_RenderClear(rendu);
	SDL_Rect toolArea = { 1300,1,500,948 };
	int count = 0;
	int r, g, b;
	SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
	SDL_RenderFillRect(rendu, &toolArea);

	toolArea = { 0,0,1300,950 };
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
	SDL_RenderFillRect(rendu, &toolArea);

	toolArea = {1325,325,450,600};
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
	SDL_RenderFillRect(rendu, &toolArea);

	toolArea = {1325,25,200,75};
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
	SDL_RenderDrawRect(rendu, &toolArea);

	toolArea = { 1575,25,200,75 };
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
	SDL_RenderDrawRect(rendu, &toolArea);

	toolArea = { 1325,125,450,50 };
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
	SDL_RenderDrawRect(rendu, &toolArea);

	toolArea = { 1325,200,450,100 };
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
	SDL_RenderDrawRect(rendu, &toolArea);
	SDL_RenderPresent(rendu);
}

SDL_Color* mouseAction(SDL_Renderer* rendu, SDL_Event* event, SDL_Color* colorCursor, Sheet* currentSheet, Palette* currentPalette, int taille) {
	// detecter si souris dans zone de palette ou zone de dessin 
	// puis si zone dessin changer la couleur du pixel correspondant 
	// si zone palette changer la couleur selectionner (creer une variable SDL_Color qui correspond au choix de couleur en cours)
	if (event->button.button == SDL_BUTTON_LEFT) {
		if (event->button.x < 1775 && event->button.x > 1325 && event->button.y < 925 && event->button.y > 325) {
			if ((event->button.x - 1325) / 30 + ((event->button.y - 325) / 30) * 15 < currentPalette->getPaletteSize()) {
				//zone de palette /!\ detecter si click est bien sur une couleur sinon depassement de vector
				colorCursor = (SDL_Color*)currentPalette->getPalette((event->button.x - 1325) / 30 + ((event->button.y - 325) / 30) * 15);
				//cout << RED << (event->button.x - 1325) / 30 + ((event->button.y - 325) / 30) * 15 << endl << RESET;
				return colorCursor;
			}
		}
		if (event->button.x < 1300 && event->button.x > 50 && event->button.y > 25 && event->button.y < 900) {
			SDL_RenderClear(rendu);
			currentSheet->setSelectedPixel(colorCursor,((event->button.x-50) / taille),((event->button.y-25) / taille));
			toolInterface(rendu, currentPalette);
			currentPalette->drawPalette(rendu);
			currentSheet->DrawSheet(rendu);
			SDL_RenderPresent(rendu);
			//cout << "le pixel : " << ((event->button.x - 50) / taille) << " : " << ((event->button.y - 25) / taille) << "\n Couleur : " << (int)colorCursor->r << (int)colorCursor->g << (int)colorCursor->b << endl;
		}
	}
	return colorCursor;
}