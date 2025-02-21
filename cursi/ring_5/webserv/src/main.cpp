#include "ConfigParser.hpp"
#include "ServerConfig.hpp"
#include "ErrorPage.hpp"
#include "LocationConfig.hpp"
#include <iostream>

int main() {
    // Se crea el parser con la ruta del archivo de configuración.
    ConfigParser parser("config/webserv.conf");

    if (!parser.parse()) {
        std::cerr << "Error al parsear el archivo de configuración." << std::endl;
        return 1;
    }

    // Se obtienen las configuraciones de los servidores.
    const std::vector<ServerConfig>& servers = parser.getServerConfigs();
    std::cout << "Se han cargado " << servers.size() << " servidor(es)." << std::endl;

    if (!servers.empty()) {
        const ServerConfig& server = servers[0];
        std::cout << "Servidor:" << std::endl;
        std::cout << "  Listen: " << server.getListen() << std::endl;
        std::cout << "  Host: " << server.getHost() << std::endl;
        std::cout << "  Server Name: " << server.getServerName() << std::endl;
        std::cout << "  Client Max Body Size: " << server.getClientMaxBodySize() << std::endl;

        // Mostrar directivas error_page
        const std::vector<ErrorPage>& errorPages = server.getErrorPages();
        std::cout << "  Error Pages:" << std::endl;
        for (size_t i = 0; i < errorPages.size(); i++) {
            const ErrorPage &ep = errorPages[i];
            std::cout << "    Página: " << ep.getPagePath() << " para códigos: ";
            const std::vector<int>& codes = ep.getErrorCodes();
            for (size_t j = 0; j < codes.size(); j++) {
                std::cout << codes[j] << " ";
            }
            std::cout << std::endl;
        }

        // Mostrar bloques location
        const std::vector<LocationConfig>& locations = server.getLocations();
        std::cout << "  Locations:" << std::endl;
        for (size_t i = 0; i < locations.size(); i++) {
            const LocationConfig &loc = locations[i];
            std::cout << "    Location: " << loc.getPath() << std::endl;
            std::cout << "      Root: " << loc.getRoot() << std::endl;
            std::cout << "      Index: " << loc.getIndex() << std::endl;
            std::cout << "      Autoindex: " << (loc.getAutoindex() ? "on" : "off") << std::endl;
            std::cout << "      CGI Pass: " << loc.getCgiPass() << std::endl;
        }
    }
    return 0;
}
