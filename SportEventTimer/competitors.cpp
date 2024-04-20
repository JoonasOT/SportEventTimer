#include "Competitors.h"

#include <fstream>
#include <iostream>

std::string addWithPadd(std::string a, std::string b, size_t s) {
	if (a.size() == s) return a + b;
	return a + std::string(s - a.size(), ' ') + b;
}

std::string getTime(std::chrono::high_resolution_clock::time_point a, std::chrono::high_resolution_clock::time_point b) {
	if (a < b) return "";
	return std::to_string(std::chrono::duration_cast<std::chrono::seconds>(a - b).count()) + " s";
}


Competitors::Competitors(std::string filename)
{
	std::ifstream file(filename);
	std::string line;
	m_start_time = std::chrono::high_resolution_clock::now();

	while (std::getline(file, line)) {
		Competitor c(line);
		m_competitors.push_back(c);
		m_max_width = std::max(((std::string)c).size(), m_max_width);
		m_active_runners++;
	}
}

std::vector<Competitor> Competitors::getCompetitors() const {
	return m_competitors;
}

std::string Competitors::endTimeFor(std::string name) {
	for (auto& c : m_competitors) {
		if (c.fullname == name) {
			c.end_time = std::chrono::high_resolution_clock::now();
			m_active_runners--;
			return getTime(c.end_time, m_start_time);
		}
	}
	return "Couldnt find competitor: " + name + "!\n";
}

std::string Competitors::endTimeFor(int number) {
	for (auto& c : m_competitors) {
		if (c.number == number) {
			c.end_time = std::chrono::high_resolution_clock::now();
			m_active_runners--;
			return getTime(c.end_time, m_start_time);
		}
	}
	return "Couldnt find competitor with number: " + std::to_string(number) + "!\n";
}

void Competitors::start() {
	m_start_time = std::chrono::high_resolution_clock::now();
}

Competitors::operator std::string() const {
	std::string out = "";
	for (const auto& c : m_competitors) { 
		out += addWithPadd((std::string)c + ": ", getTime(c.end_time, m_start_time) + "\n", m_max_width + 2);
	}
	return out;
}

bool Competitors::areCompeting() {
	return m_active_runners;
}
