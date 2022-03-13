#include<SDL.h> //ne pas oublier
#include<SDL_ttf.h> //ne pas oublier
#include <iostream>
#include "class.h"
#include "color.h"
#include "config_sdl.h"
#include "fonction.h"

using namespace std;

const int LARGEUR = 1800; //largeur fenetre
const int HAUTEUR = 950;  //hauteur fenetre

int main(int argn, char* argv[]) {//ent�te impos�e
								  //ouverture de la SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "Echec � l�ouverture";
		return 1;
	}

	//on cr�e la fen�tre
	SDL_Window* win = SDL_CreateWindow("Cassopi",
		SDL_WINDOWPOS_CENTERED,     //pos. X: autre option: SDL_WINDOWPOS_UNDEFINED
		SDL_WINDOWPOS_CENTERED,     //pos. Y: autre option: SDL_WINDOWPOS_UNDEFINED 
		LARGEUR, 			//largeur en pixels			
		HAUTEUR, 			//hauteur en pixels
		SDL_WINDOW_SHOWN//d�autres options (plein ecran, resizable, sans bordure...)
	);
	if (win == NULL)
		cout << "erreur ouverture fenetre";

	//Cr�ation d�un dessin associ� � la fen�tre (1 seul renderer par fenetre)
	SDL_Renderer* rendu = SDL_CreateRenderer(
		win,  //nom de la fen�tre
		-1, //par d�faut
		SDL_RENDERER_ACCELERATED); //utilisation du GPU, valeur recommand�e

	Palette test;
	SDL_Rect r = { 0,0,30,30 };
	Sheet feuille (Giant);
	test.setNewColor(170, 70, 130);
	test.setNewColor(0, 154, 00);
	SDL_RenderClear(rendu);
	cout << "test" << endl;
	toolInterface(rendu,&test);
	feuille.DrawSheet(rendu);


	//SDL_SetRenderDrawColor(rendu, 255, 0, 0, 0);
	//SDL_RenderDrawLine(rendu, 50, 0, 50, 900);
	//SDL_SetRenderDrawColor(rendu, 255, 255, 0, 0);
	//SDL_RenderDrawLine(rendu, 50, 900, 50, 948);
	//SDL_RenderPresent(rendu);

	bool continuer = true;   //bool�en fin de programme
	SDL_Event event;//gestion des �v�nements souris/clavier, 
					//SDL_Event est de type struct
	while (continuer)
	{
		SDL_WaitEvent(&event);//attente d�un �v�nement
		switch (event.type) //test du type d��v�nement
		{
		case SDL_QUIT: //clic sur la croix de fermeture
					   //on peut enlever SDL_Delay
			continuer = false;
			break;
		}
	}
	//destruction du renderer � la fin
	SDL_DestroyRenderer(rendu);

	//destruction � la fin
	SDL_DestroyWindow(win);   //equivalent du delete

	//fermeture
	SDL_Quit();
	return 0;
}