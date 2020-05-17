#pragma once
#include "../../main.h"
#include "imgui-master/imgui.h"
#include "imgui-master/imconfig.h"
#include "imgui-master/imgui_sdl.h"

//Klasse af ImGUI
class ImGuiInit {
public:
	void Init(SDL_Renderer* renderern);
	void Clean();
};