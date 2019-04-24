#include "main.h"

using namespace std;

SDLMain* sdlwindow = nullptr;

const int Main::screenX = 800;
const int Main::screenY = 600;

int main(int argc, char *args[])
{
	sdlwindow = new SDLMain();
	sdlwindow->Init("PLS - Partikel & Lyd System", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Main::screenX, Main::screenY, false);

	while (sdlwindow->online()) {
		sdlwindow->handleEvents();
		sdlwindow->Update();
		sdlwindow->Render();
	}

	sdlwindow->Clean();
	return 0;
}