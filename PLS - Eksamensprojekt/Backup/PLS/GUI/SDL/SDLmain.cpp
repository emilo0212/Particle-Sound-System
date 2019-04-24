#include "SDLmain.h"

SDLMain::SDLMain(){}
SDLMain::~SDLMain(){}

Particle* particle = nullptr;
ImGuiInit* imguiinit = nullptr;


void SDLMain::Init(const char* TITLE, int XPOS, int YPOS, int WIDTH, int HEIGHT, bool FULLSCREEN){

	int FLAGS = 0;

	if (FULLSCREEN) {
		FLAGS = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		
		window = SDL_CreateWindow(TITLE, XPOS, YPOS, WIDTH, HEIGHT, FLAGS);
		if (window) {
			std::cout << "SDL Window was successfully created!" << std::endl;
		}
		else {
			std::cout << "SDL Window failed. SDL Error: " << SDL_GetError() << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			std::cout << "SDL Renderer was successfully created!" << std::endl;

			imguiinit->Init(renderer);
			particle->Init();
			particle = new Particle();
		}
		else {
			std::cout << "SDL Renderer failed. SDL Error: " << SDL_GetError() << std::endl;
		}

		isOnline = true;
	}
	else {
		isOnline = false;
	}
}

void SDLMain::handleEvents() {
	ImGuiIO& io = ImGui::GetIO();
	SDL_Event event;
	int wheel = 0;
	SDL_PollEvent(&event);
	
	switch (event.type) {
	case SDL_QUIT:
		isOnline = false;
		break;
	
	case SDL_WINDOWEVENT:
		if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
			io.DisplaySize.x = static_cast<float>(event.window.data1);
			io.DisplaySize.y = static_cast<float>(event.window.data2);
		}
		break;

	case SDL_MOUSEWHEEL:
		wheel = event.wheel.y;
		break;

	default:
		break;
	}

	int mouseX, mouseY;
	const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

	io.DeltaTime = 1.0f / 60.0f;
	io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	io.MouseWheel = static_cast<float>(wheel);
}

void SDLMain::Update(){
	particle->Update();
}

void SDLMain::Render(){

	ImGui::NewFrame();
	ImGui::ShowDemoWindow();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	
	particle->DrawParticle(renderer);

	SDL_RenderPresent(renderer);
}
void SDLMain::Clean(){
	SDL_DestroyWindow(window);
	std::cout << "SDL Window destroyed!" << std::endl;

	SDL_DestroyRenderer(renderer);
	std::cout << "SDL Render destroyed!" << std::endl;

	imguiinit->Clean();
	particle->Clean();
	
	SDL_Quit();
	std::cout << "SDL System cleaned!" << std::endl;
}