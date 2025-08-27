#include "Messages.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "CliCmdHandler.hpp"

void CliCmdHandler::handlePass(Client& client, const std::vector<std::string>& args) {
	if (client.isRegistered()) {
		_server.sendToClient(client.getFd(),
			buildReply(ERR_ALREADYREGISTERED, client.getNickname(), "You may not reregister"));
		return;
	}

	if (client.isAuthenticated()) {
		_server.sendToClient(client.getFd(), "[INFO] Password already accepted");
		return;
	}

	if (args.empty()) {
		_server.sendToClient(client.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, "*", "PASS :Not enough parameters"));
		return;
	}

	if (args[0] != _server.getPassword()) {
		_server.sendToClient(client.getFd(),
			buildReply(ERR_PASSWDMISMATCH, "*", "Password incorrect"));
		return;
	}

	client.setAuthenticated(true);
	_server.sendToClient(client.getFd(), "Password accepted");
	_server.sendToClient(client.getFd(), "Please enter: NICK <nickname>");
}

void CliCmdHandler::handleNick(Client& client, const std::vector<std::string>& args) {
	bool nickExists = false;
	if (client.isRegistered()) {
			nickExists = true;
	}

	if (!client.isAuthenticated()) {
		_server.sendToClient(client.getFd(), "NICK :Please enter PASS first");
		return;
	}

	if (args.empty()) {
		_server.sendToClient(client.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, "*", "NICK :No nickname given"));
		return;
	}

	if (args.size() > 1) {
		_server.sendToClient(client.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, client.getNickname(), "NICK : Syntax error - NICK <nickname>"));
		return;
	}

	std::string nick = args[0];
	const std::string invalidChars = " ,*?!@";
	const std::string invalidStart = "$:#&~%+";

	if (nick.find_first_of(invalidChars) != std::string::npos ||
		invalidStart.find(nick[0]) != std::string::npos) {
		_server.sendToClient(client.getFd(),
			buildReply(ERR_ERRONEUSNICKNAME, "*", nick + " :Erroneous nickname"));
		return;
	}

	// Verificar si el nick ya está en uso
	const std::map<int, Client>& clients = _server.getClients();
	for (std::map<int, Client>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
		if (it->second.getNickname() == nick) {
			_server.sendToClient(client.getFd(),
				buildReply(ERR_NICKNAMEINUSE, "*", nick + " :Nickname is already in use"));
			return;
		}
	}

	client.setNickname(nick);
	client.setHasNick(true);
	_server.sendToClient(client.getFd(), "Nickname set to " + nick);
	if (!nickExists) {
		_server.sendToClient(client.getFd(), "Please enter: USER <username>");

		if (client.isAuthenticated() && client.hasNick() && client.hasUser()) {
			client.setRegistered(true);
			sendWelcome(client);
		}
	}
}

void CliCmdHandler::handleUser(Client& client, const std::vector<std::string>& args) {
	if (client.isRegistered()) {
		_server.sendToClient(client.getFd(),
			buildReply(ERR_ALREADYREGISTERED, client.getNickname(), "You may not reregister"));
		return;
	}

	if (!client.isAuthenticated()) {
		_server.sendToClient(client.getFd(), "USER :Please enter PASS first");
		return;
	}

	if (!client.hasNick()) {
		_server.sendToClient(client.getFd(), "USER :Please enter NICK first");
		return;
	}

	if (args.empty()) {
		_server.sendToClient(client.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, client.getNickname(), "USER :Not enough parameters"));
		return;
	}

	if (args.size() != 1 && args.size() != 4) {
		_server.sendToClient(client.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, client.getNickname(), "USER : Syntax error - USER <username> [<hostname> <servername> :<realname>]"));
		return;
	}

	if (client.hasUser()) {
		_server.sendToClient(client.getFd(), "[INFO] USER already set");
		return;
	}

	std::string username = args[0];
	std::string hostname = args.size() > 1 ? args[1] : "localhost";
	std::string servername = args.size() > 2 ? args[2] : "*";
	std::string realname = args.size() > 3 ? args[3] : "Unknown";

	client.setUsername(args[0]);
	client.setRealname(realname);
	client.setHasUser(true);
	_server.sendToClient(client.getFd(), "Username set to " + username +
		", hostname: " + hostname + ", servername: " + servername +
		", realname: " + realname);

	if (client.isAuthenticated() && client.hasNick() && client.hasUser()) {
		client.setRegistered(true);
		sendWelcome(client);
	}
}
