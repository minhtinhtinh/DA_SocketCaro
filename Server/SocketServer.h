/*
* This's socket and some structures for project
* @author
* - Nguyen Phuc Loi
* - 1660321
* @email
* - nploi1998@gmail.com
*/

#pragma once
#include "Player.h"
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 5454
#define SERVER_ADDR "127.0.0.1"
#define MAX_CLIENT 100
#define ERROR_INIT 1001

using namespace std;

class SocketServer {
public:
	SocketServer();

	/*
	@describe
		Init socket for server 
	@param
		port: int -> PORT of server
		address: const char* -> Address of server
	@return
		NULL
	*/
	void init(int port, const char *address);


	/*
	@describe
		Init socket for server
	@param
		NULL
	@return
		Player
	*/
	Player accepted();

	~SocketServer();
private:
	struct sockaddr_in serverAddr;
	SOCKET listenSock;
};

