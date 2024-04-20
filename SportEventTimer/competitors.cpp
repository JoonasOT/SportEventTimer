#include "Competitors.h"

#include <fstream>
#include <iostream>

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
	auto size = static_cast<size_t>(size_s);
	std::unique_ptr<char[]> buf(new char[size]);
	std::snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

std::string addWithPadd(std::string a, std::string b, size_t s) {
	if (a.size() == s) return a + b;
	return a + std::string(s - a.size(), ' ') + b;
}

std::string getTime(std::chrono::high_resolution_clock::time_point a, std::chrono::high_resolution_clock::time_point b) {
	if (a <= b) return "NO TIME";
	long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(a - b).count();
	long long s = ms / 1000;
	long long min = s / 60;
	long long h = min / 60;
	min %= 60;
	s %= 60;
	ms %= 1000;

	std::string out = string_format("%d:%02d:%02d.%03d", h, min, s, ms);
	return out;
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
	if (!m_active_runners) {
		std::cout << "Please provide file \"names.txt\" in the same folder as this executable!\n\n";
	}
}

std::vector<Competitor> Competitors::getCompetitors() const {
	return m_competitors;
}

std::string Competitors::endTimeFor(std::string name) {
	for (auto& c : m_competitors) {
		if (c.fullname == name) {
			if (!c.ended) {
				c.end_time = std::chrono::high_resolution_clock::now();
				m_active_runners -= (c.ended = true);
			}
			return getTime(c.end_time, m_start_time);
		}
	}
	return "Couldnt find competitor: " + name + "!";
}

std::string Competitors::endTimeFor(int number) {
	for (auto& c : m_competitors) {
		if (c.number == number) {
			if (!c.ended) {
				c.end_time = std::chrono::high_resolution_clock::now();
				m_active_runners -= (c.ended = true);
			}
			return getTime(c.end_time, m_start_time);
		}
	}
	return "Couldnt find competitor with number: " + std::to_string(number) + "!";
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
