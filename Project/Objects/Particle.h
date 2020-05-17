#pragma once
#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <vector>
#include <chrono>
#include <condition_variable>
#include <list>
#include <windows.h>
#include "../GUI/UI/Tabs/Engineopt.h"

//Includere "std" namespace, så vi ikke behøver 
//at skrive std:: for an alle <iostream> funktioner.
using namespace std;

//Vores namespace som vi kan benytter i andre filer.
namespace particleRelated {
	extern int particleAmount;
}

//Struct er det samme som en klasse, bare mere
//simplificeret og er brugbart når man ved
//hvad det er man vil lave og hvad det skal
//bruges ti. Da jeg ikke skal bruge denne struct eller class
//til at benytte i andre filer, så skaber jeg struct
//som er hurtigere og nemmere at få adgang til.
struct oObj {
	float px, py;
	float vx, vy;
	float ax, ay;
	float ox, oy;
	float radius0, radius1, diameter, width, height;
	float mass;
	float friction;
	float svel;
	int score;
	int id;
	int shape;
	float simTimeRemaining;
};

struct oLineObj{
	float sx, sy;
	float ex, ey;
	float radius;
};

//Min Partikel klasse som jeg kan få adgang til i alle andre filer.
//Klassen hjælper med at skabe objekter, så man ikke manuelt skal skabe
//alle de partikler, som brugeren vælger.
//Derudover hjælper klassen med at beregne de forskellige værdier for hvert objekt
//i en evig løkke indtil programmet slukkes.
class Particle {
public:
	void Update();
	void Render(SDL_Renderer* renderer);

	float RandomFloat(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}
};