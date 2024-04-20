#pragma once

#include <vector>
#include <string>
#include <chrono>

struct Competitor {
	std::string  fullname;
	int number;
	std::chrono::high_resolution_clock::time_point end_time;
	bool ended = false;

	Competitor(std::string string) {
		fullname = string.substr(0, string.find(":"));
		number = std::stoi(string.substr(fullname.length() + 1));
		end_time = std::chrono::high_resolution_clock::now();
	}
	operator std::string() const {
		return fullname + " (" + std::to_string(number) + ")";
	}
};

class Competitors
{
public:
	Competitors(std::string);
	std::vector<Competitor> getCompetitors() const;
	std::string endTimeFor(std::string);
	std::string endTimeFor(int);
	void start();
	operator std::string() const;
	bool areCompeting();

private:
	std::vector<Competitor> m_competitors;
	std::chrono::high_resolution_clock::time_point m_start_time;
	size_t m_max_width = 0;
	uint64_t m_active_runners = 0;
};

