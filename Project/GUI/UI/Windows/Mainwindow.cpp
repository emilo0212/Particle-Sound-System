#include "Mainwindow.h"

bool Mainwindow::isVisible = true;

void SetupMainMenuBar() {
	if (ImGui::BeginMainMenuBar()) {
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8 * 2.0f, 4 * 2.0f));
		ImGui::Selectable("Velkomstsiden", &Welcomewindow::showWindow, 0, ImVec2(ImGui::CalcTextSize("Velkomstsiden", NULL, true).x, 0.0f));
		ImGui::Selectable("Systemet", &Engineopt::showWindow, 0, ImVec2(ImGui::CalcTextSize("Systemet", NULL, true).x, 0.0f));

		ImGui::SameLine();
		ImGui::PopStyleVar();
		ImGui::EndMainMenuBar();
	}
}

void Mainwindow::SetupWindows() {
	if (Mainwindow::isVisible) {
		SetupMainMenuBar();
		Engineopt::RenderWindow();
		Welcomewindow::RenderWindow();
	}
}