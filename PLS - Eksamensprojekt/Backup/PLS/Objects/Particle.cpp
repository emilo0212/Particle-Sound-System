#include "Particle.h"

double xVel, yVel, xPos, yPos, Radius, acceleration;

Particle::Particle(){}
Particle::~Particle(){}

void Particle::Init() {
	xVel = 0.1;
	yVel = 0.1;
	acceleration = 0.0002;
	Radius = 20;
	xPos = Utility::randomDoubleNumber(Radius, Main::screenX);
	yPos = Utility::randomDoubleNumber(Radius, Main::screenY);

	std::cout << "Particles initialized!" << std::endl;
}

void Particle::Gravity(double friction, bool axis) {
	if (axis == true) {
		yVel *= -friction;
	}
	else {
		xVel *= -friction;
	}
}

void Particle::Collision(double radius) {
	if (xPos <= radius | xPos + radius >= Main::screenX) {
		Particle::Gravity(0.90, false);
	}

	if (yPos <= Radius) {
		yVel = -yVel;
	}

	if (yPos + radius >= Main::screenY) {
		Particle::Gravity(0.90, true);
	}
}

void Particle::Update() {
	xPos += xVel;
	yPos += yVel;
	yVel += acceleration;

	Particle::Collision(Radius);
	//std::cout << "x velocity: " << xVel << "| y velocitY: " << yVel << std::endl;
}

void Particle::DrawParticle(SDL_Renderer *Renderer) {
	int32_t radius = Radius;
	int32_t x = radius - 1;
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t err = tx - (radius << 1);

	while (x >= y)
	{
		SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
		SDL_RenderDrawPoint(Renderer, xPos + x, yPos - y);
		SDL_RenderDrawPoint(Renderer, xPos + x, yPos + y);
		SDL_RenderDrawPoint(Renderer, xPos - x, yPos - y);
		SDL_RenderDrawPoint(Renderer, xPos - x, yPos + y);
		SDL_RenderDrawPoint(Renderer, xPos + y, yPos - x);
		SDL_RenderDrawPoint(Renderer, xPos + y, yPos + x);
		SDL_RenderDrawPoint(Renderer, xPos - y, yPos - x);
		SDL_RenderDrawPoint(Renderer, xPos - y, yPos + x);

		if (err <= 0)
		{
			y++;
			err += ty;
			ty += 2;
		}
		if (err > 0)
		{
			x--;
			tx += 2;
			err += tx - (radius << 1);
		}
	}
}

void Particle::Clean() {
	std::cout << "Particles cleaned!" << std::endl;
}