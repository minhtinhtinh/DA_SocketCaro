/*
* @author
* - Nguyen Phuc Loi
* - 1660321
* @email
* - nploi1998@gmail.com
*/

#include "SocketServer.h"

SocketServer::SocketServer() {
}

void SocketServer::init(int port, const char *address) {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		throw ERROR_INIT;
		WSACleanup();
		return;
	}
	// init socket
	listenSock = socket(AF_INET, SOCK_STREAM, 0/*TCP*/);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr(address);

	// Bind
	if (bind(listenSock, (sockaddr *)&serverAddr, sizeof(serverAddr)))
	{
		throw ERROR_INIT;
		return;
	}

	// listen
	if (listen(listenSock, 10)){
		throw ERROR_INIT;
		return;
	}
}

Player SocketServer::accepted() {
	Player result;
	int clientAddrLen = sizeof(result.clientAddr);
	result.socket = accept(this->listenSock, (sockaddr *)&result.clientAddr, &clientAddrLen);
	return result;
}



/*
 Destructor
*/
SocketServer::~SocketServer()
{
	closesocket(listenSock);
	WSACleanup();
}
