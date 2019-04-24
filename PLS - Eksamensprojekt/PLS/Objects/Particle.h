#pragma once
#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <vector>
#include <chrono>
#include <condition_variable>
#include <list>
#include <windows.h>

#include "../GUI/SDL/SDLmain.h"
#include "../main.h"
#include "../GUI/UI/Tabs/Engineopt.h"

using namespace std;

namespace currentStats {
	extern int particleAmount;
}

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

struct oLineObj
{
	float sx, sy;
	float ex, ey;
	float radius;
};

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