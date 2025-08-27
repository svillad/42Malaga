#include "Server.hpp"
#include "Client.hpp"
#include "BotClient.hpp"
#include <arpa/inet.h>

bool Server::g_signal = false;

Server::Server(int port, const std::string &password)
	: _port(port), _password(password), _listenFd(-1), _running(false), _maxClientCount(0) {
	initSocket();

	BotClient* bot = new BotClient(-2);
	_clients[-2] = *bot;
}

Server::~Server() {
	if (_listenFd != -1)
		close(_listenFd);
}

void Server::initSocket() {
	_listenFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_listenFd == -1)
		throw std::runtime_error(std::string("[ERROR] socket() failed: ") + std::strerror(errno));

	if (fcntl(_listenFd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error(std::string("[ERROR] fcntl(O_NONBLOCK) failed: ") + std::strerror(errno));

	int opt = 1;
	if (setsockopt(_listenFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw std::runtime_error(std::string("[ERROR] setsockopt() failed: ") + std::strerror(errno));

	sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family      = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port        = htons(static_cast<uint16_t>(_port));

	if (bind(_listenFd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) == -1)
		throw std::runtime_error(std::string("[ERROR] bind() failed: ") + std::strerror(errno));

	if (listen(_listenFd, SOMAXCONN) == -1)
		throw std::runtime_error(std::string("[ERROR] listen() failed: ") + std::strerror(errno));
}

// void Server::handleClientInput(int clientFd) {
// 	char buffer[512];
// 	ssize_t bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
// 	buffer[bytesRead] = '\0';
// 	std::istringstream iss(buffer);
// 	std::string token;

// 	iss >> token;
// 	if (bytesRead <= 0 || token == "QUIT" || token == "quit") {
// 		disconnectClient(clientFd);
// 		return;
// 	}

// 	buffer[bytesRead] = '\0';
// 	std::string message(buffer);

// 	std::cout << "[RECV] fd=" << clientFd << " → " << message;

// 	CliCmdHandler handler(*this);
// 	handler.handle(clientFd, message);

// 	if (_clients.size() > _maxClientCount) {
// 		_maxClientCount = _clients.size();
// 		std::cout << "[INFO] New max client count: " << _maxClientCount << std::endl;
// 	}
// }

void Server::handleClientInput(int clientFd) {
	char buffer[512];
	ssize_t bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
	std::cout << "[RECV] Handle client input (fd=" << clientFd << "): " << bytesRead << " bytes..." << std::endl;
	if (bytesRead <= 0) {
		disconnectClient(clientFd);
		delPollFd(clientFd);
		return;
	}

	buffer[bytesRead] = '\0';
	std::string data(buffer, bytesRead);

	Client& client = _clients[clientFd];
	client.appendToBuffer(data);

	std::vector<std::string> commands = client.extractCompleteCommands();
	for (std::vector<std::string>::iterator it = commands.begin(); it != commands.end(); ++it) {
		std::string& command = *it;

		std::istringstream iss(command);
		std::string token;
		iss >> token;
		if (token == "QUIT" || token == "quit") {
			disconnectClient(clientFd);
			return;
		}

		std::cout << "[RECV] fd=" << clientFd << " → " << command << std::endl;

		CliCmdHandler handler(*this);
		handler.handle(clientFd, command);
	}

	if (_clients.size() > _maxClientCount) {
		_maxClientCount = _clients.size();
		std::cout << "[INFO] New max client count: " << _maxClientCount << std::endl;
	}
}

Client& Server::getClient(int fd) {
	if (!_clients.count(fd))
		throw std::runtime_error("Client not found");
	return _clients.at(fd);
}

const Client& Server::getClient(int fd) const {
	if (!_clients.count(fd))
		throw std::runtime_error("Client not found");
	return _clients.at(fd);
}

const std::map<int, Client>& Server::getClients() const {
	return _clients;
}

const std::string& Server::getPassword() const {
	return _password;
}

size_t Server::getChannelsCount() const {
	return _channels.size();
}

size_t Server::getConnectedClientsCount() const {
	return _clients.size();
}

size_t Server::getMaxClientCount() const {
	return _maxClientCount;
}

void Server::sendToClient(int clientFd, const std::string& message) {
	if (clientFd == -2)
		return; // No enviar mensajes al bot

	std::string msg = message;

	if (msg.size() < 2 || msg.substr(msg.size() - 2) != "\r\n")
		msg += "\r\n";

	ssize_t sent = send(clientFd, msg.c_str(), msg.size(), 0);
	if (sent == -1)
		std::cerr << "[ERROR] Failed to send to client (fd=" << clientFd << ")\n";
}

void Server::disconnectClient(int clientFd){
	std::cout << "[INFO] Disconnected (fd=" << clientFd << ")\n";
	CliCmdHandler burst(*this);

	for (std::map<std::string, Channel>::iterator it = _channels.begin();
		 it != _channels.end();) {
		Channel& ch = it->second;

		if (ch.isUserInChannel(clientFd)) {
			ch.removeUser(clientFd);

			if (ch.getAllUsers().empty()) {
				std::map<std::string, Channel>::iterator toErase = it++;
				_channels.erase(toErase);
				continue;
			}

			bool hasOp = false;
			const std::set<int>& users = ch.getAllUsers();
			for (std::set<int>::const_iterator ui = users.begin();
				 ui != users.end(); ++ui) {
				if (ch.isOperator(*ui)) { hasOp = true; break; }
			}

			if (!hasOp) {
				int promoteFd = ch.promoteFirstMemberToOperator();

				if (promoteFd == -2) {
					ch.removeUser(-2);
					std::map<std::string, Channel>::iterator toErase = it++;
					_channels.erase(toErase);
					continue;
				}
				else if (promoteFd != -1) {
					const Client& promoted = getClient(promoteFd);
					std::string modeMsg = ":" + promoted.getNickname() +
						"!pseudo@localhost MODE " + ch.getName() +
						" +o " + promoted.getNickname() + "\r\n";
					ch.broadcast(*this, modeMsg);
				}
			}
			burst.sendNamesBurst(ch);
		}
		++it;
	}

	if (_clients.count(clientFd)) {
		close(clientFd);
		_clients.erase(clientFd);
	}
}

void Server::signal_handler(int sig) {
	(void)sig;
	std::cout << "\n[INFO] Signal received! Shutting down...\n";
	g_signal = true;
}

Channel* Server::getChannel(const std::string& name) {
	std::map<std::string, Channel>::iterator it = _channels.find(name);
	if (it != _channels.end())
		return &it->second;
	return NULL;
}

Channel& Server::createChannel(const std::string& name) {
	_channels[name] = Channel(name);
	return _channels[name];
}

bool Server::channelExists(const std::string& name) const {
	return _channels.find(name) != _channels.end();
}

bool Server::nicknameExists(const std::string& nickname) const {
	for (std::map<int, Client>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second.getNickname() == nickname)
			return true;
	return false;
}

Client* Server::getClientByNick(const std::string& nickname) {
	for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second.getNickname() == nickname)
			return &it->second;
	return NULL;
}

const Client* Server::getClientByNick(const std::string& nickname) const {
	for (std::map<int, Client>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second.getNickname() == nickname)
			return &it->second;
	return NULL;
}

void Server::removeChannel(const std::string &name) {
	_channels.erase(name);
}

const std::map<std::string, Channel>& Server::getChannels() const {
	return _channels;
}

void Server::run() {
	std::cout << "[INFO] Listening on port " << _port << "\n";
	_running = true;

	addPollFd(_listenFd, POLLIN);

	std::vector<struct pollfd> _newPfds;
	_newPfds.reserve(32);
	while (!g_signal)
	{
		if (::poll(&_pfds[0], _pfds.size(), 1000) == -1) {
			if (errno == EINTR && g_signal) break;
			throw std::runtime_error("[ERROR] poll() failed");
		}

		for (size_t i = 0; i < _pfds.size();)
		{
			struct pollfd p = _pfds[i];

			// Nothing to do if no events
			if (!(p.revents & (POLLIN|POLLOUT|POLLERR|POLLHUP))) {
				++i;
				continue;
			}

			// 1. New client connection
			if (p.fd == _listenFd && (p.revents & POLLIN))
			{
				int cfd = accept(_listenFd, 0, 0);
				if (cfd != -1) {
					std::cout << "[INFO] New client connected (fd=" << cfd << ")" << std::endl;
					fcntl(cfd, F_SETFL, O_NONBLOCK);
					_clients[cfd] = Client(cfd);

					struct pollfd neu; neu.fd = cfd; neu.events = POLLIN; neu.revents = 0;
					_newPfds.push_back(neu);

					sendToClient(cfd,"Welcome! Please enter: PASS <password>");
				}
				++i;
				continue;
			}

			// 2. error/closed connection
			if (p.revents & (POLLERR|POLLHUP)) {
				disconnectClient(p.fd);
				delPollFd(p.fd);
				if (i) --i;
				else   ++i;
				continue;
			}

			// 3-A. proxy DCC SEND (listenFd/dataFd)
			if (_tx.count(p.fd)) {
				handleTransferAccept(p.fd);
				++i;
				continue;
			}
			bool handledSend = false;
			for (std::map<int,TxControl>::iterator it=_tx.begin();it!=_tx.end(); ++it) {
				if (it->second.dataFd == p.fd)
				{
					if (p.revents & POLLIN){
						handleTransferSendAck(p.fd);
					}
					if (p.revents & POLLOUT) {
						handleTransferSend(p.fd);
					}
					handledSend = true;
					break;
				}
			}
			if (handledSend) {
				++i;
				continue;
			}

			// 3-B. proxy DCC RECV (connFd)
			if (_rx.count(p.fd) && (p.revents & (POLLIN | POLLHUP))) {
				handleTransferRecv(p.fd);
				++i;
				continue;
			}

			// 4. socket cliente IR
			if (p.revents & POLLIN)
				handleClientInput(p.fd);

			++i;
		}

		// Incorporate new FDs created during the loop
		if (!_newPfds.empty()) {
			_pfds.insert(_pfds.end(), _newPfds.begin(), _newPfds.end());
			_newPfds.clear();
		}
	}
	std::cout << "[INFO] Server shutting down...\n";
}
