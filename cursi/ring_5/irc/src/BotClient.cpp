#include "BotClient.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Messages.hpp"
#include <ctime>
#include <map>
#include <cstdlib>
#include <sstream>

static std::map<int, Game> games;

BotClient::BotClient(int fakeFd) : Client(fakeFd) {
	setNickname("bot");
	setUsername("JamesBot");
	setRegistered(true);
}

std::string BotClient::getTime() const {
	char buf[64];
	std::time_t t = std::time(NULL);
	std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
	return buf;
}

void BotClient::replyMultiline(Client& sender, const std::string& channel, Server& server,
							   const std::string& msg) const {
	std::istringstream iss(msg);
	std::string line;
	while (std::getline(iss, line)) {
		if (!line.empty())
			reply(sender, channel, server, line);
	}
}

void BotClient::handleCommand(Client& sender, const std::string& channel, const std::string& cmd,
							  std::vector<std::string>& args, Server& server) {
	if (cmd == "HELP") {
		cmdHelp(sender, channel, server, args);
	}
	else if (cmd == "TIME") {
		cmdTime(sender, channel, server, args);
	}
	else if (cmd == "JOIN") {
		cmdJoin(sender, channel, server, args);
	}
	else if (cmd == "ROLL") {
		cmdRoll(sender, channel, server, args);
	}
	else if (cmd == "FLIP") {
		cmdFlip(sender, channel, server, args);
	}
	else if (cmd == "8BALL") {
		cmd8Ball(sender, channel, server, args);
	}
	else if (cmd == "GAME") {
		cmdGame(sender, channel, server, args);
	}
	else {
		std::string msg = "[🤖] BEEP-BEEP! " + cmd + " :Invalid input. Unable to process command.";
		reply(sender, channel, server, msg);
	}
}

void BotClient::cmdHelp(Client& sender, const std::string& channel, Server& server, const std::vector<std::string>& args) const {
	std::map<std::string, std::string> helpText;
	helpText["HELP"]  = "[HELP] Show available BOT commands or help for a specific one.";
	helpText["TIME"]  = "[TIME] Show the current server time.";
	helpText["JOIN"]  = "[JOIN <#channel>] Join the bot to a channel.";
	helpText["ROLL"]  = "[ROLL [#n1] [#n2]] Roll a random number between #n1 and #n2 (defaults: 1,100).";
	helpText["FLIP"]  = "[FLIP] Flip a coin.";
	helpText["8BALL"] = "[8BALL <question>] Ask the magic 8-ball a yes/no question.";
	helpText["GAME"]  = "[GAME start | <1-9> | status] Play a mini game (e.g., Tic-Tac-Toe).";

	if (args.empty()) {
		std::string msg = "[🤖] BEEP-BEEP! Available BOT commands: HELP, TIME, JOIN <#channel>, ROLL [#n1] [#n2], FLIP, 8BALL <question>, GAME [start | <1-9> | status]";
		reply(sender, channel, server, msg);
		return;
	}


	if (args.size() > 1) {
		reply(sender, channel, server, "[🤖] BEEP-BEEP! Syntax error - HELP [command] ");
		return;
	}

	std::string subcmd = args[0];
	std::transform(subcmd.begin(), subcmd.end(), subcmd.begin(), ::toupper);

	std::map<std::string, std::string>::const_iterator it = helpText.find(subcmd);
	if (it != helpText.end()) {
		reply(sender, channel, server, "[🤖] BEEP-BEEP! " + it->second);
	} else {
		reply(sender, channel, server, "[🤖] BEEP-BEEP! Unknown BOT command: " + args[1]);
	}
}


void BotClient::cmdTime(Client& sender, const std::string& channel, Server& server, const std::vector<std::string>& args) const {
	if (!args.empty()) {
		reply(sender, channel, server, "[🤖] BEEP-BEEP! Syntax error - TIME");
		return;
	}
	std::string msg = "[🤖] BEEP-BEEP! Current server timestamp: " + getTime();
	reply(sender, channel, server, msg);
}

