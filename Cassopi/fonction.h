#pragma once
#include<SDL.h> //ne pas oublier
#include<SDL_ttf.h> //ne pas oublier
#include <iostream>
#include "class.h"

using namespace std;

void toolInterface(SDL_Renderer* rendu, Palette* colorPalette);
void mouseAction(SDL_Renderer* rendu, SDL_Event* event, SDL_Color* colorCursor, Sheet* currentSheet, Palette* currentPalette, int taille);
