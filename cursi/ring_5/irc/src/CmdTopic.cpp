// Comando TOPIC
// Sintaxis:
//   TOPIC <#canal> [:<nuevo tópico>]
//
// Reglas / Códigos de error manejados:
//  - Si el usuario no está registrado:           ERR_NOTREGISTERED  (451)
//  - Si faltan parámetros:                       ERR_NEEDMOREargs (461)
//  - Si el canal no existe:                      ERR_NOSUCHCHANNEL  (403)
//  - Mostrar tópico:
//      • Si no hay tópico:                       RPL_NOTOPIC (331)
//      • Si existe tópico:                       RPL_TOPIC  (332)
//  - Cambiar tópico:
//      • (Versión simplificada) Solo operadores pueden cambiarlo. Si no lo es:
//            ERR_CHANOPRIVSNEEDED (482)

#include "CliCmdHandler.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Messages.hpp"

void CliCmdHandler::handleTopic(Client& sender, std::vector<std::string>& args) {
	if (!sender.isRegistered()) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NOTREGISTERED, sender.getNickname(), "TOPIC :You have not registered"));
		return;
	}

	if (args.empty()) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(), "TOPIC :Not enough parameters"));
		return;
	}

	if (args.size() > 2) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(), "TOPIC : Syntax error - TOPIC <#channel> [:<new topic>]"));
		return;
	}

	const std::string& chanName = args[0];

	Channel* channel = _server.getChannel(chanName);
	if (!channel) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NOSUCHCHANNEL, sender.getNickname(), chanName + " :No such channel"));
		return;
	}

	if (args.size() == 1) {
		if (channel->getTopic().empty())
			_server.sendToClient(sender.getFd(), buildReply(RPL_NOTOPIC, sender.getNickname(), chanName + " :No topic is set"));
		else
			_server.sendToClient(sender.getFd(), buildReply(RPL_TOPIC,   sender.getNickname(), chanName + " :" + channel->getTopic()));
		return;
	}

	if (!channel->isOperator(sender.getFd())) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_CHANOPRIVSNEEDED, sender.getNickname(), chanName + " :You're not channel operator"));
		return;
	}

	std::string newTopic;
	for (size_t i = 1; i < args.size(); ++i) {
		if (i > 1) newTopic += " ";
		newTopic += args[i];
	}

	channel->setTopic(newTopic);

	std::string prefix = ":" + sender.getNickname() + "!" + sender.getUsername() + "@localhost";
	std::string topicMsg = prefix + " TOPIC " + chanName + " :" + newTopic + "\r\n";
	channel->broadcast(_server, topicMsg);
}
