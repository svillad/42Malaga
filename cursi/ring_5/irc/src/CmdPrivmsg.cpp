// Comando PRIVMSG:
// Sintaxis:
//   PRIVMSG <destino> :<texto>
//   PRIVMSG <#canal> :<texto>
//   PRIVMSG <nick> :<texto>
//   PRIVMSG :DCC SEND <file> [<port>] [<ip>]
//   PRIVMSG :DCC RECV <file> [<port>] [<ip>]
//
// Reglas / Códigos de error:
//  - Si falta destino:                 ERR_NORECIPIENT (411)
//  - Si falta texto:                   ERR_NOTEXTTOSEND (412)
//  - Si el destino comienza con '#':  (canal)
//      • Si el canal no existe:       ERR_NOSUCHCHANNEL (403)
//      • Si el remitente no está:     ERR_CANNOTSENDTOCHAN (404)
//  - Si el destino es un nick:
//      • Si el nick no existe:        ERR_NOSUCHNICK (401)
//
// Efecto:
//  - A canal: difundir a todos los miembros excepto el remitente.
//  - A nick : enviar solo al receptor.

#include "Messages.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "CliCmdHandler.hpp"
#include "BotClient.hpp"
#include <arpa/inet.h>

static std::string buildPrefix(const Client &c) {
	return c.getNickname() + "!" + c.getUsername() + "@localhost";
}

static void sendNotice(Server &srv, const Client &c, const std::string &msg) {
	srv.sendToClient(c.getFd(),
		":localhost NOTICE " + c.getNickname() + " :" + msg + "\r\n");
}

void CliCmdHandler::handlePrivmsg(Client &sender, std::vector<std::string> &args) {
	if (!sender.isRegistered()) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NOTREGISTERED, sender.getNickname(), "PRIVMSG :You have not registered"));
		return;
	}

	if (args.empty()) {
		_server.sendToClient(sender.getFd(), buildReply(ERR_NORECIPIENT, sender.getNickname(), "PRIVMSG :No recipient given (PRIVMSG)"));
		return;
	}

	if (args.size() == 1) {
		_server.sendToClient(sender.getFd(), buildReply(ERR_NOTEXTTOSEND, sender.getNickname(), "PRIVMSG :No text to send"));
		return;
	}

	if (args.size() > 2) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NEEDMOREPARAMS, sender.getNickname(), "PRIVMSG : Syntax error - PRIVMSG <destination> :<text>"));
		return;
	}

	const std::string &target = args[0];
	const std::string &text   = args[1];

	// Channel case
	if (!target.empty() && target[0] == '#') {
		if (!_server.channelExists(target)) {
			_server.sendToClient(sender.getFd(),
				buildReply(ERR_NOSUCHCHANNEL, sender.getNickname(),
						target + " :No such channel"));
			return;
		}
		Channel& chan = *_server.getChannel(target);
		privmsgToChannel(sender, chan, text);
		return;
	}

	// Nick case
	if (!_server.nicknameExists(target)) {
		_server.sendToClient(sender.getFd(),
			buildReply(ERR_NOSUCHNICK, sender.getNickname(),
					target + " :No such nick/channel"));
		return;
	}
	Client& rcvr = *_server.getClientByNick(target);
	privmsgToNick(sender, rcvr, text);
}

void CliCmdHandler::privmsgToChannel(Client& s, Channel& c, const std::string& txt) {
	if (!c.isUserInChannel(s.getFd())) {
		_server.sendToClient(s.getFd(),
			buildReply(ERR_CANNOTSENDTOCHAN, s.getNickname(),
					   c.getName() + " :Cannot send to channel"));
		return;
	}
	std::string raw = ":" + buildPrefix(s) +
					  " PRIVMSG " + c.getName() + " :" + txt + "\r\n";
	c.broadcast(_server, raw, s.getFd());
}

void CliCmdHandler::privmsgToNick(Client& s, Client& r, const std::string& txt) {
	// DCC SEND/RECV
	std::vector<std::string> tok;
	std::istringstream iss(txt); std::string w;
	while (iss >> w) tok.push_back(w);

	if (tok.size() >= 2 && toUpper(tok[0]) == "DCC") {
		if (toUpper(tok[1]) == "SEND")
			handleDccSend(s, r, tok);

		else if (toUpper(tok[1]) == "RECV")
			handleDccRecv(s, tok);
		return;
	}

	// Normal PRIVMSG
	std::string raw = ":" + buildPrefix(s) +
					  " PRIVMSG " + r.getNickname() + " :" + txt + "\r\n";
	_server.sendToClient(r.getFd(), raw);

	// Echo to bot (-2)
	if (r.getFd() == -2) {
		BotClient* bot = static_cast<BotClient*>(&r);
		std::vector<std::string> a; a.push_back(s.getNickname()); a.push_back(txt);
		handlePrivmsg(*bot, a);
	}
}

