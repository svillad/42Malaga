#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <set>

class Server;
class Client;

class Channel {
	private:
		std::string		_name;
		std::string		_topic;
		std::set<int>	_members;
		std::set<int>	_operators;

		// Modes
		bool			_inviteOnly;       // +i
		bool			_topicRestricted;  // +t
		std::string		_channelKey;       // +k
		int				_userLimit;        // +l
		bool			_private;          // +p
		bool			_secret;           // +s

		std::set<int>	_invited;

	public:
		Channel();
		explicit Channel(const std::string& name);

		// Members
		void addUser(int clientFd, bool isOperator = false);
		void removeUser(int clientFd);
		bool isUserInChannel(int clientFd) const;

		// Operators
		bool isOperator(int clientFd) const;
		bool addOperator(int fd);
		bool removeOperator(int fd);
		int promoteFirstMemberToOperator();
		int operatorCount() const;

		// Basics
		const std::string& getName() const;
		void setTopic(const std::string& topic);
		const std::string& getTopic() const;

		// Modes
		void setInviteOnly(bool value);
		bool isInviteOnly() const;
		void setTopicRestricted(bool b);
		bool isTopicRestricted() const;
		void setPrivate(bool);
		bool isPrivate() const;
		void setSecret(bool);
		bool isSecret() const;

		void setPassword(const std::string& key);
		std::string getPassword() const;
		bool hasPassword() const;
		bool checkPassword(const std::string& key) const;
		void clearPassword();

		void setUserLimit(int limit);
		int getUserLimit() const;
		bool isFull() const;
		void clearUserLimit();

		// Invitaciones
		void inviteUser(int clientFd);
		bool isUserInvited(int clientFd) const;
		void removeInvitation(int fd);

		// Acceso a miembros
		const std::set<int>& getAllUsers() const;
		// excludeFd se usa para no enviar el mensaje al cliente que lo originó, para evitar duplicados
		void broadcast(Server& server, const std::string& message, int excludeFd = -1);
};

#endif