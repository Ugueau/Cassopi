#include<SDL.h> //ne pas oublier
#include<SDL_ttf.h> //ne pas oublier
#include <iostream>
#include "class.h"
#include "color.h"
#include "fonction.h"

using namespace std;


void toolInterface(SDL_Renderer* rendu) {
	SDL_RenderClear(rendu);
	SDL_Rect toolArea = { 1300,1,500,948 };
	SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
	SDL_RenderFillRect(rendu, &toolArea);

	toolArea = {1323,323,452,602};
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

	//for(vector<SDL_Color>::const_iterator it = )



	SDL_RenderPresent(rendu);
}