//Includere 'Particle.h' filen
#include "Particle.h"

//Includere "std" namespace, s� vi ikke beh�ver 
//at skrive std:: for an alle <iostream> funktioner.
using namespace std;

//Definere mine variabler
vector<oObj> vecObjects;
vector<oLineObj> vecLineObjs;
float lineRadius = 2.0f;
bool showLines = true;

int screenWidth = Main::screenX;
int screenHeight = Main::screenY;
float minBoxWidth = screenWidth / 3.8f, maxBoxWidth = screenWidth / 1.02f;
float minBoxHeight = screenHeight / 15.0f, maxBoxHeight = screenHeight / 1.05f;

auto tp1 = chrono::system_clock::now();
auto tp2 = chrono::system_clock::now();

//Min update current stats funktion, som finder m�ngden af
//antal partikler, i vecObjects array.
void updateCS() {
	particleRelated::particleAmount = vecObjects.size();
}

//Min funktion til at tilf�je partikler.
void AddObject(float x, float y, int s = 0) {
	oObj o;
	o.px = x; o.py = y;
	o.vx = 0; o.vy = 0;
	o.ax = 0; o.ay = 0;
	o.ox = 0; o.oy = 0;
	o.diameter = ((float)rand() / (float)RAND_MAX) * Engine::SIZE;
	o.mass = (o.diameter / 2) * Engine::MASS;
	o.friction = Engine::FRICTION;
	o.svel = Engine::STARTVELOCITY;
	o.score = s;
	o.simTimeRemaining = 0.0f;
	o.id = vecObjects.size();
	vecObjects.emplace_back(o);
}

//Min funktion til at initialisere linjerne eller rammerne som skaber sp�rringsboksen.
void InitLines() {
	vecLineObjs.push_back({ minBoxWidth, maxBoxHeight, maxBoxWidth, maxBoxHeight, lineRadius });
	vecLineObjs.push_back({ maxBoxWidth, maxBoxHeight, maxBoxWidth, minBoxHeight, lineRadius });
	vecLineObjs.push_back({ maxBoxWidth, minBoxHeight, minBoxWidth, minBoxHeight, lineRadius });
	vecLineObjs.push_back({ minBoxWidth, minBoxHeight, minBoxWidth, maxBoxHeight, lineRadius });
}

//Min tegning af cirklerne med SDL hvor der benyttes Midpoint algoritmen
void DrawCircle(int xc, int yc, int r, SDL_Renderer* renderer)
{
	int _x = xc, _y = yc;
	int x = 0;
	int y = r;
	int p = 3 - 2 * r;
	if (!r) return;

	while (y >= x)
	{
		SDL_RenderDrawPoint(renderer, _x + x, _y - y);
		SDL_RenderDrawPoint(renderer, _x + x, _y + y);
		SDL_RenderDrawPoint(renderer, _x - x, _y - y);
		SDL_RenderDrawPoint(renderer, _x - x, _y + y);
		SDL_RenderDrawPoint(renderer, _x + y, _y - x);
		SDL_RenderDrawPoint(renderer, _x + y, _y + x);
		SDL_RenderDrawPoint(renderer, _x - y, _y - x);
		SDL_RenderDrawPoint(renderer, _x - y, _y + x);

		if (p < 0) p += 4 * x++ + 6;
		else p += 4 * (x++ - y--) + 10;
	}
}

//Min tegning af linjerne til sp�rringsboksen.
void DrawLine(int x1, int y1, int x2, int y2, SDL_Renderer* renderer) {
	int x_1 = x1, x_2 = x2;
	int y_1 = y1, y_2 = y2;
	SDL_RenderDrawLine(renderer, x_1, y_1, x_2, y_2);
}

