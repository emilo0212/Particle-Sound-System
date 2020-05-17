#pragma once
#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <vector>
#include <chrono>
#include <condition_variable>
#include <list>
#include <windows.h>
#include "../GUI/UI/Tabs/Engineopt.h"

//Includere "std" namespace, s� vi ikke beh�ver 
//at skrive std:: for an alle <iostream> funktioner.
using namespace std;

//Vores namespace som vi kan benytter i andre filer.
namespace particleRelated {
	extern int particleAmount;
}

//Struct er det samme som en klasse, bare mere
//simplificeret og er brugbart n�r man ved
//hvad det er man vil lave og hvad det skal
//bruges ti. Da jeg ikke skal bruge denne struct eller class
//til at benytte i andre filer, s� skaber jeg struct
//som er hurtigere og nemmere at f� adgang til.
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

//Min Partikel klasse som jeg kan f� adgang til i alle andre filer.
//Klassen hj�lper med at skabe objekter, s� man ikke manuelt skal skabe
//alle de partikler, som brugeren v�lger.
//Derudover hj�lper klassen med at beregne de forskellige v�rdier for hvert objekt
//i en evig l�kke indtil programmet slukkes.
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