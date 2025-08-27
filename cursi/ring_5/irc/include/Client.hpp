#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <unistd.h>
#include <vector>

class Client {
	private:
		int _fd;
		std::string _nickname;
		std::string _username;
		std::string _realname;

		bool _authenticated; //PASS ok
		bool _hasNick;
		bool _hasUser;
		bool _registered;

		std::string _recvBuffer;

	public:
		Client();
		Client(int socketFd);
		~Client();

		int getFd() const;
		const std::string& getNickname() const;
		const std::string& getUsername() const;
		const std::string& getRealname() const;

		bool isAuthenticated() const;
		bool hasNick() const;
		bool hasUser() const;
		bool isRegistered() const;

		void setNickname(const std::string& nick);
		void setUsername(const std::string& user);
		void setRealname(const std::string& real);
		void setAuthenticated(bool auth);
		void setHasNick(bool hasNick);
		void setHasUser(bool hasUser);
		void setRegistered(bool reg);

		void appendToBuffer(const std::string& data);
		std::vector<std::string> extractCompleteCommands();
};

#endif