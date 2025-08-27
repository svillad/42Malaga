// src/handlers/cmd_list.cpp
// -------------------------
// Comando LIST – muestra los canales visibles
// Sintaxis:
//   LIST                 todos los canales visibles
//   LIST <#chan1,#chan2> sólo esos canales
//
// Visibilidad según modos:
//   - +s (secret): el canal NO aparece en LIST a quien no sea miembro.
//   - +p (private): aparece pero sin topic, y opcionalmente sin users (usamos users=0).
//
// Respuestas:
//   321 RPL_LISTSTART   (opcional)
//   322 RPL_LIST   <nick> <#chan> <users> :<topic>
//   323 RPL_LISTEND
//
// Implementación mínima:
//   • Sin parámetros: iterar mapa _channels y decidir visibilidad.
//   • Con parámetros: split "," y filtrar.
//   • users = channel.getAllUsers().size();   (o 0 si +p y externo)
//
// Dependencias
#include "CliCmdHandler.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Messages.hpp"

#include <sstream>
#include <set>

static std::set<std::string> splitListTargets(const std::string& csv) {
	std::set<std::string> out;
	std::string token;
	std::istringstream iss(csv);
	while (std::getline(iss, token, ','))
		out.insert(token);
	return out;
}

void CliCmdHandler::handleList(Client& requester, std::vector<std::string>& args) {
	if (!requester.isRegistered()) {
		_server.sendToClient(requester.getFd(),
			buildReply(ERR_NOTREGISTERED, requester.getNickname(), "LIST :You have not registered"));
		return;
	}

	if (args.size() > 1) {
		_server.sendToClient(requester.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, requester.getNickname(), "LIST : Syntax error - LIST [<#channel1>,<#channel2>,...]"));
		return;
	}

	std::set<std::string> filter;
	if (!args.empty())
		filter = splitListTargets(args[0]);

	_server.sendToClient(requester.getFd(),
		buildReply(RPL_LISTSTART, requester.getNickname(), "Channel Users :Topic"));

	const std::map<std::string, Channel>& chans = _server.getChannels();
	for (std::map<std::string, Channel>::const_iterator it = chans.begin(); it != chans.end(); ++it) {
		const Channel& ch = it->second;
		const std::string& name = ch.getName();

		if (!filter.empty() && filter.find(name) == filter.end())
			continue;

		bool isMember = ch.isUserInChannel(requester.getFd());

		if (ch.isSecret() && !isMember)
			continue;

		int users = static_cast<int>(ch.getAllUsers().size());
		std::string topic = ch.getTopic();

		if (ch.isPrivate() && !isMember) {
			topic = "";
			users = 0;
		}

		std::ostringstream oss;
		oss << name << " " << users << " :" << topic;
		_server.sendToClient(requester.getFd(),
			buildReply(RPL_LIST, requester.getNickname(), oss.str()));
	}

	_server.sendToClient(requester.getFd(),
		buildReply(RPL_LISTEND, requester.getNickname(), ":End of CHANNEL List"));
}
