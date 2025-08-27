#include "DccProxy.hpp"
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/stat.h>

int DccProxy::openListenSock(unsigned short &portOut)
{
	int lfd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (lfd == -1)
		return -1;

	::fcntl(lfd, F_SETFL, O_NONBLOCK);

	int yes = 1;
	::setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

	struct sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family      = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;

	if (portOut != 0 && (portOut < 1024 || portOut > 65535))
		portOut = 0;
		
	addr.sin_port = htons(portOut);
	if (::bind(lfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1 ||
		::listen(lfd, 1) == -1)
	{
		if (portOut != 0) {
			addr.sin_port = 0;
			if (::bind(lfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1 ||
				::listen(lfd, 1) == -1)
			{
				::close(lfd);
				return -1;
			}
		} else {
			::close(lfd);
			return -1;
		}
	}

	socklen_t len = sizeof(addr);
	::getsockname(lfd, reinterpret_cast<sockaddr*>(&addr), &len);
	portOut = static_cast<unsigned short>(ntohs(addr.sin_port));

	return lfd;
}
long DccProxy::fileSize(const std::string& path) {
	struct stat st;
	return (::stat(path.c_str(), &st) == 0) ? static_cast<long>(st.st_size) : -1L;
}

unsigned long DccProxy::ipToDecimal(const std::string& ip) {
	struct in_addr addr;
	if (inet_aton(ip.c_str(), &addr))
		return ntohl(addr.s_addr);
	return 0;
}
