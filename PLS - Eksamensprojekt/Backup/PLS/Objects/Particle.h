#pragma once
#include "main.h"
#include "Utility.h"

#include <chrono>
#include <thread>
#include <future>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>


class Particle {
public:
	Particle();
	~Particle();

	void Init();
	void Update();
	void Clean();
	void DrawParticle(SDL_Renderer *Renderer);

private:
	void Gravity(double friction, bool axis);
	void Collision(double radius);
};