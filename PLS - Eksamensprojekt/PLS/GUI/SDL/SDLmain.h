#pragma once
#include <SDL.h>

#include <iostream>
#include <vector>

#include "../UI/Windows/Mainwindow.h"
#include "../../Objects/Particle.h"
#include "../Framework/ImGuiInit.h"

class Particle; class ImGuiInit;
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
