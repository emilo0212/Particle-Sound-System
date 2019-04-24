#include "Engineoptions.h"

bool Engineopt::showWindow = true;

void Engineopt::RenderWindow() {
	if (!Engineopt::showWindow)
		return;

	static int page = 0;
	
	ImGui::SetNextWindowSize(ImVec2(455, 300));
	if (ImGui::Begin("Engine options", &Engineopt::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize)) {
		
		const char* tabs[] = {
			"Engine",  //0
			"Config",  //2
		};

		for (int i = 0; i < IM_ARRAYSIZE(tabs); i++) {

			if(ImGui::Button(tabs[i], ImVec2(ImGui::GetWindowSize().x / IM_ARRAYSIZE(tabs) - 11, 0)))
				page = i;

			if (i < IM_ARRAYSIZE(tabs) - 1)
				ImGui::SameLine();
		}

		ImGui::Separator();

		switch (page) {
		case 0:
			Engine::RenderTab();
			break;
		case 1:
			Config::RenderTab();
			break;
		}
		ImGui::End();
	}
}