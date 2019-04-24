#include "main.h"
SDLMain *sdlwindow = nullptr;

float Main::screenX = 1280;
float Main::screenY = 720;

int main(int argc, char *args[])
{
	sdlwindow = new SDLMain();
	sdlwindow->Init("PLS - Partikel & Lyd System", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Main::screenX, Main::screenY);

	while (sdlwindow->online()) {
		sdlwindow->handleEvents();
		sdlwindow->Update();
		sdlwindow->Render();
	}

	sdlwindow->Clean();
	return 0;
}