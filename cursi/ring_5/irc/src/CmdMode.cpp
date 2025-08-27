// Comando MODE
// Sintaxis:
//   MODE <#canal>                    → devuelve los modos actuales
//   MODE <#canal> (+|-)flags [param] → cambia modos
//
// Flags:
//   i  invite-only
//   t  sólo operadores pueden cambiar TOPIC
//   k  contraseña     (+k <key> / -k)
//   o  operador       (+o <nick> / -o <nick>)
//   l  límite users   (+l <n> / -l)
//   p  canal privado  (+p / -p)
//   s  canal secreto  (+s / -s)
//
// Códigos de error manejados
//   451 ERR_NOTREGISTERED         (no ha terminado PASS/NICK/USER)
//   461 ERR_NEEDMOREPARAMS        (falta canal o flag)
//   403 ERR_NOSUCHCHANNEL         (el canal no existe)
//   442 ERR_NOTONCHANNEL          (emisor no está en el canal)
//   482 ERR_CHANOPRIVSNEEDED      (no es operador para cambiar)
//   467 ERR_KEYSET                (clave ya establecida +k)
//   441 ERR_USERNOTINCHANNEL      (-o nick no está)
//   324 RPL_CHANNELMODEIS         (respuesta a consulta)

#include "CliCmdHandler.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Messages.hpp"

#include <sstream>

static std::string prefix(const Client& c) {
	return c.getNickname() + "!" + c.getUsername() + "@localhost";
}

static bool isBot(const Client& c) {
	return c.getFd() == -2;
}

static bool isInteger(const std::string &s) {
	if (s.empty()) return false;

	size_t i = 0;
	if (s[0] == '+' || s[0] == '-') {
		if (s.size() == 1) return false;
		i = 1;
	}
	for ( ; i < s.size(); ++i) {
		if (!std::isdigit(static_cast<unsigned char>(s[i])))
			return false;
	}
	return true;
}

static std::string buildModeString(const Channel& ch, std::string* paramsOut = 0) {
	std::string flags;
	if (ch.isInviteOnly())      flags += 'i';
	if (ch.isTopicRestricted()) flags += 't';
	if (ch.hasPassword())       flags += 'k';
	if (ch.getUserLimit() != -1)flags += 'l';
	if (ch.isPrivate())         flags += 'p';
	if (ch.isSecret())          flags += 's';

	if (paramsOut) {
		std::string& p = *paramsOut;
		if (ch.hasPassword())      { p += ' '; p += ch.getPassword(); }
		if (ch.getUserLimit() != -1) { p += ' '; p += to_string(ch.getUserLimit()); }
	}
	return flags;
}

static void buildNamesList(const Channel& ch, const Server&  srv, std::string&   out) {
	for (std::set<int>::const_iterator it = ch.getAllUsers().begin();
		 it != ch.getAllUsers().end(); ++it) {
		const Client& c = srv.getClient(*it);
		if (!out.empty()) out += ' ';
		if (ch.isOperator(*it)) out += '@';
		out += c.getNickname();
	}
}

void CliCmdHandler::sendNamesBurst(const Channel& ch)  {
	std::string list;
	buildNamesList(ch, _server, list);

	const std::string& chan = ch.getName();
	char symbol = ch.isSecret() ? '@' : '=';

	for (std::set<int>::const_iterator it = ch.getAllUsers().begin();
		 it != ch.getAllUsers().end(); ++it) {
		const Client& dst = _server.getClient(*it);
		_server.sendToClient(dst.getFd(),
			buildReply(RPL_NAMSTART, dst.getNickname(),
					   "Symbol Channel :Nicknames"));
		_server.sendToClient(dst.getFd(),
			buildReply(RPL_NAMREPLY,  dst.getNickname(),
					   std::string(1, symbol) + ' ' + chan + " :" + list));
		_server.sendToClient(dst.getFd(),
			buildReply(RPL_ENDOFNAMES,dst.getNickname(),
					   chan+" :End of NAMES list"));
	}
}


