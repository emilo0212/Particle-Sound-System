#pragma once
#include <SDL.h>
#undef main

#include <iostream>
#include <vector>

#include "../UI/Windows/Mainwindow.h"
#include "../../Objects/Particle.h"
#include "../Framework/ImGuiInit.h"

//Inkludere partikel & imguiinit klasserne.
class Particle; class ImGuiInit;

//Min SDL klasse som jeg kan f� adgang til i alle andre filer.
//Klassen hj�lper med at skabe objekter, s� man ikke manuelt skal skabe
//alle objektkerne.
//Derudover hj�lper klassen med at beregne de forskellige v�rdier for hvert objekt
//i en evig l�kke indtil programmet slukkes.
class SDLMain {
public:
	void Init(const char* TITLE, int XPOS, int YPOS, int WIDTH, int HEIGHT);
	void handleEvents();
	void Update();
	void Render();
	void Clean();

	SDL_Surface* getWindowSurface() { return windowSurface; }
	SDL_Renderer* getRenderer() { return renderer; }

	bool online() {
		return isOnline;
	}

	SDL_Renderer* renderer = nullptr;
	SDL_Surface* windowSurface = nullptr;

private:
	bool isOnline;
	
	SDL_Window* window = nullptr;
};
