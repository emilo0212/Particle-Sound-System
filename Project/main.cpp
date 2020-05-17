#include "main.h"

//Includere "std" namespace, s� vi ikke beh�ver 
//at skrive std:: for an alle <iostream> funktioner.
using namespace std;

//S�tter pointeren til objektet "sdlwindow" til at v�re i lig 
//med en nullpointer, s� vi ikke oplever hukommelsesrelateret problemer
SDLMain *sdlwindow = nullptr;

//Initialisere min sk�rm st�rrelse med nogle v�rdier.
int Main::screenX = 1280;
int Main::screenY = 720;

//Main l�kken, som k�rer hele programmet, ogs� kendt som
//"entry point" i programemrings begreb.
int main()
{
	//S�tter objektet til at v�re et nyt objektet af klassen "SDLMain"
	sdlwindow = new SDLMain();

	//Initialisere vinduet med objektet
	sdlwindow->Init("PLS - Partikel & Lyd System", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Main::screenX, Main::screenY);

	//Mens sdlwindow->online() (som er en booleon) er true, s� 
	//k�rer den de forskellige handlinger i en l�kke.
	while (sdlwindow->online()) {
		sdlwindow->handleEvents();
		sdlwindow->Update();
		sdlwindow->Render();
	}
	
	//Ellers lukker den programmet og cleaner det hele.
	sdlwindow->Clean();
	return 0;
}

