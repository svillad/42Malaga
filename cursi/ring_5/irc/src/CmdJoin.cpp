// Comando JOIN:
// Sintaxis:
//   JOIN <#canal> [<clave>]
//
// Reglas / Códigos de error:
//  - Si el usuario no está registrado:           ERR_NOTREGISTERED   (451)
//  - Si faltan parámetros:                       ERR_NEEDMOREPARAMS  (461)
//  - Nombre de canal inválido:                   ERR_NOSUCHCHANNEL   (403)
//  - Ya está en el canal:                        ERR_USERONCHANNEL   (443)
//  - Canal con +i y no invitado:                 ERR_INVITEONLYCHAN  (473)
//  - Canal con clave y clave incorrecta/faltante:ERR_BADCHANNELKEY   (475)
//  - Canal con límite y está lleno:              ERR_CHANNELISFULL   (471)
//
// Efecto:
//  - Si el canal no existe, se crea y el primer usuario pasa a ser operador.
//  - Se difunde "JOIN" a todos los miembros.
//  - Se envían replies de TOPIC (331/332) y NAMES (353/366) al nuevo miembro.

#include "Messages.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "CliCmdHandler.hpp"

void CliCmdHandler::handleJoin(Client& client, const std::vector<std::string>& args) {
	if (!client.isRegistered()) {
		_server.sendToClient(client.getFd(), buildReply(ERR_NOTREGISTERED, client.getNickname(), "JOIN :You have not registered"));
		return;
	}

	if (args.empty()) {
		_server.sendToClient(client.getFd(), buildReply(ERR_NEEDMOREPARAMS, client.getNickname(), "JOIN :Not enough parameters"));
		return;
	}

	if (args.size() > 2) {
		_server.sendToClient(client.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, client.getNickname(), "JOIN :Syntax error - JOIN <#channel> [<key>]"));
		return;
	}

	std::string chanName = args[0];

	// Validación de nombre de canal
	if (chanName[0] != '#') {
		_server.sendToClient(client.getFd(), buildReply(ERR_NOSUCHCHANNEL, client.getNickname(), chanName + " :Invalid channel name"));
		return;
	}

	if (args[0].size() < 2 || args[0].size() > 50) {
		_server.sendToClient(client.getFd(), buildReply(ERR_NOSUCHCHANNEL, client.getNickname(), chanName + " :Invalid channel name"));
		return;
	}

	Channel* channel = _server.getChannel(chanName);
	if (!channel) {
		channel = &_server.createChannel(chanName);
		channel->addUser(client.getFd(), true); // Primer usuario = operador
	} else {
		if (channel->isUserInChannel(client.getFd())) {
			_server.sendToClient(client.getFd(), buildReply(ERR_USERONCHANNEL, client.getNickname(), chanName + " :You are already on channel"));
			return;
		}

		if (channel->isInviteOnly() && !channel->isUserInvited(client.getFd())) {
			_server.sendToClient(client.getFd(), buildReply(ERR_INVITEONLYCHAN, client.getNickname(), chanName + " :Cannot join channel (+i)"));
			return;
		}

		if (channel->hasPassword()) {
			if (args.size() < 2 || !channel->checkPassword(args[1])) {
				_server.sendToClient(client.getFd(), buildReply(ERR_BADCHANNELKEY, client.getNickname(), chanName + " :Cannot join channel (+k)"));
				return;
			}
		}

		if (channel->isFull()) {
			_server.sendToClient(client.getFd(), buildReply(ERR_CHANNELISFULL, client.getNickname(), chanName + " :Cannot join channel (+l)"));
			return;
		}

		channel->addUser(client.getFd());
	}

	// Confirmación JOIN
	std::string prefix = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost";
	std::string joinMsg = prefix + " JOIN " + chanName + "\r\n";
	channel->broadcast(_server, joinMsg);

	// Topic
	if (!channel->getTopic().empty()) {
		_server.sendToClient(client.getFd(), buildReply(RPL_TOPIC, client.getNickname(), chanName + " :" + channel->getTopic()));
	} else {
		_server.sendToClient(client.getFd(), buildReply(RPL_NOTOPIC, client.getNickname(), chanName + " :No topic is set"));
	}

	// Names
	std::string names = "";
	const std::set<int>& users = channel->getAllUsers();
	for (std::set<int>::const_iterator it = users.begin(); it != users.end(); ++it) {
		const Client& c = _server.getClient(*it);
		if (channel->isOperator(*it))
			names += "@" + c.getNickname() + " ";
		else
			names += c.getNickname() + " ";
	}

	_server.sendToClient(client.getFd(), buildReply(RPL_NAMREPLY, client.getNickname(), "= " + chanName + " :" + names));
	_server.sendToClient(client.getFd(), buildReply(RPL_ENDOFNAMES, client.getNickname(), chanName + " :End of NAMES list"));
}