bool CliCmdHandler::handleDccSend(Client& snd, Client& rcv, const std::vector<std::string>& t) {
	if (t.size() < 3) {
		sendNotice(_server, snd, "[DCC] SEND: bad syntax");
		return false;
	}

	const std::string file = t[2];
	long sz = DccProxy::fileSize(file);
	if (sz < 0) {
		sendNotice(_server, snd, "[DCC] file not found");
		return false;
	}
	unsigned short port = (t.size() >= 5 ? std::atoi(t[4].c_str()) : 0);
	if (port != 0 && (port < 1024 || port > 65535)) {
		sendNotice(_server, snd, "[DCC] invalid port (must be 1024-65535)");
		return false;
	}

	int lfd = DccProxy::openListenSock(port);
	if (lfd == -1) {
		sendNotice(_server, snd, "[DCC] cannot open listen socket");
		return false;
	}

	int ffd = open(file.c_str(), O_RDONLY|O_NONBLOCK);
	if (ffd == -1) {
		::close(lfd);
		sendNotice(_server, snd, "[DCC] open() failed");
		return false;
	}

	TxControl x; x.listenFd=lfd; x.dataFd=-1; x.fileFd=ffd;
	x.offset=0; x.size=sz; x.senderFd=snd.getFd();
	_server.addTransfer(lfd, x);

	std::string ip = (t.size() >= 4 ? t[3] : "127.0.0.1");;
	std::ostringstream oss;
	oss << '\x01' << "DCC SEND " << file << " " <<  DccProxy::ipToDecimal(ip) << " "
		<< port << ' ' << sz << '\x01';

	std::string raw = ":" + buildPrefix(snd) +
					  " PRIVMSG " + rcv.getNickname() + " :" +
					  oss.str() + "\r\n";
	_server.sendToClient(rcv.getFd(), raw);
	
	sendNotice(_server, snd,
			   "[DCC] listening on port " + to_string(port));
	return true;
}

bool CliCmdHandler::handleDccRecv(Client& snd, const std::vector<std::string>& t) {
	if (t.size() < 5) {
		sendNotice(_server, snd, "[DCC] RECV: bad syntax");
		return false;
	}

	const std::string file = t[2];
	std::string ip         = t[3];
	unsigned short port    = std::atoi(t[4].c_str());
	off_t sz               = (t.size() >= 6 ? std::atol(t[5].c_str()) : 0);

	if (port == 0) {
		sendNotice(_server, snd, "[DCC] RECV: port missing");
		return false;
	}

	if (port < 1024 || port > 65535) {
		sendNotice(_server, snd, "[DCC] invalid port (must be 1024-65535)");
		return false;
	}

	int cfd = socket(AF_INET, SOCK_STREAM, 0);
	if (cfd == -1) {
		sendNotice(_server, snd, "[DCC] socket() failed");
		return false;
	}
	fcntl(cfd, F_SETFL, O_NONBLOCK);
	struct sockaddr_in a; std::memset(&a,0,sizeof(a));
	a.sin_family = AF_INET; a.sin_port = htons(port);
	if (inet_pton(AF_INET, ip.c_str(), &a.sin_addr) != 1 ||
		(connect(cfd, (sockaddr*)&a, sizeof(a)) == -1 && errno != EINPROGRESS))
	{
		close(cfd);
		sendNotice(_server, snd, "[DCC] connect() failed");
		return false;
	}

	std::string tmp = "/tmp/" + snd.getNickname() + "_" + file;
	int ffd = open(tmp.c_str(),
					 O_CREAT|O_WRONLY|O_TRUNC|O_NONBLOCK, 0600);
	if (ffd == -1) {
		close(cfd);
		sendNotice(_server, snd, "[DCC] cannot create dest file");
		return false;
	}

	RxControl rx; rx.connFd=cfd; rx.fileFd=ffd; rx.received=0;
	rx.size=sz; rx.receiverFd=snd.getFd(); rx.name=file;
	_server.addRecv(cfd, rx);

	sendNotice(_server, snd,
			   "[DCC] receiving '" + file + "' into " + tmp);
	return true;
}

void CliCmdHandler::handleNotice(Client &sender, std::vector<std::string> &args) {
	if (!sender.isRegistered()) {
		return;
	}

	if (args.size() < 2) {
		return;
	}

	const std::string &target = args[0];
	const std::string &text   = args[1];

	if (!target.empty() && target[0] == '#') {
		if (!_server.channelExists(target)) {
			return;
		}
		Channel *channel = _server.getChannel(target);
		if (!channel->isUserInChannel(sender.getFd())) {
			return;
		}
		std::string raw = ":" + buildPrefix(sender) + " NOTICE " + target + " :" + text + "\r\n";
		channel->broadcast(_server, raw, sender.getFd());
	} else {
		if (!_server.nicknameExists(target)) {
			return;
		}
		Client *receiver = _server.getClientByNick(target);

		if (receiver->getFd() >= 0) {
			std::string raw = ":" + buildPrefix(sender) + " NOTICE " + target + " :" + text + "\r\n";
			_server.sendToClient(receiver->getFd(), raw);
		}
	}
}
