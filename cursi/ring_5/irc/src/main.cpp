#include <iostream>
#include <cstdlib>
#include <string>
#include <csignal>
#include "Server.hpp"

static int parsePort(const char* str) {
	char* end = 0;
	long port = std::strtol(str, &end, 10);
	if (*end != '\0' || port <= 1024 || port > 65535)
		throw std::runtime_error("[ERROR] Port must be an integer between 1024 and 65535");
	return static_cast<int>(port);
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "[ERROR] Usage: " << argv[0] << " <port> <password>" << std::endl;
		return EXIT_FAILURE;
	}

	try {
		signal(SIGINT, Server::signal_handler);
		signal(SIGQUIT, Server::signal_handler);

		int port = parsePort(argv[1]);
		std::string password(argv[2]);

		std::cout << "[INFO] port:" << port << " password:" << password << std::endl;
		Server ircServer(port, password);
		ircServer.run();
	}
	catch (const std::exception& ex) {
		std::cerr << "[ERROR] Fatal: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
