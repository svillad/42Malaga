// Comando WHOIS:
// Sintaxis:
//   WHO
//
// Numerics enviados:
//   311 RPL_WHOISUSER      <nick> <user> localhost * :<realname>
//   318 RPL_ENDOFWHOIS     <nick> :End of WHO list
// Errores:
//   451 ERR_NOTREGISTERED  (cliente no registrado)

#include "CliCmdHandler.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Messages.hpp"

#include <sstream>
void CliCmdHandler::handleWho(Client &requester, std::vector<std::string> &args)
{
	if (!requester.isRegistered()) {
		_server.sendToClient(requester.getFd(),
			buildReply(ERR_NOTREGISTERED, requester.getNickname(),
					   "WHO :You have not registered"));
		return;
	}
	if (args.size() > 1) {
		_server.sendToClient(requester.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, requester.getNickname(),
					   "WHO :Syntax error – WHO [<#channel>]"));
		return;
	}

	bool byChannel = !args.empty();
	const Channel *chan = 0;

	if (byChannel) {
		const std::string &channelName = args[0];

		if (!_server.channelExists(channelName)) {
			_server.sendToClient(requester.getFd(),
				buildReply(ERR_NOSUCHCHANNEL, requester.getNickname(),
						   channelName + " :No such channel"));
			return;
		}
		chan = _server.getChannel(channelName);

		const std::set<int> &members = chan->getAllUsers();
		for (std::set<int>::const_iterator it = members.begin();
			 it != members.end(); ++it)
		{
			const Client &c = _server.getClient(*it);

			std::string nickField = chan->isOperator(*it) ? ("@" + c.getNickname()) : c.getNickname();
			std::string line = nickField + " " 
							 + c.getUsername() + " "
							 + "localhost * :"
							 + c.getRealname();

			_server.sendToClient(requester.getFd(),
				buildReply(RPL_WHOISUSER, requester.getNickname(), line));
		}

		_server.sendToClient(requester.getFd(),
			buildReply(RPL_ENDOFWHO, requester.getNickname(),
					   chan->getName() + " :End of WHO list"));
		return;
	}

	const std::map<int, Client> &all = _server.getClients();
	for (std::map<int, Client>::const_iterator it = all.begin();
		 it != all.end(); ++it)
	{
		const Client &c = it->second;

		std::string line = c.getNickname() + " "
						 + c.getUsername() + " localhost * :"
						 + c.getRealname();

		_server.sendToClient(requester.getFd(),
			buildReply(RPL_WHOISUSER, requester.getNickname(), line));
	}
	_server.sendToClient(requester.getFd(),
		buildReply(RPL_ENDOFWHO, requester.getNickname(),
				   "* :End of WHO list"));
}
