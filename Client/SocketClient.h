#pragma once
/*
* This's socket and some structures for project
* @author
* - Nguyen Nhut Minh
* - 1660345
* @email
* - nhutminh12a21998@gmail.com
*/

#include <iostream>
#include <process.h>
#include <winsock2.h>
#include <string.h>
#include <string>
#include <WS2tcpip.h>
#include "..\lib\Map.h"

using namespace std;

#pragma comment (lib, "Ws2_32.lib")

#define PORT 5454
#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 50
#define ERROR_INIT 1001

class SocketClient
{
public:
	SocketClient();

	SOCKET getClient();
	
	void InitClient(const char* server_addr, const int port);

	int registerUsername(string username);

	int Send(const char buff[]);

	string Receive();

	static unsigned _stdcall SendThread(void* param);

	~SocketClient();

private:
	SOCKET server;
};