#include "ConfigParser.hpp"
#include "LocationConfig.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>

ConfigParser::ConfigParser() : _filename("config/webserv.conf") {
}

ConfigParser::ConfigParser(const std::string &filename) : _filename(filename) {
}

ConfigParser::ConfigParser(const ConfigParser &other) {
    *this = other;
}

ConfigParser &ConfigParser::operator=(const ConfigParser &other) {
    if (this != &other) {
        _filename = other._filename;
        _serverConfigs = other._serverConfigs;
    }
    return *this;
}

ConfigParser::~ConfigParser() {}

// Método para recortar espacios en blanco
void ConfigParser::trim(std::string &str) {
    const char* whitespace = " \t\n\r";
    str.erase(0, str.find_first_not_of(whitespace));
    str.erase(str.find_last_not_of(whitespace) + 1);
}

// Método para tokenizar una línea
std::vector<std::string> ConfigParser::tokenize(const std::string &line) {
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Método para procesar directivas en el bloque del servidor
void ConfigParser::processServerDirective(ServerConfig &server, const std::vector<std::string> &tokens) {
    if (tokens[0] == "listen" && tokens.size() >= 2) {
        server.setListen(std::atoi(tokens[1].c_str()));
    } else if (tokens[0] == "host" && tokens.size() >= 2) {
        server.setHost(tokens[1]);
    } else if (tokens[0] == "server_name" && tokens.size() >= 2) {
        server.setServerName(tokens[1]);
    } else if (tokens[0] == "error_page" && tokens.size() >= 3) {
        // tokens[1]..tokens[n-2] serán códigos y tokens[n-1] la página de error
        std::vector<int> codes;
        for (size_t i = 1; i < tokens.size() - 1; i++) {
            codes.push_back(std::atoi(tokens[i].c_str()));
        }
        ErrorPage ep(codes, tokens[tokens.size() - 1]);
        server.addErrorPage(ep);
    } else if (tokens[0] == "client_max_body_size" && tokens.size() >= 2) {
        server.setClientMaxBodySize(static_cast<size_t>(std::atoi(tokens[1].c_str())));
    }
}

// Método para procesar directivas en el bloque de ubicación
void ConfigParser::processLocationDirective(LocationConfig &location, const std::vector<std::string> &tokens) {
    if (tokens[0] == "root" && tokens.size() >= 2)
        location.setRoot(tokens[1]);
    else if (tokens[0] == "index" && tokens.size() >= 2)
        location.setIndex(tokens[1]);
    else if (tokens[0] == "autoindex" && tokens.size() >= 2)
        location.setAutoindex(tokens[1] == "on");
    else if (tokens[0] == "cgi_pass" && tokens.size() >= 2)
        location.setCgiPass(tokens[1]);
}

// Método principal de parseo
bool ConfigParser::parse() {
    std::ifstream file(_filename.c_str());
    if (!file) {
        std::cerr << "Error: no se pudo abrir el archivo de configuración: " << _filename << std::endl;
        return false;
    }

    std::string line;
    ServerConfig currentServer;
    bool inServerBlock = false;
    bool inLocationBlock = false;
    LocationConfig currentLocation;

    while (std::getline(file, line)) {
        trim(line);
        if (line.empty() || line[0] == '#')
            continue;

        // Inicia bloque de servidor
        if (line == "server {") {
            inServerBlock = true;
            currentServer = ServerConfig();
            continue;
        }

        // Inicia bloque de ubicación dentro del servidor
        if (inServerBlock && line.substr(0, 9) == "location ") {
            size_t pos = line.find('{');
            if (pos != std::string::npos) {
                currentLocation = LocationConfig();
                std::vector<std::string> tokens = tokenize(line.substr(0, pos));
                if (tokens.size() >= 2)
                    currentLocation.setPath(tokens[1]);
                inLocationBlock = true;
            }
            continue;
        }

        // Fin de bloque
        if (line == "}") {
            if (inLocationBlock) {
                currentServer.addLocation(currentLocation);
                inLocationBlock = false;
            } else if (inServerBlock) {
                _serverConfigs.push_back(currentServer);
                inServerBlock = false;
            }
            continue;
        }

        // Tokeniza la línea para procesar directivas
        std::vector<std::string> tokens = tokenize(line);
        if (tokens.empty())
            continue;

        // Procesa la directiva según el contexto (servidor o ubicación)
        if (inServerBlock && !inLocationBlock) {
            processServerDirective(currentServer, tokens);
        } else if (inServerBlock && inLocationBlock) {
            processLocationDirective(currentLocation, tokens);
        }
    }

    file.close();
    return true;
}

const std::vector<ServerConfig>& ConfigParser::getServerConfigs() const {
    return _serverConfigs;
}
