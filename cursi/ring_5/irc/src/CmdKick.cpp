// Comando KICK:
// Sintaxis:
//   KICK <#canal> <nick> [:motivo opcional]
//
// Reglas / Códigos de error:
//  - Solo los operadores del canal pueden expulsar.
//  - Si el nick no existe:             ERR_NOSUCHNICK (401)
//  - Si el canal no existe:            ERR_NOSUCHCHANNEL (403).
//  - Si el emisor no es operador:      ERR_CHANOPRIVSNEEDED (482).
//  - Si el target no está en el canal: ERR_USERNOTINCHANNEL (441).
//
// Efecto:
//  - Enviar mensaje KICK a todos los miembros (Channel::broadcast).
//  - El objetivo sale del canal. Si el canal queda vacío, se borra.
//  - Si tras el KICK no quedan operadores pero sí miembros, se promociona
//    automáticamente al miembro más antiguo (primer fd) y se difunde un
//    MODE +o.
//  - Si el canal queda vacío, se elimina.

#include "CliCmdHandler.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Messages.hpp"

static const std::string DEFAULT_REASON = "Kicked";

void CliCmdHandler::handleKick(Client &sender, std::vector<std::string> &args) {
	if (!sender.isRegistered()) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NOTREGISTERED, sender.getNickname(), "KICK :You have not registered"));
		return;
	}

	if (args.size() < 2) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(), "KICK :Not enough parameters"));
		return;
	}

	if (args.size() > 3) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(), "KICK : Syntax error - KICK <#channel> <nick> [:reason]"));
		return;
	}

	const std::string &chanName   = args[0];
	const std::string &targetNick = args[1];

	Channel *channel = _server.getChannel(chanName);
	if (!channel) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NOSUCHCHANNEL, sender.getNickname(), chanName + " :No such channel"));
		return;
	}

	if (!channel->isOperator(sender.getFd())) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_CHANOPRIVSNEEDED, sender.getNickname(), chanName + " :You're not channel operator"));
		return;
	}

	Client *target = _server.getClientByNick(targetNick);
	if (!target) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NOSUCHNICK, sender.getNickname(), targetNick + " :No such nick"));
		return;
	}

	if (!channel->isUserInChannel(target->getFd())) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_USERNOTINCHANNEL, sender.getNickname(), targetNick + " " + chanName + " :User not in channel"));
		return;
	}

	std::string reason = DEFAULT_REASON;
	if (args.size() >= 3) {
		reason.clear();
		for (size_t i = 2; i < args.size(); ++i) {
			if (i > 2) reason += " ";
			reason += args[i];
		}
	}

	std::ostringstream oss;
	oss << ":" << sender.getNickname()
		<< " KICK " << chanName << " " << targetNick << " :" << reason << "\r\n";
	std::string kickMsg = oss.str();

	channel->broadcast(_server, kickMsg);
	channel->removeUser(target->getFd());

	if (channel->getAllUsers().empty())
		_server.removeChannel(chanName);

	if (!channel->getAllUsers().empty()) {
		int newOpFd = channel->promoteFirstMemberToOperator();

		if (newOpFd == -2) {
			channel->removeUser(-2);
			_server.removeChannel(chanName);
		}
		else if (newOpFd != -1) {
			const Client& promoted = _server.getClient(newOpFd);
			std::string modeMsg = ":" + sender.getNickname() + " MODE " +
								chanName + " +o " + promoted.getNickname() + "\r\n";
			channel->broadcast(_server, modeMsg);
		}
	}
}
