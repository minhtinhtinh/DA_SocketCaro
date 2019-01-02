/*
* This's socket and some structures for project
* @author
* - Nguyen Phuc Loi
* - 1660321
* @email
* - nploi1998@gmail.com
*/

#pragma once
#include <pthread.h>
#include <iostream> 
#include <stdio.h>
#include <WinSock2.h>
#include <map>
#include <string.h>
#include <string>
#include <sstream>

#define MAX_TEXT 50

using namespace std;

class Player {
public:
	Player();

	/*
	@describe
		Receive a text from client
	@param
		NULL
	@return
		if success will return text from client
		else return string empty
	*/
	string receive();

	/*
	@describe
		Send a text to client
	@param
		text: string
	@return
		if success will return true
		else return false
	*/
	bool sendAText(string text);


	/*
	@describe
		Send x, y, win for player
	@param
		player: Player
	@return
		success: true
		not success: false
	*/
	bool sendXYWin(int x, int y, int win);

	~Player();
public:
	SOCKET socket;
	string name;
	pthread_t thread;
	sockaddr_in clientAddr;
	char chessman;
};
