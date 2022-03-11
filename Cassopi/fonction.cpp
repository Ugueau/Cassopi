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

	for (int i = -1; i < colorPalette->getPaletteSize()/15; i++) {
		for (int j = 0; j < 15; j++) {
			toolArea = { (1325+j*30),(355+i*30),30,30 };
			r = colorPalette->getPalette(count)->r;
			g = colorPalette->getPalette(count)->g;
			b = colorPalette->getPalette(count)->b;
			if (r == 0 && g == 0 && b == 0) {
				SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
				SDL_RenderDrawRect(rendu, &toolArea);
			}
			else {
				SDL_SetRenderDrawColor(rendu, r, g, b, 255);
				SDL_RenderFillRect(rendu, &toolArea);
			}
			SDL_RenderPresent(rendu);
			count++;
			if (count >= colorPalette->getPaletteSize()) {
				return;
			}	
		}
	}
}