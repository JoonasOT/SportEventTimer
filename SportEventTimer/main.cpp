#include <iostream>

#include "Competitors.h"

int main(int argc, char* argv[]) {
	Competitors competitors("names.txt");
	
	std::string input;
	std::string out;
	while (competitors.areCompeting()) {
		std::getline(std::cin, input);
		if (input == "end") break;
		if (input.size() < 1) continue;
		if (input[0] == '#') {
			out = "Number " + input.substr(1) + ": " + competitors.endTimeFor(std::stoi(input.substr(1)));
		} else {
			out = input + ": " + competitors.endTimeFor(input);
		}
		std::cout << out << "\n";
	}
	
	std::cout << "\n\nResults:\n" << (std::string)competitors;

	return 0;
}