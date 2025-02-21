#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <string>
#include <vector>
#include "ServerConfig.hpp"

class ConfigParser {
private:
    std::string _filename;
    std::vector<ServerConfig> _serverConfigs;

    void trim(std::string &str);
    std::vector<std::string> tokenize(const std::string &line);
    void processServerDirective(ServerConfig &server, const std::vector<std::string> &tokens);
    void processLocationDirective(class LocationConfig &location, const std::vector<std::string> &tokens);

public:
    ConfigParser();
    ConfigParser(const std::string &filename);
    ConfigParser(const ConfigParser &other);
    ConfigParser &operator=(const ConfigParser &other);
    ~ConfigParser();

    bool parse();
    const std::vector<ServerConfig>& getServerConfigs() const;
};

#endif
