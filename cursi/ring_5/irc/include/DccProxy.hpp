/* DccProxy.hpp --------------------------------------------------------- */
#ifndef DCC_PROXY_HPP
#define DCC_PROXY_HPP
#include <map>
#include <string>

struct TxControl {
	int listenFd;
	int dataFd;
	int fileFd;
	int offset;
	int size;
	int senderFd;
	std::string pending;
};

struct RxControl {
	int connFd;
	int fileFd;
	int received;
	int size;
	int receiverFd;
	std::string name;
};

class DccProxy {
public:
	static int openListenSock(unsigned short &portOut);
	static long fileSize(const std::string& path);
	static unsigned long ipToDecimal(const std::string& ip);
};

#endif