//Update funktionen af partiklerne, hvor alt bliver beregnet.
void Particle::Update(){
	//Kalder funktionen til at opdatere vores partikel m�ngder.
	updateCS();

	//Tid, s� vi kan have hastighed.
	tp2 = chrono::system_clock::now();
	chrono::duration<float> elapsedTime = tp2 - tp1;
	tp1 = tp2;

	//Tidsforskellen s� vi kan have en afgr�nsning p� simulationer.
	float newElapsedTime = elapsedTime.count();

	//Hvis vi tilf�jer partikler, s� s�tter vi x og y koordinaterne til at v�re tilf�ldige p� sk�rmen.
	if (Engine::addObj) {
		for (int i = 0; i < Engine::AMOUNT; i++) {
			float x = fabs(RandomFloat(minBoxWidth + (Engine::SIZE / 2), maxBoxWidth - (Engine::SIZE / 2)));
			float y = fabs(RandomFloat(minBoxHeight + (Engine::SIZE / 2), maxBoxHeight - (Engine::SIZE / 2)));
			AddObject(x, y);
		}
		Engine::addObj = false;
	}

	//Hvis vi fjerner partikler, s� tjekker vi om vi fjerne for mange og justere i forhold til det.
	if (Engine::removeObj) {
		int removeAmount;

		if ((size_t)Engine::AMOUNT > vecObjects.size()) {
			removeAmount = vecObjects.size();
		}
		else {
			removeAmount = Engine::AMOUNT;
		}

		vecObjects.erase(vecObjects.begin(), vecObjects.begin() + removeAmount);
		Engine::removeObj = false;
	}
	
	//Vi initalisere linjerne en gang og kun en gang.
	if (showLines) {
		InitLines();
		showLines = false;
	}
	
	//Afstandsformlen
	auto objCollision = [](float x1, float y1, float r1, float x2, float y2, float r2) {
		return fabs((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)) <= ((r1 + r2) * (r1 + r2));
	};

	//Nye vector arrays af objekter fra vores forrige structs.
	vector<pair<oObj*, oObj*>> vecColPairs;
	vector<oObj*> vecSimObjs;

	//Variabler til forskellige simulations l�kker.
	float simStable = 0.05f;
	int simulationUpdates = 1;
	int maxSimulationSteps = 2;
	float simElapsedTime = newElapsedTime / (float)simulationUpdates;

	//L�kken som k�res iforhold til m�ngden af simulationsUpdates variablen.
	for (int i = 0; i < simulationUpdates; i++) { 
		for (auto &obj : vecObjects) {
			obj.simTimeRemaining = simElapsedTime;
		}

		//En underl�kke som k�rer i forhold til et maksimum m�ngde af simulationer.
		for (int j = 0; j < maxSimulationSteps; j++) {
			for (auto &obj : vecObjects) {
				if (obj.simTimeRemaining > 0.0f) {
					//Vi tracker vores positioner ved at gemme vores positioner i obj.ox og obj.oy
					obj.ox = obj.px;
					obj.oy = obj.py;

					//Objekternes accelerationer
					obj.ay = -obj.vy * obj.friction + obj.svel;
					obj.ax = -obj.vx * obj.friction;
					
					//Objekternes hastigheder
					obj.vy += obj.ay * obj.simTimeRemaining;
					obj.vx += obj.ax * obj.simTimeRemaining;
					
					//Objekternes positioner
					obj.py += obj.vy * obj.simTimeRemaining;
					obj.px += obj.vx * obj.simTimeRemaining;
					
					//Objekternes genplacering ved overskridning af kollision beregning
					if (obj.px < minBoxWidth) obj.px += (float)maxBoxWidth + obj.diameter;
					if (obj.px >= maxBoxWidth) obj.px -= (float)maxBoxWidth - obj.diameter;
					if (obj.py < minBoxHeight) obj.py += (float)maxBoxHeight + obj.diameter;
					if (obj.py >= maxBoxHeight) obj.py -= (float)maxBoxHeight - obj.diameter;

					//Farts neds�tning til 0 af de objekter som st�r nederst 
					//(hvilket er et problem som jeg kommer ind p� i rapporten)
					if (fabs(obj.vx*obj.vx + obj.vy*obj.vy) < simStable) {
						obj.vx = 0;
						obj.vy = 0;
					}
				}
			}

			//Statisk kollision & opdateringen af objekternes positioner
			for (auto &obj : vecObjects){
				float deltatime = obj.simTimeRemaining;

				for (auto &edge : vecLineObjs) {
					float lineX1 = edge.ex - edge.sx;
					float lineY1 = edge.ey - edge.sy;

					float lineX2 = obj.px - edge.sx;
					float lineY2 = obj.py - edge.sy;

					float edgeLength = lineX1 * lineX1 + lineY1 * lineY1;

					float t = max(0, min(edgeLength, (lineX1 * lineX2 + lineY1 * lineY2))) / edgeLength;

					float closestPointX = edge.sx + t * lineX1;
					float closestPointY = edge.sy + t * lineY1;

					float distance = sqrtf((obj.px - closestPointX)*(obj.px - closestPointX) + (obj.py - closestPointY)*(obj.py - closestPointY));

					if (distance <= ((obj.diameter / 2) + edge.radius)) {
						oObj* simObj = new oObj();
						simObj->diameter = edge.radius * 2;
						simObj->mass = obj.mass * obj.friction;
						simObj->px = closestPointX;
						simObj->py = closestPointY;
						simObj->vx = -obj.vx;
						simObj->vy = -obj.vy;
						
						vecSimObjs.push_back(simObj);

						vecColPairs.push_back({ &obj, simObj });

						float overlap = 1.0f * (distance - (obj.diameter / 2) - (simObj->diameter / 2));

						obj.px -= overlap * (obj.px - simObj->px) / distance;
						obj.py -= overlap * (obj.py - simObj->py) / distance;
					}
				}

				//Viderudvikling p� statisk kollision
				for (auto &target : vecObjects){
					if (obj.id != target.id){
						if (objCollision(obj.px, obj.py, obj.diameter/2, target.px, target.py, target.diameter/2)){
							vecColPairs.push_back({ &obj, &target });

							float distance = sqrtf((obj.px - target.px)*(obj.px - target.px) + (obj.py - target.py)*(obj.py - target.py));
							float overlap = 0.5f * (distance - obj.diameter/2 - target.diameter / 2);

							obj.px -= overlap * (obj.px - target.px) / distance;
							obj.py -= overlap * (obj.py - target.py) / distance;

							target.px += overlap * (obj.px - target.px) / distance;
							target.py += overlap * (obj.py - target.py) / distance;
						}
					}
				}

				float intendedSpeed = sqrtf(obj.vx * obj.vx + obj.vy * obj.vy);
				float intendedDistance = intendedSpeed * obj.simTimeRemaining;
				float actualDistance = sqrtf((obj.px - obj.ox)*(obj.px - obj.ox) + (obj.py - obj.oy)*(obj.py - obj.oy));
				float actualTime = actualDistance / intendedSpeed;

				obj.simTimeRemaining = obj.simTimeRemaining - actualTime;
			}

			//Dynamisk kollision
			float efficiency = 1.00f;
			for (auto c : vecColPairs) {
				oObj *o1 = c.first, *o2 = c.second;

				//Distancen mellem objekterne med afstandsformlen
				float distance = sqrtf((o1->px - o2->px)*(o1->px - o2->px) + (o1->py - o2->py)*(o1->py - o2->py));

				// Normal v�rdien
				float nx = (o2->px - o1->px) / distance;
				float ny = (o2->py - o1->py) / distance;

				// Tangent v�rdien
				float tx = -ny;
				float ty = nx;

				// Skalarprodukt af tangent v�rdien
				float dpTan1 = o1->vx * tx + o1->vy * ty;
				float dpTan2 = o2->vx * tx + o2->vy * ty;

				// Skalarvprodukt af Normal v�rdien
				float dpNorm1 = o1->vx * nx + o1->vy * ny;
				float dpNorm2 = o2->vx * nx + o2->vy * ny;

				//Bevarelse af momentum i f�rste dimension
				float m1 = efficiency * (dpNorm1 * (o1->mass - o2->mass) + 2 * o2->mass * dpNorm2) / (o1->mass + o2->mass);
				float m2 = efficiency * (dpNorm2 * (o2->mass - o1->mass) + 2 * o1->mass * dpNorm1) / (o1->mass + o2->mass);

				//Opdateringen af objekternes hastigheder.
				o1->vx = tx * dpTan1 + nx * m1;
				o1->vy = ty * dpTan1 + ny * m1;
				o2->vx = tx * dpTan2 + nx * m2;
				o2->vy = ty * dpTan2 + ny * m2;
			}

			//Cleaner sk�rmen
			vecColPairs.clear();

			for (auto &obj : vecSimObjs) delete obj;
			vecSimObjs.clear();
		}
	}
}

