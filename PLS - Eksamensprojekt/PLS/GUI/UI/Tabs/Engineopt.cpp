#include "Engineopt.h"

int Engine::AMOUNT = 0;
float Engine::SIZE = 64.0f;
float Engine::MASS = 15.0f;
float Engine::FRICTION = 0.8f;
float Engine::STARTVELOCITY = 105.0f;
bool Engine::addObj = false;
bool Engine::removeObj = false;

int currentStats::particleAmount;

void Engine::RenderTab() {
	ImGui::Text("Particle settings: ");
	ImGui::Spacing();
	ImGui::SliderFloat("Size", &Engine::SIZE, 5.0f, 150.0f);
	ImGui::Spacing();
	ImGui::SliderFloat("Mass", &Engine::MASS, 1.0f, 1000.0f);
	ImGui::Spacing();
	ImGui::SliderFloat("Friction", &Engine::FRICTION, 0.0f, 1.0f);
	ImGui::Spacing();
	ImGui::SliderFloat("Velocity", &Engine::STARTVELOCITY, 100.0f, 1000.0f);
	ImGui::Spacing();

	ImGui::Separator();

	ImGui::Spacing();
	ImGui::SliderInt("Amount", &Engine::AMOUNT, 0, 100);

	if (ImGui::Button("Add particles")) {
		Engine::addObj = true;
	}

	ImGui::SameLine();
	ImGui::Dummy(ImVec2(60.0f, 0.0f));
	ImGui::SameLine();

	if (ImGui::Button("Remove particles")) {
		Engine::removeObj = true;
	}

	ImGui::Text("Current Particles = %d", currentStats::particleAmount);
}