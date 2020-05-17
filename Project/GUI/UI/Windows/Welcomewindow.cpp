#include "Welcomewindow.h"

bool Welcomewindow::showWindow = true;

void Welcomewindow::RenderWindow() {
	if (!Welcomewindow::showWindow)
		return;

	static int page = 0;

	ImGui::SetNextWindowPos(ImVec2(12.0f, 275.0f));
	ImGui::SetNextWindowSize(ImVec2(310, 350));
	if (ImGui::Begin("Velkomstsiden", &Welcomewindow::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {

		ImGui::TextColored(ImVec4(0.0f, 0.0f, 255.0f, 255.0f), "Velkommen til PLS! - Partikel & Lyd System!");

		ImGui::Separator();

		ImGui::TextColored(ImVec4(0.0f, 0.0f, 255.0f, 255.0f), "Menu interaktion: ");
		ImGui::Text("1) Systemet kan startes ved at trykke paa \nknappen oeverst med navnet 'Systemet'.");
		ImGui::Text("2) Vinduet kan lukkes ved at trykke paa\nsamme knap igen.");
		ImGui::Text("3) Det samme gaelder for velkomst vinduet.");

		ImGui::Separator();

		ImGui::TextColored(ImVec4(0.0f, 0.0f, 255.0f, 255.0f), "Partikel interaktion: ");
		ImGui::Text("1) Hver indstillinger har en hjaelpe etiket\ntil hoejre for den.");
		ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 255.0f), 
			"Kendt fejl:\nI visse tilfaelde kan partiklerne falde\nunder rammen, da computerens CPU ikke kan\nberegne hurtigt nok iforhold til hvad der\nkraeves. En midlertidig loesning til dette\nproblem er at genindstille partiklernes\nposiition til oeverst under rammen.");
		ImGui::Separator();
		
		ImGui::TextColored(ImVec4(0.0f, 0.0f, 255.0f, 255.0f), "Lyd interaktion: ");
		ImGui::Text("1) Lyden kan indstilles ved at åbne 'System' vinduet\n&navigere til 'Lyden' knappen");
		ImGui::End();
	}
}