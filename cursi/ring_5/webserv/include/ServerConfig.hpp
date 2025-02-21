#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP

#include "ErrorPage.hpp"
#include "LocationConfig.hpp"
#include <string>
#include <vector>

class ServerConfig {
private:
    int _listen;
    std::string _host;
    std::string _serverName;
    std::vector<ErrorPage> _errorPages;
    size_t _clientMaxBodySize;
    std::vector<LocationConfig> _locations;

public:
    ServerConfig();
    ServerConfig(const ServerConfig &other);
    ServerConfig &operator=(const ServerConfig &other);
    ServerConfig(int listen,
                 const std::string &host,
                 const std::string &serverName,
                 size_t clientMaxBodySize);
    ~ServerConfig();

    // Setters
    void setListen(int listen);
    void setHost(const std::string &host);
    void setServerName(const std::string &serverName);
    void setClientMaxBodySize(size_t size);
    void addLocation(const LocationConfig &location);
    void addErrorPage(const ErrorPage &errorPage);

    // Getters
    int getListen() const;
    const std::string& getHost() const;
    const std::string& getServerName() const;
    size_t getClientMaxBodySize() const;
    const std::vector<LocationConfig>& getLocations() const;
    const std::vector<ErrorPage>& getErrorPages() const;
};

#endif
