#include "CliCmdHandler.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Messages.hpp"

#include <iomanip>

std::vector<std::string> CliCmdHandler::split(const std::string& line) {
	std::vector<std::string> out;
	std::istringstream iss(line);
	std::string token;

	while (iss >> token) {
		if (token[0] == ':') {
			std::string rest;
			std::getline(iss, rest);
			std::string param = token.substr(1);

			if (!param.empty()) {
				param += rest;
			} else {
				if (!rest.empty() && rest[0] == ' ')
					rest.erase(0, 1);
				param = rest;
			}
			out.push_back(param);
			break;
		}
		out.push_back(token);
	}
	return out;
}

std::string CliCmdHandler::toUpper(const std::string& str) {
	std::string result = str;
	for (size_t i = 0; i < result.length(); ++i)
		result[i] = std::toupper(static_cast<unsigned char>(result[i]));
	return result;
}

void CliCmdHandler::sendWelcome(Client& client) {
	std::string nick = client.getNickname();
	std::string user = client.getUsername();

	_server.sendToClient(client.getFd(), buildReply(RPL_WELCOME, nick, "Welcome to the IRC Network, " + nick + "!" + user + "@localhost"));
	_server.sendToClient(client.getFd(), buildReply(RPL_YOURHOST, nick, "Your host is localhost, running version 1.0"));
	_server.sendToClient(client.getFd(), buildReply(RPL_CREATED, nick, "This server was created just now"));
	_server.sendToClient(client.getFd(), buildReply(RPL_MYINFO, nick, "localhost 1.0 o o"));

	_server.sendToClient(client.getFd(), buildReply(RPL_HIGHESTCONNCOUNT, nick, "Highest connection count: " + to_string(_server.getMaxClientCount())));
	_server.sendToClient(client.getFd(), buildReply(RPL_LUSERCHANNELS, nick, "Currently " + to_string(_server.getChannelsCount()) + " channels on the server"));
	_server.sendToClient(client.getFd(), buildReply(RPL_LUSERUSERS, nick, "Currently " + to_string(_server.getConnectedClientsCount()) + " users on the server"));
}

std::string CliCmdHandler::buildReply(int code, const std::string& nick, const std::string& message) {
	std::ostringstream oss;
	oss << ":localhost "
		<< std::setw(3) << std::setfill('0') << code << ' '
		<< (nick.empty() ? "*" : nick) << " " << message << "\r\n";
	return oss.str();
}


CliCmdHandler::CliCmdHandler(Server& server) : _server(server) {}

void CliCmdHandler::callJoin(Client& cl, const std::vector<std::string>& args) {
	handleJoin(cl, args);
}

int CliCmdHandler::detectShortcutForBot(Client &cli, int clientFd,  std::vector<std::string> &tokens, std::string &cmd) {
	if (tokens.empty() || tokens[0].empty() || tokens[0][0] != '!') {
		cmd = toUpper(tokens[0]);
		tokens.erase(tokens.begin());
		return 0;
	}

	if (tokens[0].size() == 1) {
		_server.sendToClient(clientFd,
			buildReply(ERR_UNKNOWNCOMMAND, cli.getNickname(), ":Unknown command"));
		return -1;
	}

	tokens[0] = toUpper(tokens[0].substr(1));
	cmd = "BOT";
	return 1;
}

void CliCmdHandler::handle(int clientFd, const std::string& message) {
	Client& client = _server.getClient(clientFd);
	std::vector<std::string>tokens = split(message);

	if (tokens.empty())
		return;

	std::string cmd;
	int bangState = detectShortcutForBot(client, clientFd, tokens, cmd);
	if (bangState == -1)
		return;

	std::cout << " Command: " << cmd << std::endl;
	std::cout << " tokens received: "	<< tokens.size() << std::endl;
	for (size_t i = 0; i < tokens.size(); i++) {
		std::cout << "  token[" << i << "]: " << tokens[i] << std::endl;
	}

	if (cmd == "PASS")
		handlePass(client, tokens);
	else if (cmd == "NICK")
		handleNick(client, tokens);
	else if (cmd == "USER")
		handleUser(client, tokens);
	else if (cmd == "JOIN")
		handleJoin(client, tokens);
	else if (cmd == "PRIVMSG")
		handlePrivmsg(client, tokens);
	else if (cmd == "NOTICE")
		handleNotice(client, tokens);
	else if (cmd == "KICK")
		handleKick(client, tokens);
	else if (cmd == "INVITE")
		handleInvite(client, tokens);
	else if (cmd == "TOPIC")
		handleTopic(client, tokens);
	else if (cmd == "MODE")
		handleMode(client, tokens);
	else if (cmd == "LIST")
		handleList(client, tokens);
	else if (cmd == "WHOIS")
		handleWhois(client, tokens);
	else if (cmd == "WHO")
		handleNames(client, tokens);
	else if (cmd == "NAMES")
		handleNames(client, tokens);
	else if (cmd == "BOT")
		handleBot(client, tokens);
	else if (cmd == "INFO" || cmd == "HELP")
		handleHelp(client, tokens);
	else if (cmd == "QUIT") {
		_server.disconnectClient(clientFd);
	}
	else
		_server.sendToClient(clientFd,
			buildReply(ERR_UNKNOWNCOMMAND, client.getNickname(), cmd + " :Unknown command"));
}