#include<SDL.h> //ne pas oublier
#include<SDL_ttf.h> //ne pas oublier
#include <iostream>
#include "class.h"
#include "color.h"
#include "config_sdl.h"
#include "fonction.h"


using namespace std;

const int LARGEUR = 1800;
const int HAUTEUR = 950;
const SDL_Rect colorPaletteSize = { 0,0,30,30 };
const SDL_Color baseColorCursor = { 0,0,255,255 };

int main(int argn, char* argv[]) {
	
	SDL_Color* colorCursor = (SDL_Color*) &baseColorCursor;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "Echec à l’ouverture";
		return 1;
	}

	//on crée la fenêtre
	SDL_Window* win = SDL_CreateWindow("Cassopi",
		SDL_WINDOWPOS_CENTERED,     
		SDL_WINDOWPOS_CENTERED,      
		LARGEUR, 					
		HAUTEUR, 			
		SDL_WINDOW_SHOWN
	);
	if (win == NULL)
		cout << "erreur ouverture fenetre";

	//Création d’un dessin associé à la fenêtre (1 seul renderer par fenetre)
	SDL_Renderer* rendu = SDL_CreateRenderer(win,-1, SDL_RENDERER_ACCELERATED);
	Palette currentPalette;
	Sheet currentSheet (Giant);
	currentPalette.setNewColor(170, 70, 130);
	currentPalette.setNewColor(0, 154, 00);
	SDL_RenderClear(rendu);
	refreshDisplay(rendu, &currentPalette, &currentSheet);


	//SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
	//SDL_RenderDrawLine(rendu, 1500, 325, 1500, 355);
	//SDL_RenderPresent(rendu);


	bool continuer = true;
	SDL_Event event;
	while (continuer)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			continuer = false;
			break;
		case SDL_KEYDOWN:
			cout << YELLOW << "reset" << endl;
			if (event.key.keysym.sym == SDLK_r) {
				currentSheet.sheetReset();
				refreshDisplay(rendu, &currentPalette, &currentSheet);
			}
			else if (event.key.keysym.sym == SDLK_s) {
				currentSheet.sheetToSVG("monSVG");
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			bool click = true;
			while (click) {
				cout << RED << "click" << endl;
				SDL_WaitEvent(&event);
				if (event.type == SDL_MOUSEBUTTONUP) {
					click = false;
					cout << GREEN << "stop" << endl;
				}
				colorCursor = mouseAction(rendu, &event, colorCursor, &currentSheet, &currentPalette, currentSheet.getSheetSize());
			}
			break;
		}
	}

	//destruction du renderer à la fin
	SDL_DestroyRenderer(rendu);

	//destruction à la fin
	SDL_DestroyWindow(win);   //equivalent du delete

	//fermeture
	SDL_Quit();
	return 0;
}