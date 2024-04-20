#include <iostream>

#include "Competitors.h"

enum INPUT_TYPE { END, STATS, NUMBER, NAME, INVALID };

INPUT_TYPE inputToType(std::string input) {
	if (input.size() < 1) return INVALID;
	if (input[0] == '#') return NUMBER;
	for (auto& c : input) c = std::toupper(c);
	if (input == "END") return END;
	if (input == "STATS") return STATS;
	return NAME;
}


int main(int argc, char* argv[]) {
	Competitors competitors("names.txt");
	if (!competitors.areCompeting()) {
		std::cin.get();
		return -1;
	}
	std::string input;
	std::string out;

	std::cout << "----To start write \"START\"----\n";
	while (true) {
		std::getline(std::cin, input);
		if (input == "end") return 1;
		if (input == "START") break;
	}

	competitors.start();
	std::cout << "Competition started!\n\n";

	bool ended = false;
	while (competitors.areCompeting() && !ended) {
		std::cout << ">";
		std::getline(std::cin, input);
		switch (inputToType(input))
		{
		case END:
			ended = true;
			out = "Competition ended!";
			break;
		case STATS:
			out = (std::string)competitors;
			break;
		case NUMBER:
			out = "Number " + input.substr(1) + ": " + competitors.endTimeFor(std::stoi(input.substr(1)));
			break;
		case NAME:
			out = input + ": " + competitors.endTimeFor(input);
			break;
		case INVALID:
		default:
			continue;
		}
		std::cout << out << "\n\n";
	}
	
	std::cout << "\n\nResults:\n" << (std::string)competitors << "\n\n";
	std::cin.get();

	return 0;
}