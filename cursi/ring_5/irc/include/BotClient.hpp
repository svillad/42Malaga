#ifndef BOTCLIENT_HPP
#define BOTCLIENT_HPP

#include "Client.hpp"
#include "Game.hpp"
#include <string>
#include <vector>
#include <map>

class Server;

class BotClient : public Client {
public:
	explicit BotClient(int fakeFd = -2);

	void handleCommand(Client& sender, const std::string& channel, const std::string& cmd,
					   std::vector<std::string>& args, Server& server);

private:
	void cmdHelp(Client& sender, const std::string& channel, Server& server, const std::vector<std::string>& args) const;
	void cmdTime(Client& sender, const std::string& channel, Server& server, const std::vector<std::string>& args) const;
	void cmdJoin(Client& sender, const std::string& channel, Server& server, std::vector<std::string>& args);
	void cmdRoll(Client& sender, const std::string& channel, Server& server, const std::vector<std::string>& args) const;
	void cmdFlip(Client& sender, const std::string& channel, Server& server, const std::vector<std::string>& args) const;
	void cmd8Ball(Client& sender, const std::string& channel, Server& server, const std::vector<std::string>& args) const;
	void cmdGame(Client& sender, const std::string& channel, Server& server, const std::vector<std::string>& args);

	void replyMultiline(Client& sender, const std::string& channel, Server& server, const std::string& msg) const;
	void reply(Client& sender, const std::string& channel, Server& server, std::string msg) const;
	std::string getTime() const;
};

#endif