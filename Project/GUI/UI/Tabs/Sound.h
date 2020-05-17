#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "winmm.lib")

#include <SFML/Audio.hpp>

#include <experimental/filesystem>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <vector>
#include <valarray>
#include <complex>
#include <math.h>
#include <limits>

#include "../../SDL/SDLmain.h"



namespace Sound {
	void RenderTab();
	
	extern float song_frequency;
	extern float song_volume;

	extern bool play_button_pressed;
}