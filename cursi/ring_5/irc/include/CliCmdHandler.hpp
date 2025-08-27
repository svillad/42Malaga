#ifndef CLICMDHANDLER_HPP
#define CLICMDHANDLER_HPP

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

class Server;
class Client;
class Channel;

class CliCmdHandler {
	private:
		Server& _server;
		std::vector<std::string>split(const std::string& str);
		std::string toUpper(const std::string& str);
		void sendWelcome(Client& client);
		std::string buildReply(int code, const std::string& nick, const std::string& message);
		int detectShortcutForBot(Client &cli, int clientFd,  std::vector<std::string> &tokens, std::string &cmd);

		void handlePass(Client& client, const std::vector<std::string>& args);
		void handleNick(Client& client, const std::vector<std::string>& args);
		void handleUser(Client& client, const std::vector<std::string>& args);

		void handleJoin(Client& client, const std::vector<std::string>& args);
		void handlePrivmsg(Client &sender, std::vector<std::string>& args);
		void handleNotice(Client &sender, std::vector<std::string>& args);
		void handleKick(Client &sender, std::vector<std::string>& args);
		void handleInvite(Client &sender, std::vector<std::string>& args);
		void handleTopic(Client& sender, std::vector<std::string>& args);
		void handleMode(Client& sender, std::vector<std::string>& args);
		void handleList(Client& requester, std::vector<std::string>& args);
		void handleWhois(Client &requester, std::vector<std::string>& args);
		void handleWho(Client &requester, std::vector<std::string> &args);
		void handleNames(Client& requester, std::vector<std::string>& args);
		void handleBot(Client& sender, std::vector<std::string>& args);
		void handleHelp(Client& sender, std::vector<std::string>& args);

	public:
		CliCmdHandler(Server& server);

		void handle(int clientFd, const std::string& message);
		void callJoin(Client& cl, const std::vector<std::string>& args);
		void sendNamesBurst(const Channel& ch);

		void privmsgToChannel(Client& s, Channel& c, const std::string& txt);
		void privmsgToNick(Client& s, Client& r, const std::string& txt);
		bool handleDccSend(Client& sender, Client& receiver, const std::vector<std::string>& args);
		bool handleDccRecv(Client& sender, const std::vector<std::string>& args);
};

#endif
