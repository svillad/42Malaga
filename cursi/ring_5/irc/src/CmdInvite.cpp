// Comando INVITE
// Sintaxis:
//   INVITE <nick> <#canal>
//
// Reglas / Códigos de error manejados:
//  - Si el usuario no está registrado:           ERR_NOTREGISTERED   (451)
//  - Si faltan parámetros:                       ERR_NEEDMOREPARAMS  (461)
//  - Si el nick no existe:                       ERR_NOSUCHNICK      (401)
//  - Si el canal no existe:                      ERR_NOSUCHCHANNEL   (403)
//  - Si el emisor no está en el canal:           ERR_NOTONCHANNEL    (442)
//  - Si el invitado ya está en el canal:         ERR_USERONCHANNEL   (443)
//  - Si el canal es +i y emisor no es operador:  ERR_CHANOPRIVSNEEDED(482)
//
// Efecto:
//  - Añade al invitado a la lista de invitados del canal (Channel::inviteUser).
//  - Envío al target:    ":<inviter> INVITE <nick> :<canal>\r\n"
//  - Respuesta al inviter: RPL_INVITING (341)

#include "CliCmdHandler.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Messages.hpp"

static std::string prefixFor(const Client &c) {
	return c.getNickname() + "!" + c.getUsername() + "@localhost";
}

void CliCmdHandler::handleInvite(Client &sender, std::vector<std::string> &args) {
	if (!sender.isRegistered()) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NOTREGISTERED, sender.getNickname(), "INVITE :You have not registered"));
		return;
	}

	if (args.size() < 2) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(), "INVITE :Not enough parameters"));
		return;
	}

	if (args.size() > 2) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(), "INVITE :Syntax error - INVITE <nick> <#channel>"));
		return;
	}

	const std::string &targetNick = args[0];
	const std::string &chanName   = args[1];

	Client *target = _server.getClientByNick(targetNick);
	if (!target) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NOSUCHNICK, sender.getNickname(), targetNick + " :No such nick"));
		return;
	}

	Channel *channel = _server.getChannel(chanName);
	if (!channel) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NOSUCHCHANNEL, sender.getNickname(), chanName + " :No such channel"));
		return;
	}

	if (!channel->isUserInChannel(sender.getFd())) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NOTONCHANNEL, sender.getNickname(), chanName + " :You're not on that channel"));
		return;
	}

	if (channel->isUserInChannel(target->getFd())) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_USERONCHANNEL, sender.getNickname(), targetNick + " " + chanName + " :User already on channel"));
		return;
	}

	if (channel->isInviteOnly() && !channel->isOperator(sender.getFd())) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_CHANOPRIVSNEEDED, sender.getNickname(), chanName + " :You're not channel operator"));
		return;
	}

	channel->inviteUser(target->getFd());

	std::string rawInvite = ":" + prefixFor(sender) + " INVITE " + targetNick + " :" + chanName + "\r\n";
	_server.sendToClient(target->getFd(), rawInvite);

	_server.sendToClient(sender.getFd(),
		buildReply(RPL_INVITING, sender.getNickname(), targetNick + " " + chanName));
}
