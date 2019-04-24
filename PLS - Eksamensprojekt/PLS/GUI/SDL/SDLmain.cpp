#include "SDLmain.h"

ImGuiInit* imguiinit = nullptr;
Particle* particles = nullptr;


void pConstruction(int function, SDL_Renderer* renderer) {
	switch (function) {
	case 0:
		particles->Update();
		break;
	case 1:
		particles->Render(renderer);
		break;
	}
}

void SDLMain::Init(const char* TITLE, int XPOS, int YPOS, int WIDTH, int HEIGHT){

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		
		window = SDL_CreateWindow(TITLE, XPOS, YPOS, WIDTH, HEIGHT, NULL);
		if (window) {
			std::cout << "SDL Window was successfully created!" << std::endl;
		}
		else {
			std::cout << "SDL Window failed. SDL Error: " << SDL_GetError() << std::endl;
		}

		windowSurface = SDL_GetWindowSurface(window);
		if (windowSurface) {
			std::cout << "SDL Window Surface was successfully created!" << std::endl;
		} {
			std::cout << "SDL Window Surface failed. SDL Error: " << SDL_GetError() << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			std::cout << "SDL Renderer was successfully created!" << std::endl;
		}
		else {
			std::cout << "SDL Renderer failed. SDL Error: " << SDL_GetError() << std::endl;
		}
		isOnline = true;
	}
	else {
		isOnline = false;
	}

	imguiinit->Init(renderer);
}

void SDLMain::handleEvents() {
	ImGuiIO& io = ImGui::GetIO();
	SDL_Event event;

	int wheel = 0;
	int mouseX, mouseY;
	const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

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

	io.DeltaTime = 1.0f / 60.0f;
	io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	io.MouseWheel = static_cast<float>(wheel);
}

void SDLMain::Update(){
	pConstruction(0, renderer);
}

void SDLMain::Render(){
	
	ImGui::NewFrame();
	Mainwindow::SetupWindows();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	ImGui::Render();
	
	ImGuiSDL::Render(ImGui::GetDrawData());
	pConstruction(1, renderer);

	SDL_RenderPresent(renderer);
	
}

void SDLMain::Clean(){
	SDL_DestroyWindow(window);
	std::cout << "SDL Window destroyed!" << std::endl;

	SDL_DestroyRenderer(renderer);
	std::cout << "SDL Render destroyed!" << std::endl;

	imguiinit->Clean();
	
	SDL_Quit();
	std::cout << "SDL System cleaned!" << std::endl;
}