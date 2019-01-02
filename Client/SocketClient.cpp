/*
* @author
* - Nguyen Nhut Minh
* - 1660345
* @email
* - nhutminh12a21998@gmail.com
*/


#include "SocketClient.h"
SocketClient::SocketClient()
{
}

SOCKET SocketClient::getClient()
{
	return this->server;
}

void SocketClient::InitClient(const char* server_addr, int port)
{
	WSADATA WSAData;
	sockaddr_in addr;

	WSAStartup(MAKEWORD(2, 0), &WSAData);
	WORD wVersion = MAKEWORD(2, 2);
	this->server = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_addr.s_addr = inet_addr(server_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	int check = connect(this->server, (sockaddr *)&addr, sizeof(addr));
	if (check == SOCKET_ERROR){
		throw ERROR_INIT;
	}
}

int SocketClient::registerUsername(string username)
{
	return Send(username.c_str());
}

int SocketClient::Send(const char buff[])
{
	int check = send(server, buff, strlen(buff), 0);

	if (check != SOCKET_ERROR) {
		return 1;
	}
	//closesocket(server);
	return 0;
}

string SocketClient::Receive()
{
	char str[BUFF_SIZE];
	int check = recv(this->server, str, sizeof(str), 0);
	if (check == SOCKET_ERROR) {
		//closesocket(this->server);
		return string();
	}
	str[check] = NULL;
	return string(str);
}

unsigned _stdcall SocketClient::SendThread(void* param)
{
	Map game;
	SocketClient client;
	client.server = (SOCKET)param;
	int x, y;
	char buff[2];
	while (1)
	{
		memset(&buff, 0, sizeof(buff));
		do
		{
			cout << "\nSelect cell (x, y): " << endl;
			cin >> x >> y;
			if (!game.isValid(x, y))
				cout << "Cell error!!!. Please select cell again." << endl;
		} while (!game.isValid(x, y));
		memset(&buff, 0, sizeof(buff));
		buff[0] = (char)x;
		buff[1] = (char)y;
		client.Send(buff);
	}
	system("pause");
	closesocket(client.server);
	WSACleanup();
	return 0;
}


SocketClient::~SocketClient()
{
	closesocket(this->server);
	WSACleanup();
}