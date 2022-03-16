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

int main(int argn, char* argv[]) {

	SDL_Color test1 = { 0,0,255,255 };
	SDL_Color* colorCursor = &test1;

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
	SDL_Renderer* rendu = SDL_CreateRenderer(
		win,  
		-1, 
		SDL_RENDERER_ACCELERATED);

	Palette myPalette;
	SDL_Rect r = { 0,0,30,30 };
	Sheet feuille (M);
	myPalette.setNewColor(170, 70, 130);
	myPalette.setNewColor(0, 154, 00);
	SDL_RenderClear(rendu);
	cout << "test" << endl;
	toolInterface(rendu,&myPalette);
	feuille.DrawSheet(rendu);
	myPalette.drawPalette(rendu);
	//SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
	//SDL_RenderDrawLine(rendu, 1500, 325, 1500, 355);
	//SDL_RenderPresent(rendu);


	bool continuer = true;
	SDL_Event event;

	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			continuer = false;
			break;

		case SDL_MOUSEBUTTONUP:
			mouseAction(rendu,&event, colorCursor, &feuille, &myPalette, M);
			feuille.DrawSheet(rendu);
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