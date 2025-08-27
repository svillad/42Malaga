#include "Server.hpp"
#include "Client.hpp"
#include "BotClient.hpp"
#include <arpa/inet.h>

void Server::addTransfer(int fd, const TxControl& tx) {
	_tx[fd] = tx;
	addPollFd(fd, POLLIN);
}

void Server::addRecv(int fd, const RxControl& rx) {
	_rx[fd] = rx;
	addPollFd(fd, POLLIN);
}

void Server::addPollFd(int fd, short ev) {
	struct pollfd p; p.fd = fd; p.events = ev; p.revents = 0;
	_pfds.push_back(p);
}

void Server::delPollFd(int fd) {
	std::cout << "[INFO] Disconnected (fd=" << fd << ")\n";
	for (size_t i = 0; i < _pfds.size(); ++i) {
		if (_pfds[i].fd == fd) {
			_pfds.erase(_pfds.begin() + i);
			break;
		}
	}
}

void Server::modPollFd(int fd, short newEvents) {
	for (size_t j = 0; j < _pfds.size(); ++j)
		if (_pfds[j].fd == fd) {
			_pfds[j].events = newEvents;
			break;
		}
}

void Server::handleTransferAccept(int listenFd) {
	TxControl &tx = _tx[listenFd];
	int dataFd = accept(listenFd, 0, 0);
	if (dataFd == -1) return;
	fcntl(dataFd, F_SETFL, O_NONBLOCK);
	tx.dataFd = dataFd;
	addPollFd(dataFd, POLLIN | POLLOUT);

	delPollFd(listenFd);
	close(listenFd);
	tx.listenFd = -1;
}

void Server::handleTransferAbort(TxControl &tx,int dataFd) {
	close(tx.fileFd);
	close(tx.dataFd); 
	close(tx.listenFd);
	delPollFd(dataFd);
	_tx.erase(tx.listenFd);

	sendToClient(tx.senderFd,
		":localhost NOTICE " + getClient(tx.senderFd).getNickname() +
		" :[DCC] send aborted");
}

void Server::handleTransferSend(int dataFd) {
	TxControl* px = 0;
	for (std::map<int,TxControl>::iterator it = _tx.begin(); it != _tx.end(); ++it) {
		if (it->second.dataFd == dataFd) {
			px = &it->second;
			break;
		}
	}
	if (!px)
		return;

	TxControl &tx = *px;

	// Attempt to send pending data
	while (!tx.pending.empty()) {
		ssize_t n = write(dataFd, tx.pending.data(), tx.pending.size());
		if (n == -1) {
			if (errno == EAGAIN) return;
			handleTransferAbort(tx, dataFd);
			return;
		}
		tx.pending.erase(0, n);
		tx.offset += n;
	}

	// Attempt to read from the file and send it
	char buf[BUFFER_SIZE];
	ssize_t rd = read(tx.fileFd, buf, sizeof(buf));
	if (rd > 0) {
		ssize_t wr = write(dataFd, buf, rd);
		if (wr == -1) {
			if (errno == EAGAIN) {
				tx.pending.assign(buf, buf + rd);
				return;
			}
			handleTransferAbort(tx, dataFd);
			return;
		}

		tx.offset += wr;
		if (wr < rd) {
			tx.pending.assign(buf + wr, buf + rd);
		}
		return;
	}

	// Transfer completed: EOF/no data pending
	if (rd == 0 && tx.pending.empty() && tx.offset >= tx.size) {
		// shutdown(dataFd, SHUT_WR);
		std::ostringstream oss;
		oss << ":localhost NOTICE " << getClient(tx.senderFd).getNickname()
			<< " :[DCC] transfer complete (" << tx.size << " bytes)";
		sendToClient(tx.senderFd, oss.str());

		close(tx.fileFd);
		close(tx.dataFd);
		close(tx.listenFd);
		delPollFd(dataFd);
		_tx.erase(tx.listenFd);
		return;
	}

	// Error handling
	if (rd == -1 && errno != EAGAIN)
		handleTransferAbort(tx, dataFd);
}

void Server::handleTransferSendAck(int dataFd) {
	TxControl *px = 0;
	for (std::map<int,TxControl>::iterator it=_tx.begin();
		 it!=_tx.end(); ++it)
		if (it->second.dataFd == dataFd) { px=&it->second; break; }
	if (!px) return;
	TxControl &tx = *px;

	char dump[32];
	ssize_t n = ::read(dataFd, dump, sizeof(dump));   // lee ACK

	if (n == 0 && tx.pending.empty() && tx.offset >= tx.size) {
		std::ostringstream oss;
		oss << ":localhost NOTICE "
			<< getClient(tx.senderFd).getNickname()
			<< " :[DCC] transfer complete (" << tx.size << " bytes)";
		sendToClient(tx.senderFd, oss.str());

		close(tx.fileFd);
		close(tx.dataFd);
		if (tx.listenFd != -1)
			close(tx.listenFd);
		delPollFd(dataFd);
		_tx.erase(tx.listenFd);
	}
}

void Server::handleTransferRecv(int connFd) {
	std::map<int,RxControl>::iterator it = _rx.find(connFd);
	if (it == _rx.end())
		return;
	RxControl &rx = it->second;

	char buf[BUFFER_SIZE];
	ssize_t n = read(rx.connFd, buf, sizeof(buf));
	if (n > 0) {
		write(rx.fileFd, buf, n);
		rx.received += n;

		if (rx.size == 0 || rx.received >= rx.size) {
			uint32_t ack = htonl(static_cast<uint32_t>(rx.received));
			write(rx.connFd, &ack, 4);
			close(rx.connFd);
			close(rx.fileFd);
			delPollFd(connFd);
			std::ostringstream oss;
			oss << ":localhost NOTICE "
				<< getClient(rx.receiverFd).getNickname()
				<< " :[DCC] download complete (" << rx.received << " bytes)";
			sendToClient(rx.receiverFd, oss.str());
			_rx.erase(it);
			return;
		}
		uint32_t ack = htonl(static_cast<uint32_t>(rx.received));
		write(rx.connFd, &ack, 4);
		return;
	}

	if (n == 0) {
		if (rx.size == 0 || rx.received >= rx.size) {
			close(rx.connFd);
			close(rx.fileFd);
			delPollFd(connFd);
			std::ostringstream oss;
			oss << ":localhost NOTICE "
				<< getClient(rx.receiverFd).getNickname()
				<< " :[DCC] download complete (" << rx.received << " bytes)";
			sendToClient(rx.receiverFd, oss.str());
			_rx.erase(it);
		}
		return;
	}

	if (n == -1 && errno == EAGAIN)
		return;

	// Error handling
	close(rx.connFd);
	close(rx.fileFd);
	delPollFd(connFd);
	_rx.erase(it);
	sendToClient(rx.receiverFd,
		":localhost NOTICE " + getClient(rx.receiverFd).getNickname() +
		" :[DCC] download aborted");
}
