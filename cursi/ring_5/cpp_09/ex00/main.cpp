#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	BitcoinExchange btc("data/data.csv");
	btc.process(argv[1]);
	return 0;
}
