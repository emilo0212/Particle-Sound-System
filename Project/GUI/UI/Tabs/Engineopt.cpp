#include "Engineopt.h"

int Engine::AMOUNT = 0;
float Engine::SIZE = 64.0f;
float Engine::MASS = 15.0f;
float Engine::FRICTION = 0.8f;
float Engine::STARTVELOCITY = 105.0f;
bool Engine::addObj = false;
bool Engine::removeObj = false;

int particleRelated::particleAmount;

void Engine::RenderTab() {
	ImGui::Text("Partikel indstillinger: ");
	ImGui::Spacing();
	ImGui::SliderFloat("Stoerrelse", &Engine::SIZE, 5.0f, 150.0f);
	ImGui::Spacing();
	ImGui::SliderFloat("Masse", &Engine::MASS, 1.0f, 1000.0f);
	ImGui::Spacing();
	ImGui::SliderFloat("Friktion", &Engine::FRICTION, 0.0f, 1.0f);
	ImGui::Spacing();
	ImGui::SliderFloat("Hastighed", &Engine::STARTVELOCITY, 100.0f, 1000.0f);
	ImGui::Spacing();

	ImGui::Separator();

	ImGui::Spacing();
	ImGui::SliderInt("Maengde", &Engine::AMOUNT, 0, 100);

	if (ImGui::Button("Tilfoej")) {
		Engine::addObj = true;
	}

	ImGui::SameLine();
	ImGui::Dummy(ImVec2(-10.0f, 0.0f));
	ImGui::SameLine();

	if (ImGui::Button("Fjern")) {
		Engine::removeObj = true;
	}

	ImGui::SameLine();

	ImGui::Text("Antal partikler: %d", particleRelated::particleAmount);
}