// Comando WHOIS:
// Sintaxis:
//   WHOIS <nick>
//
// Numerics enviados:
//   311 RPL_WHOISUSER      <nick> <user> localhost * :<realname>
//   319 RPL_WHOISCHANNELS  <nick> :@#chan1 #chan2 +#chan3
//   318 RPL_ENDOFWHOIS     <nick> :End of WHOIS list
// Errores:
//   451 ERR_NOTREGISTERED  (cliente no registrado)
//   431 ERR_NONICKNAMEGIVEN (sin parámetro)
//   401 ERR_NOSUCHNICK     (nick no existe)

#include "CliCmdHandler.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Messages.hpp"

#include <sstream>

void CliCmdHandler::handleWhois(Client &requester, std::vector<std::string> &args) {
	if (!requester.isRegistered()) {
		_server.sendToClient(requester.getFd(),
			buildReply(ERR_NOTREGISTERED, requester.getNickname(), "WHOIS :You have not registered"));
		return;
	}

	if (args.empty()) {
		_server.sendToClient(requester.getFd(),
			buildReply(ERR_NONICKNAMEGIVEN, requester.getNickname(), "WHOIS :No nickname given"));
		return;
	}

	if (args.size() > 1) {
		_server.sendToClient(requester.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, requester.getNickname(), "WHOIS : Syntax error - WHOIS <nick>"));
		return;
	}

	const std::string &targetNick = args[0];
	Client *target = _server.getClientByNick(targetNick);
	if (!target) {
		_server.sendToClient(requester.getFd(),
			buildReply(ERR_NOSUCHNICK, requester.getNickname(), targetNick + " :No such nick"));
		return;
	}

	std::string whoUser = target->getNickname() + " "
					+ target->getUsername() + " "
					+ "localhost * :"
					+ target->getRealname();
	_server.sendToClient(requester.getFd(),
		buildReply(RPL_WHOISUSER, requester.getNickname(), whoUser));
	
	std::string chanList;
	for (std::map<std::string, Channel>::const_iterator it = _server.getChannels().begin();
		it != _server.getChannels().end(); ++it) {
		const Channel& channel = it->second;
		if (!channel.isUserInChannel(target->getFd()))
			continue;

		bool requesterInside = channel.isUserInChannel(requester.getFd());

		if (channel.isSecret() && !requesterInside)
			continue;

		std::string entry;
		if (channel.isOperator(target->getFd()))
			entry += '@';

		if (channel.isPrivate() && !requesterInside)
			entry += '*';

		entry += channel.getName();
		chanList += entry + " ";
	}

	if (!chanList.empty())
		_server.sendToClient(requester.getFd(),
			buildReply(RPL_WHOISCHANNELS, requester.getNickname(), targetNick + " :" + chanList));

	_server.sendToClient(requester.getFd(),
		buildReply(RPL_ENDOFWHOIS, requester.getNickname(), target->getNickname() + " :End of WHOIS list"));
}
