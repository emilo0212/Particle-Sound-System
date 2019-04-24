#pragma once
#include <SDL.h>
#include <iostream>

#include "Particle.h"
#include "ImGuiInit.h"

class SDLMain {
public:
	SDLMain();
	~SDLMain();

	void Init(const char* TITLE, int XPOS, int YPOS, int WIDTH, int HEIGHT, bool FULLSCREEN);
	void handleEvents();
	void Update();
	void Render();
	void Clean();

	bool online() {
		return isOnline;
	}
	SDL_Renderer* renderer;

private:
	bool isOnline;
	SDL_Window* window;
	
};
