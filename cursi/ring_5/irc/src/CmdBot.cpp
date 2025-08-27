// Comando BOT
// Sintaxis:
//   BOT <sub‑comando> [args...]
// Ejemplos:
//   BOT help
//   BOT time
//   BOT join #canal
//
// El bot responde por mensaje privado al emisor. No requiere que exista un canal.
// Numerics de error: reutilizamos 461 (NEEDMOREPARAMS) y 401 (NOSUCHNICK) si Bot no está.
//
#include "CliCmdHandler.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Messages.hpp"
#include "BotClient.hpp"

void CliCmdHandler::handleBot(Client& sender, std::vector<std::string>& args) {
	if (!sender.isRegistered()) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NOTREGISTERED, sender.getNickname(), "BOT :You have not registered"));
		return;
	}

	if (args.empty()) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(), "BOT :Missing sub-command"));
		return;
	}

	BotClient* bot = static_cast<BotClient*>(_server.getClientByNick("bot"));
	if (!bot) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NOSUCHNICK, sender.getNickname(), "Bot :Bot not available"));
		return;
	}

	std::string channel;
	std::vector<std::string> words = args;

	for (size_t i = 0; i < words.size(); ++i) {
		if (!words[i].empty() && words[i][0] == '#') {
			channel = words[i];
			words.erase(words.begin() + i);
			break;
		}
	}

	if (words.empty()) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(), "BOT :Missing sub-command"));
		return;
	}

	std::string subCmd = toUpper(words[0]);
	std::vector<std::string> subArgs(words.begin() + 1, words.end());

	bot->handleCommand(sender, channel, subCmd, subArgs, _server);
}