void BotClient::cmdJoin(Client& sender, const std::string& chan, Server& server, std::vector<std::string>& args) {
	if (chan.empty()) {
		std::string msg = "[🤖] BEEP-BEEP! You must specify a channel to join";
		reply(sender, "", server, msg);
		return;
	}
	if (!server.channelExists(chan)) {
		std::string msg = "[🤖] BEEP-BEEP! Channel " + chan + " does not exist";
		reply(sender, "", server, msg);
		return;
	}
	Channel* channel = server.getChannel(chan);
	if (channel->isFull()) {
		std::string msg = "[🤖] BEEP-BEEP! Channel " + chan + " is full";
		reply(sender, "", server, msg);
		return;
	}
	args.insert(args.begin(), chan);
	CliCmdHandler h(server);
	h.callJoin(*this, args);
}

void BotClient::cmdRoll(Client& sender, const std::string& channel, Server& srv, const std::vector<std::string>& args) const {
	int lo = 1, hi = 100;

	if (args.size() == 1) {
		lo = 1;
		hi = std::atoi(args[0].c_str());
		if (hi < lo) std::swap(lo, hi);
	}
	else if (args.size() == 2) {
		lo = std::atoi(args[0].c_str());
		hi = std::atoi(args[1].c_str());
		if (lo >= hi) std::swap(lo, hi);
	}
	else if (args.size() > 2) {
		reply(sender, channel, srv, "[🤖] BEEP-BEEP! Syntax error - ROLL [#n1] [#n2]");
		return;
	}
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	int result = lo + std::rand() % (hi - lo + 1);

	std::ostringstream oss;
	oss << "[🤖] BEEP-BEEP! Result: " << result << " (" << lo << ", " << hi << ")";

	reply(sender, channel, srv, oss.str());
}

void BotClient::cmdFlip(Client& sender, const std::string& channel, Server& server, const std::vector<std::string>& args) const {
	if (!args.empty()) {
		reply(sender, channel, server, "[🤖] BEEP-BEEP! Syntax error - FLIP");
		return;
	}
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	std::string outcome = (std::rand() % 2 == 0) ? "Heads" : "Tails";
	std::string msg = "[🤖] BEEP-BEEP! Coin flip result: " + outcome;
	reply(sender, channel, server, msg);
}

void BotClient::cmd8Ball(Client& sender, const std::string& channel, Server& server, const std::vector<std::string>& args) const {
	if (args.empty()) {
		reply(sender, channel, server, "[🤖] BEEP-BEEP! You must ask a question for the magic 8-ball.");
		return;
	}

	const char* EIGHTBALL[] = {
		"Without a doubt", "Most likely", "Reply is hazy",
		"Ask again later", "Don't count on it", "Very doubtful",
		"Yes", "Absolutely!", "My circuits say no",
		"The stars say yes"
	};
	const size_t EB_COUNT = sizeof(EIGHTBALL) / sizeof(EIGHTBALL[0]);

	std::string question;
	for (size_t i = 0; i < args.size(); ++i) {
		question += args[i] + " ";
	}
	if (!question.empty()) {
		question.erase(question.size() - 1);
	}

	std::string lower_question = question;
	std::transform(lower_question.begin(), lower_question.end(), lower_question.begin(), ::tolower);

	std::string msg;
	if (lower_question == "what is the answer to life, the universe, and everything?") {
		msg = "[🤖] BEEP-BEEP! The human asked: \"" + lower_question + "\" — Deep Thought says: 42.";
		reply(sender, channel, server, msg);
		return;
	}
	msg = "[🤖] BEEP-BEEP! The human asked: \"" + question + "\" — Magic 8-ball says: " + EIGHTBALL[std::rand() % EB_COUNT];
	reply(sender, channel, server, msg);
}

