#include "Channel.hpp"
#include "Server.hpp"

Channel::Channel() :
	  _name(""), _topic(""),
	  _inviteOnly(false),
	  _channelKey(""),
	  _userLimit(-1),
	  _private(false),
	  _secret(false) {}

Channel::Channel(const std::string& name) :
	  _name(name),
	  _topic(""),
	  _inviteOnly(false),
	  _channelKey(""),
	  _userLimit(-1),
	  _private(false),
	  _secret(false) {}


void Channel::addUser(int clientFd, bool isOperator) {
	_members.insert(clientFd);
	if (isOperator)
		_operators.insert(clientFd);
}

void Channel::removeUser(int clientFd) {
	_members.erase(clientFd);
	_operators.erase(clientFd);
	_invited.erase(clientFd);
}

bool Channel::isUserInChannel(int clientFd) const {
	return _members.find(clientFd) != _members.end();
}

bool Channel::isOperator(int clientFd) const {
	return _operators.find(clientFd) != _operators.end();
}

bool Channel::addOperator(int fd) {
	if (!isUserInChannel(fd))
		return false;

	std::pair<std::set<int>::iterator, bool> res = _operators.insert(fd);
	return res.second;
}

bool Channel::removeOperator(int fd) {
	std::set<int>::iterator it = _operators.find(fd);
	if (it == _operators.end())
		return false;

	_operators.erase(it);
	return true;
}

int Channel::promoteFirstMemberToOperator() {
	for (std::set<int>::const_iterator it = _operators.begin(); it != _operators.end(); ++it)
		if (*it != -2) return -1;

	int candidate = -1;
	for (std::set<int>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
		if (*it == -2) continue;
		candidate = *it;
		break;
	}

	if (candidate != -1) {
		_operators.insert(candidate);
	}
	else {
		candidate = -2;
	}
	return candidate;
}

int Channel::operatorCount() const {
	return _operators.size();
}

const std::string& Channel::getName() const {
	return _name;
}

void Channel::setTopic(const std::string& topic) {
	_topic = topic;
}

const std::string& Channel::getTopic() const {
	return _topic;
}

void Channel::setInviteOnly(bool value) {
	_inviteOnly = value;
}

bool Channel::isInviteOnly() const {
	return _inviteOnly;
}

void Channel::setTopicRestricted(bool value) {
	_topicRestricted = value;
}

bool Channel::isTopicRestricted() const {
	return _topicRestricted;
}

void Channel::setPrivate(bool value){
	_private = value;
}

bool Channel::isPrivate() const {
	return _private;
}

void Channel::setSecret(bool value) {
	_secret= value;
}

bool Channel::isSecret() const {
	return _secret;
}

void Channel::setPassword(const std::string& key) {
	_channelKey = key;
}

std::string Channel::getPassword() const {
	return _channelKey;
}

bool Channel::hasPassword() const {
	return !_channelKey.empty();
}

bool Channel::checkPassword(const std::string& key) const {
	return _channelKey == key;
}

void Channel::clearPassword() {
	_channelKey.clear();
}

void Channel::setUserLimit(int limit) {
	_userLimit = limit;
}

int Channel::getUserLimit() const {
	return _userLimit;;
}

bool Channel::isFull() const {
	return _userLimit != -1 && static_cast<int>(_members.size()) >= _userLimit;
}

void Channel::clearUserLimit() {
	_userLimit = -1;
}

void Channel::inviteUser(int clientFd) {
	_invited.insert(clientFd);
}

bool Channel::isUserInvited(int clientFd) const {
	return _invited.find(clientFd) != _invited.end();
}
void Channel::removeInvitation(int fd) {
	_invited.erase(fd);
}

const std::set<int>& Channel::getAllUsers() const {
	return _members;
}

void Channel::broadcast(Server& server, const std::string& message, int excludeFd) {
	for (std::set<int>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
		if (*it != excludeFd) {
			server.sendToClient(*it, message);
		}
	}
}