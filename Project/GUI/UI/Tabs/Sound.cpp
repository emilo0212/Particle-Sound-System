#include "Sound.h"

#define SAMPLE_COUNT 1024
float output_stream[SAMPLE_COUNT];

const double PI = 3.141592653589793238460;

namespace fs = std::experimental::filesystem;
using namespace std;

bool song_playing = false;
bool Sound::play_button_pressed = false;

float Sound::song_volume = 50.0f;
float Sound::song_frequency = 1.0f;

sf::Music music;
sf::SoundBuffer buffer;
sf::Sound sound;

string& replace(string& s, const string& from, const string& to){
	if (!from.empty())
		for (size_t pos = 0; (pos = s.find(from, pos)) != string::npos; pos += to.size())
			s.replace(pos, from.size(), to);

	return s;
}

string songPath() {
	char pathChar[MAX_PATH];

	HMODULE hModule = GetModuleHandle(NULL);
	if (hModule != NULL) {
		GetModuleFileName(hModule, pathChar, (sizeof(pathChar)));
	}
	else {
		cout << "Module handle is NULL" << endl;
	}

	stringstream scconverter;
	scconverter << pathChar;

	string pathString = scconverter.str();
	string fn = pathString.substr(pathString.find_last_of('\\') + 1);

	pathString = replace(pathString, fn, "Songs");

	return pathString;
}

vector<string> songList(string songPath) {
	vector<string> songsList;

	using iterator = fs::recursive_directory_iterator;
	for (iterator iter(songPath); iter != iterator{}; ++iter) {
		if (iter->path().extension() == ".wav")
			songsList.push_back(iter->path().string().substr(songPath.find_last_of('\\') + 7));
	}

	return songsList;
}

void Sound::RenderTab() {
	static string current_song = songList(songPath())[0];
	string selected_song;

	vector<complex<double>> samples = { 20,20,20 };

	if (ImGui::ListBoxHeader("", ImVec2(290, 130))) {
		for (const auto& sl : songList(songPath())) {
			bool is_selected = (current_song == sl);
			char* x = new char[sl.length() + 1];
			strcpy(x, sl.c_str());

			if (ImGui::Selectable(x, is_selected))
				current_song = sl;

			if (is_selected)
				ImGui::SetItemDefaultFocus();
			
			delete[] x;
		}
		ImGui::ListBoxFooter();
	}

	if (ImGui::Button("Play", ImVec2(0, 0))) {
		if (!play_button_pressed) {
			string fullPath = songPath();
			selected_song = fullPath.append('\\' + current_song);
			music.openFromFile(selected_song);
			music.setVolume(Sound::song_volume);
			music.setPitch(Sound::song_frequency);
			
			music.play();

			song_playing = true;
			play_button_pressed = true;
		}
	}
	
	ImGui::SameLine();

	if (ImGui::Button("Stop", ImVec2(0, 0))) {
		music.pause();
		song_playing = false;
		play_button_pressed = false;
	}

	ImGui::SameLine();

	ImGui::PushItemWidth(140.0f);
		ImGui::SliderFloat("Volume", &Sound::song_volume, 0.0f, 100.0f);
		ImGui::Dummy(ImVec2(80, 0));
		ImGui::SameLine();
		ImGui::SliderFloat("Frequency", &Sound::song_frequency, 0.0f, 2.0f);
	ImGui::PopItemWidth();
}