//Tegner partiklerne
void Particle::Render(SDL_Renderer* renderer){
	//Tegner cirklerne
	for (auto obj : vecObjects)
		DrawCircle(static_cast<int>(obj.px), static_cast<int>(obj.py), static_cast<int>(obj.diameter/2), renderer);

	//Tegner linjerne som skaber sp�rringsboksen.
	for (auto line : vecLineObjs) {
		DrawCircle(static_cast<int>(line.sx), static_cast<int>(line.sy), static_cast<int>(line.radius), renderer);
		DrawCircle(static_cast<int>(line.ex), static_cast<int>(line.ey), static_cast<int>(line.radius), renderer);

		float nx = -(line.ey - line.sy);
		float ny = (line.ex - line.sx);
		float d = sqrt(nx*nx + ny * ny);
		nx /= d;
		ny /= d;

		DrawLine(static_cast<int>(line.sx + nx * line.radius), static_cast<int>(line.sy + ny * line.radius), 
				 static_cast<int>(line.ex + nx * line.radius), static_cast<int>(line.ey + ny * line.radius), renderer);

		DrawLine(static_cast<int>(line.sx - nx * line.radius), static_cast<int>(line.sy - ny * line.radius), 
			     static_cast<int>(line.ex - nx * line.radius), static_cast<int>(line.ey - ny * line.radius), renderer);
	}
}