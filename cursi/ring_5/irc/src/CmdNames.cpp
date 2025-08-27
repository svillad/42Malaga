// Comando NAMES
// Sintaxis:
//   NAMES                 todos los canales visibles + usuarios sin canal
//   NAMES <#chan1,#chan2> sólo esos canales
//
// Reglas de visibilidad:
//   - +s (secret): sólo se muestra si el solicitante ES miembro.
//   - +p (private): si solicitante fuera ⇒ lista normal; si no ⇒ lista vacía (`353` sin nicks).
//
// Numeric replies:
//   353 RPL_NAMREPLY  <nick> (=|*) <#chan> :[@]User1 [+]User2 User3
//   366 RPL_ENDOFNAMES <nick> <#chan> :End of NAMES list
//   366 con canal "*" marca fin de la lista de usuarios sin canal.

#include "CliCmdHandler.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Messages.hpp"

#include <sstream>
#include <set>

static std::set<std::string> splitTargets(const std::string& csv) {
	std::set<std::string> out; std::string tok; std::istringstream iss(csv);
	while (std::getline(iss, tok, ',')) out.insert(tok);
	return out;
}

static void buildNamesList(const Channel& channel, const Server& server, std::string& out) {
	for (std::set<int>::const_iterator it = channel.getAllUsers().begin();
		 it != channel.getAllUsers().end(); ++it) {
		const Client& c = server.getClient(*it);
		if (!out.empty())
			out += " ";
		if (channel.isOperator(*it))
			out += "@";
		out += c.getNickname();
	}
}

void CliCmdHandler::handleNames(Client& requester, std::vector<std::string>& args) {
	if (!requester.isRegistered()) {
		_server.sendToClient(requester.getFd(),
			buildReply(ERR_NOTREGISTERED, requester.getNickname(), "NAMES :You have not registered"));
		return;
	}

	if (args.size() > 1) {
		_server.sendToClient(requester.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, requester.getNickname(), "NAMES : Syntax error - NAMES [<#channel1>,<#channel2>,...]"));
		return;
	}

	std::set<std::string> filter;
	if (!args.empty())
		filter = splitTargets(args[0]);

	_server.sendToClient(requester.getFd(),
		buildReply(RPL_NAMSTART, requester.getNickname(), "Symbol Channel :Nicknames"));

	const std::map<std::string, Channel>& chans = _server.getChannels();

	for (std::map<std::string, Channel>::const_iterator it = chans.begin(); it != chans.end(); ++it) {
		const Channel& channel = it->second;
		const std::string& name = channel.getName();

		if (!filter.empty() && filter.find(name) == filter.end())
			continue;

		bool isMember = channel.isUserInChannel(requester.getFd());

		if (channel.isSecret() && !isMember)
			continue;

		std::string list;
		if (isMember || !channel.isPrivate())
			buildNamesList(channel, _server, list);

		char symbol = '=';
		if (name.size() && name[0] == '#') symbol = isMember ? '=' : '*';
		if (isMember) channel.isSecret() ? symbol = '@' : symbol = '=';

		_server.sendToClient(requester.getFd(),
			buildReply(RPL_NAMREPLY, requester.getNickname(), std::string(1, symbol) + " " + name + " :" + list));
		_server.sendToClient(requester.getFd(),
			buildReply(RPL_ENDOFNAMES, requester.getNickname(), name + " :End of NAMES list"));
	}

	if (filter.empty()) {
		std::string list;
		const std::map<int, Client>& clients = _server.getClients();
		for (std::map<int, Client>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
			int fd = it->first;
			bool inChannel = false;
			for (std::map<std::string, Channel>::const_iterator cIt = chans.begin(); cIt != chans.end() && !inChannel; ++cIt)
				if (cIt->second.isUserInChannel(fd)) inChannel = true;
			if (!inChannel) {
				if (!list.empty()) list += " ";
				list += it->second.getNickname();
			}
		}
		if (!list.empty()) {
			_server.sendToClient(requester.getFd(),
				buildReply(RPL_NAMREPLY, requester.getNickname(), "* * :" + list));
			_server.sendToClient(requester.getFd(),
				buildReply(RPL_ENDOFNAMES, requester.getNickname(), "* :End of NAMES list"));
		}
	}
}