#ifndef SERVER_HPP
#define SERVER_HPP

#include <stdexcept>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <vector>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <csignal>
#include <sstream>
#include <string>
#include <map>

#include "Client.hpp" 
#include "CliCmdHandler.hpp"
#include "Channel.hpp"
#include "DccProxy.hpp"

#define BUFFER_SIZE 8192
class Server {
	public:
		Server(int port, const std::string &password);
		~Server();

		void 		run();
		int 		getPort() const { return _port; }

		// I/O client
		void		handleClientInput(int clientFd);
		void		sendToClient(int clientFd, const std::string& message);
		void		disconnectClient(int clientFd);

		// Client
		Client&							getClient(int fd);
		const Client&					getClient(int fd) const;
		const std::map<int, Client>&	getClients() const;
		const std::string&				getPassword() const;
		size_t							getChannelsCount() const;
		size_t							getConnectedClientsCount() const;
		size_t							getMaxClientCount() const;

		// Channel
		Channel*	getChannel(const std::string& name);
		Channel&	createChannel(const std::string& name);
		bool		channelExists(const std::string& name) const;
		void		removeChannel(const std::string &name);
		const std::map<std::string, Channel>& getChannels() const;

		// Nickname
		bool		nicknameExists(const std::string& nickname) const;
		Client*		getClientByNick(const std::string& nickname);
		const Client* getClientByNick(const std::string& nickname) const;

		// Signal
		static void signal_handler(int sig);

		void addPollFd(int fd, short events);       // insertar
		void delPollFd(int fd);                     // eliminar
		void addTransfer(int fd, const TxControl& tx); // añadir transferencia
		void addRecv(int fd, const RxControl& rx); // añadir recepción
		void modPollFd(int fd, short newEvents); // modificar eventos de un fd

	private:
		int			_port;
		std::string	_password;
		int			_listenFd;
		bool		_running;

		std::map<int, Client>			_clients;
		size_t							_maxClientCount;
		std::map<std::string, Channel>	_channels;

		std::map<int, TxControl> _tx;
		std::map<int, RxControl> _rx;
		std::vector<struct pollfd> _pfds;

		static bool	g_signal;

		void initSocket();

		void handleTransferAccept(int lfd);
		void handleTransferAbort(TxControl &x,int dataFd);
		void handleTransferSend(int dataFd);
		void handleTransferRecv(int dataFd);
		void handleTransferSendAck(int dataFd);

};

#endif