void CliCmdHandler::handleMode(Client& sender, std::vector<std::string>& args) {
	if (!sender.isRegistered()) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NOTREGISTERED, sender.getNickname(), "MODE :You have not registered"));
		return;
	}

	if (args.empty()) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(), "MODE :Not enough parameters"));
		return;
	}

	const std::string& chanName = args[0];
	Channel* channel = _server.getChannel(chanName);
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

	if (args.size() == 1) {
		std::string trailing;
		std::string modes = "+" + buildModeString(*channel, &trailing);
		_server.sendToClient(sender.getFd(),
			buildReply(RPL_CHANNELMODEIS, sender.getNickname(), chanName + " " + modes + trailing));
		return;
	}

	if (!channel->isOperator(sender.getFd())) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_CHANOPRIVSNEEDED, sender.getNickname(), chanName + " :You're not channel operator"));
		return;
	}

	const std::string &modeStr = args[1];
	if (modeStr.empty() || (modeStr[0] != '+' && modeStr[0] != '-')) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NEEDMOREPARAMS,
					sender.getNickname(), "MODE :flags must start with '+' or '-'"));
		return;
	}

	bool adding    = true;
	size_t argIdx  = 2;

	std::vector<std::string> broadcasts;

	for (size_t i = 0; i < modeStr.size(); ++i) {
		char c = modeStr[i];
		if (c == '+' || c == '-') {
			adding = (c == '+');
			continue;
		}

		bool ok = false;
		std::ostringstream line;
		line << ':' << prefix(sender) << " MODE " << chanName << ' '
			 << (adding?'+':'-') << c;

		switch (c) {
			/* ---------- i / t / p / s  ---------------- */
			case 'i': channel->setInviteOnly(adding);      ok = true;break;
			case 't': channel->setTopicRestricted(adding); ok = true;break;
			case 'p': channel->setPrivate(adding);         ok = true;break;
			case 's': channel->setSecret(adding);          ok = true;break;

			/* ---------- k (key)  ---------------------- */
			case 'k':
				if (adding) {
					if (channel->hasPassword()) {
						_server.sendToClient(sender.getFd(),
							buildReply(ERR_KEYSET, sender.getNickname(),
									chanName + " :Channel key already set"));
						++argIdx; continue;
					}
					if (argIdx >= args.size()) {
						_server.sendToClient(sender.getFd(),
							buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(),
									"MODE +k :Missing key"));
						return;
					}
					channel->setPassword(args[argIdx]);
					line << ' ' << args[argIdx];
					++argIdx;
				} else {
					channel->clearPassword();
				}
				ok = true;
				break;

			/* ---------- o (operator) ------------------- */
			case 'o':
			{
				if (argIdx >= args.size()) {
					_server.sendToClient(sender.getFd(),
						buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(),
								"MODE +o/-o :Missing nick"));
					return;
				}
				Client* tgt = _server.getClientByNick(args[argIdx]);
				if (!tgt || !channel->isUserInChannel(tgt->getFd())) {
					_server.sendToClient(sender.getFd(),
						buildReply(ERR_USERNOTINCHANNEL, sender.getNickname(),
								args[argIdx] + ' ' + chanName +
								" :They aren't on that channel"));
					++argIdx; break;
				}
				if (adding && isBot(*tgt)) {
					_server.sendToClient(sender.getFd(),
						buildReply(ERR_CHANOPRIVSNEEDED, sender.getNickname(),
								chanName + " :The bot cannot be channel operator"));
					++argIdx; break;
				}
				if (!adding && channel->isOperator(tgt->getFd()) &&
					channel->operatorCount() == 1) {
					_server.sendToClient(sender.getFd(),
						buildReply(ERR_CHANOPRIVSNEEDED, sender.getNickname(),
								chanName + " :You cannot remove the last operator"));
					++argIdx; break;
				}
				bool changed = false;

				if (adding)
					changed = channel->addOperator(tgt->getFd());
				else {
					if (channel->operatorCount() == 1) {
						_server.sendToClient(sender.getFd(),
						buildReply(ERR_CHANOPRIVSNEEDED, sender.getNickname(),
									chanName+" :You cannot remove the last operator"));
					} else
						changed = channel->removeOperator(tgt->getFd());
				}

				if (changed) {
					line << ' ' << args[argIdx];
					sendNamesBurst(*channel);
					ok = true;
				}
				++argIdx;
				break;
			}

			/* ---------- l (limit)  --------------------- */
			case 'l':
				if (adding) {
					if (argIdx >= args.size()) {
						_server.sendToClient(sender.getFd(),
							buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(),
									"MODE +l :Missing limit"));
						return;
					}
					if (!isInteger(args[argIdx])) {
						_server.sendToClient(sender.getFd(),
							buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(),
									"MODE +l :User limit must be an integer"));
						++argIdx; break;
					}
					int lim = std::atoi(args[argIdx].c_str());
					if (lim <= 0) lim = -1;
					channel->setUserLimit(lim);
					line << ' ' << lim;
					++argIdx;
				} else {
					channel->clearUserLimit();
				}
				ok = true;
				break;

			/* ---------- unknown -------------------- */
			default:
				_server.sendToClient(sender.getFd(),
					buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(),
							"MODE :Unknown mode flag '" + std::string(1,c) + '\''));
				continue;
		}

		if (ok) broadcasts.push_back(line.str()+"\r\n");
	}

	/* 3. Send broadcasts ----------------------- */
	for (size_t i = 0; i < broadcasts.size(); ++i)
		channel->broadcast(_server, broadcasts[i]);
}
