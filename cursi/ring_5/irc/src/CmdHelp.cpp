// Comando HELP:
// Sintaxis:
//   HELP
//
// Numerics enviados:
//   200 RPL_HELPSTART      :Help information
//   201 RPL_HELPTEXT       :<text>
//   202 RPL_ENDOFHELP      :End of help information
// Errores:
//   451 ERR_NOTREGISTERED  (cliente no registrado)

#include "CliCmdHandler.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Messages.hpp"
#include <map>

void CliCmdHandler::handleHelp(Client& sender, std::vector<std::string>& args) {
	if (!sender.isRegistered()) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NOTREGISTERED, sender.getNickname(), "HELP :You have not registered"));
		return;
	}

	if (args.size() > 1) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(), "HELP :Syntax error - HELP [command]"));
		return;
	}

	// Tabla de ayuda por comando
	std::map<std::string, std::string> helpMap;
	helpMap["HELP"]    = "HELP [command] :Show general or specific help";
	helpMap["INFO"]    = "INFO [command] :Show general or specific Info";
	helpMap["NICK"]    = "NICK <nickname> :Set your nickname";
	helpMap["USER"]    = "USER <username> <hostname> <servername> <realname> :Register user";
	helpMap["JOIN"]    = "JOIN <#channel> :Join a channel";
	helpMap["PART"]    = "PART <#channel> :Leave a channel";
	helpMap["PRIVMSG"] = "PRIVMSG <target> <message> :Send a private message";
	helpMap["KICK"]    = "KICK <#channel> <nick> [:reason] :Kick a user from a channel";
	helpMap["INVITE"]  = "INVITE <nick> <#channel> :Invite a user to a channel";
	helpMap["TOPIC"]   = "TOPIC <#channel> [:topic] :Set or view channel topic";
	helpMap["MODE"]    = "MODE <target> <modes> :Change modes for a user or channel";
	helpMap["LIST"]    = "LIST :List available channels";
	helpMap["WHOIS"]   = "WHOIS <nick> :Get info about a user";
	helpMap["WHO"]   = "WHO <channel> :Get info about a channel";
	helpMap["NAMES"]   = "NAMES <#channel> :List users in a channel";
	helpMap["BOT"]     = "BOT :Interact with the IRC bot";

	_server.sendToClient(sender.getFd(),
		buildReply(RPL_HELPSTART, sender.getNickname(), "HELP :Help information"));

	if (args.size() == 1) {
		std::string cmd = args[1];
		std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
		std::map<std::string, std::string>::iterator it = helpMap.find(cmd);
		if (it != helpMap.end()) {
			_server.sendToClient(sender.getFd(),
				buildReply(RPL_HELPTEXT, sender.getNickname(), "HELP :" + it->second));
		} else {
			_server.sendToClient(sender.getFd(),
				buildReply(ERR_UNKNOWNCOMMAND, sender.getNickname(), cmd + " :Unknown command"));
		}
	} else {
		std::string availableCmds = "Available commands: ";
		for (std::map<std::string, std::string>::const_iterator it = helpMap.begin(); it != helpMap.end(); ++it) {
			if (it != helpMap.begin())
				availableCmds += ", ";
			availableCmds += it->first;
		}
		_server.sendToClient(sender.getFd(),
			buildReply(RPL_HELPTEXT, sender.getNickname(), "HELP :" + availableCmds));
	}

	_server.sendToClient(sender.getFd(),
		buildReply(RPL_ENDOFHELP, sender.getNickname(), "HELP :End of HELP information"));
}
