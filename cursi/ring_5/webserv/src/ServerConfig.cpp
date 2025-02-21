#include "ServerConfig.hpp"
#include <cstdlib>

ServerConfig::ServerConfig() : _listen(80), _clientMaxBodySize(0) {
}

ServerConfig::ServerConfig(const ServerConfig &other){
    *this = other;
}

ServerConfig &ServerConfig::operator=(const ServerConfig &other) {
    if (this != &other) {
        _listen = other._listen;
        _host = other._host;
        _serverName = other._serverName;
        _errorPages = other._errorPages;
        _clientMaxBodySize = other._clientMaxBodySize;
        _locations = other._locations;
    }
    return *this;
}

ServerConfig::ServerConfig(int listen, const std::string &host,const std::string &serverName,
                           size_t clientMaxBodySize)
    : _listen(listen), _host(host), _serverName(serverName), _clientMaxBodySize(clientMaxBodySize) {
}

ServerConfig::~ServerConfig() {
}

// Setters
void ServerConfig::setListen(int listen) {
    _listen = listen;
}

void ServerConfig::setHost(const std::string &host) {
    _host = host;
}

void ServerConfig::setServerName(const std::string &serverName) {
    _serverName = serverName;
}

void ServerConfig::setClientMaxBodySize(size_t size) {
    _clientMaxBodySize = size;
}

void ServerConfig::addLocation(const LocationConfig &location) {
    _locations.push_back(location);
}

void ServerConfig::addErrorPage(const ErrorPage &errorPage) {
    _errorPages.push_back(errorPage);
}

// Getters
int ServerConfig::getListen() const {
    return _listen;
}

const std::string& ServerConfig::getHost() const {
    return _host;
}

const std::string& ServerConfig::getServerName() const {
    return _serverName;
}

size_t ServerConfig::getClientMaxBodySize() const {
    return _clientMaxBodySize;
}

const std::vector<LocationConfig>& ServerConfig::getLocations() const {
    return _locations;
}

const std::vector<ErrorPage>& ServerConfig::getErrorPages() const {
    return _errorPages;
}