void BotClient::cmdGame(Client& sender, const std::string& channel, Server& server, const std::vector<std::string>& args) {
	Game& g = games[sender.getFd()];
	std::string out;

	if (args.empty() || args[0] == "start") {
		g.reset();
		reply(sender, channel, server, "[🤖] BEEP-BEEP! New game protocol activated for tic-tac-toe. Player assigned: X.");
		replyMultiline(sender, channel, server, g.drawBoard(sender.getNickname()));
		return;
	}

	if (!args.empty() && args[0] == "status") {
		reply(sender, channel, server, "[🤖] BEEP-BEEP! Current game status for tic-tac-toe.");
		replyMultiline(sender, channel, server, g.drawBoard(sender.getNickname()));
		return;
	}

	if (!args.empty() && args.size() == 1){
		const std::string& posToken = (args[0] == "move") ? args[1] : args[0];
		int pos = std::atoi(posToken.c_str());
		if (pos < 1 || pos > 9 || g.getCell(pos-1) != ' ' || !g.isActive()) {
			reply(sender, channel, server, "[🤖] BEEP-BEEP! Invalid move");
			return;
		}
		g.setCell(pos-1, 'X');
		int st = g.checkWin();
		if (st == 1) {
			reply(sender, channel, server, "[🤖] BEEP-BEEP! You won!");
			replyMultiline(sender, channel, server, g.drawBoard(sender.getNickname()));
			g.setActive(false);
			return;
		}
		else {
			std::vector<int> empt;
			for (int i = 0; i < 9; ++i) if (g.getCell(i)==' ') empt.push_back(i);
			if (!empt.empty()) {
				g.setCell(empt[std::rand()%empt.size()], 'O');
			}
			st = g.checkWin();
			if (st == 2) {
				reply(sender, channel, server, "[🤖] BEEP-BEEP! You lost!");
				replyMultiline(sender, channel, server, g.drawBoard(sender.getNickname()));
				g.setActive(false);
				return;
			}
			else if (st == 3) {
				reply(sender, channel, server, "[🤖] BEEP-BEEP! It's a draw!");
				replyMultiline(sender, channel, server, g.drawBoard(sender.getNickname()));
				g.setActive(false);
				return;
			}
			else out = g.drawBoard(sender.getNickname());
		}
		replyMultiline(sender, channel, server, out);
		if (!g.isActive()) games.erase(sender.getFd());
		return;
	}

	reply(sender, channel, server, "[🤖] BEEP-BEEP! Usage: game start | game <1-9> | status");
}

void BotClient::reply(Client& sender, const std::string& chan, Server& server, std::string msg) const {
	bool isPrivate = chan.empty();
	std::string target = isPrivate ? "" : chan;

	if (isPrivate) {
		server.sendToClient(sender.getFd(), ":" + getNickname() + "!bot@localhost PRIVMSG " +
			server.getClient(sender.getFd()).getNickname() + " :" + msg + "\r\n");
	}
	else {
		Channel* channel = server.getChannel(target);
		if (!server.channelExists(target)){
			msg = "[🤖] BEEP-BEEP! Channel " + target + " does not exist";
			server.sendToClient(sender.getFd(), ":" + getNickname() + "!bot@localhost PRIVMSG " +
				server.getClient(sender.getFd()).getNickname() + " :" + msg + "\r\n");
		}
		else if (!channel->isUserInChannel(sender.getFd())) {
			msg = "[🤖] BEEP-BEEP! You are not in channel " + chan;
			server.sendToClient(sender.getFd(), ":" + getNickname() + "!bot@localhost PRIVMSG " +
				server.getClient(sender.getFd()).getNickname() + " :" + msg + "\r\n");
		}
		else if (!channel->isUserInChannel(getFd())) {
			msg = "[🤖] BEEP-BEEP! I must be in the channel to send messages";
			server.sendToClient(sender.getFd(), ":" + getNickname() + "!bot@localhost PRIVMSG " +
				server.getClient(sender.getFd()).getNickname() + " :" + msg + "\r\n");
			return;
		}
		else
			channel->broadcast(server, ":" + getNickname() + "!bot@localhost PRIVMSG " +
						   chan + " :" + msg + "\r\n");
	}
}
