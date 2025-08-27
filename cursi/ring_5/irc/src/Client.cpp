#include "Client.hpp"

Client::Client()
	: _fd(-1), _nickname(""), _username(""), _realname(""),
	  _authenticated(false), _hasNick(false),
	  _hasUser(false), _registered(false) {}

Client::Client(int socketFd)
	: _fd(socketFd), _nickname(""), _username(""), _realname(""),
	  _authenticated(false), _hasNick(false),
	  _hasUser(false), _registered(false) {}

Client::~Client() {}

int Client::getFd() const {
	return _fd;
}

const std::string& Client::getNickname() const {
	return _nickname;
}

const std::string& Client::getUsername() const {
	return _username;
}

const std::string& Client::getRealname() const {
	return _realname;
}

bool Client::isAuthenticated() const {
	return _authenticated;
}

bool Client::hasNick() const {
	return _hasNick;
}

bool Client::hasUser() const {
	return _hasUser;
}

bool Client::isRegistered() const {
	return _registered;
}

void Client::setNickname(const std::string& nick) {
	_nickname = nick;
}

void Client::setUsername(const std::string& user) {
	_username = user;
}

void Client::setRealname(const std::string& real) {
	_realname = real;
}

void Client::setAuthenticated(bool auth) {
	_authenticated = auth;
}

void Client::setHasNick(bool hasNick) {
	_hasNick = hasNick;
}

void Client::setHasUser(bool hasUser) {
	_hasUser = hasUser;
}

void Client::setRegistered(bool reg) {
	_registered = reg;
}

void Client::appendToBuffer(const std::string& data) {
	_recvBuffer += data;
}

std::vector<std::string> Client::extractCompleteCommands() {
	std::vector<std::string> commands;
	size_t pos;

	while ((pos = _recvBuffer.find('\n')) != std::string::npos) {
		std::string line = _recvBuffer.substr(0, pos);
		if (!line.empty() && line[line.size() - 1] == '\r') {
			line.erase(line.size() - 1);  // Remove optional \r
		}
		commands.push_back(line);
		_recvBuffer.erase(0, pos + 1);
	}

	return commands;
}
