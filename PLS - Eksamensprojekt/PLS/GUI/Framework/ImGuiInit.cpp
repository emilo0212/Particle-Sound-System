#include "ImGuiInit.h"

void ImGuiInit::Init(SDL_Renderer* renderer) {
	ImGui::CreateContext();
	ImGuiSDL::Initialize(renderer, Main::screenX, Main::screenY);
	std::cout << "ImGui initialized!" << std::endl;
}

void ImGuiInit::Clean(){
	ImGuiSDL::Deinitialize();
	std::cout << "ImGuiSDL deinitialized!" << std::endl;

	ImGui::DestroyContext();
	std::cout << "ImGui context destroyed!" << std::endl;
}