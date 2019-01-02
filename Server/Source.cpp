/*
* @author
* - Nguyen Phuc Loi
* - 1660321
* @email
* - nploi1998@gmail.com
*/

#include "SocketServer.h"
#include <WS2tcpip.h>
#include <process.h>
#include <queue>
#include "Match.h"
using namespace std;

#define BUFF_SIZE 50

//Content the names of client
map<string, bool> hash;

//Queue content players when it connected
queue<Player> queuePlayers;


/*
	@describe
		Register an account
	@param
		param: void
	@return
		NULL
*/
void *registerAccount(void *param);


/*
@describe
	communication between players
@param
	player01: player
	player02: player
@return
	2: player01 is out
	1: player01 is win
	0: not win
*/
int communication(Player player01, Player player02, Map &game);



/*
@describe
	Start new match
@param
	param: void
@return
	NULL
*/
void *startMatch(void *param);



/*
@describe	
	Check player, do you want to play continue
@param
	player: Player
@return
	agree: true
	not agree: false
*/
int playContinue(Player &player);


/*
@describe	
	Check queue of players, if queue have more 2 player connect to add 2 player in game
@param
	player: Player
@return
	agree: true
	not agree: false
*/
void checkQueue() {
	cout << "\nNumber plays in queue is: " << queuePlayers.size() << endl;
	if (queuePlayers.size() >= 2){
		Match *m = new Match;
		m->addPlayer(queuePlayers.front());
		queuePlayers.pop();
		m->addPlayer(queuePlayers.front());
		queuePlayers.pop();
		
		// If have 2 players, will start new Match
		pthread_create(&m->thread, NULL, startMatch, (void*)m);
	}
}


int main() {
	/*
		If cannot init socket for server, program will throw exception
		*/
	SocketServer server;
	try {
		server.init(PORT, SERVER_ADDR);
	}
	catch (int exception){
		if (exception == ERROR_INIT){
			cout << "Error!! Cannot init server !!";
			system("pause");
			return 0;
		}
	}

	cout << "*** SERVER'S OPENING !! ***\n";

	while (true) {
		// Init new match
		Player *playerTemp = new Player;

		//new connection
		*playerTemp = server.accepted();

		cout << playerTemp->socket << " connected\n";

		//start thread for user create an account anh add in new game
		pthread_create(&playerTemp->thread, NULL, registerAccount, (void*)playerTemp);
	}

	return 0;
}

void *registerAccount(void *param) {
	char buff[50];
	Player *client = (Player*)param;
	string sucess = "0";
	string userName;
	while (true) {

		userName = client->receive();
		// Client outed, will close socket
		if (userName.empty()) {
			closesocket(client->socket);
			break;
		}
		// Check if user is exist, will send for client '0', else '1'
		if ((bool)(::hash.find(userName) == ::hash.end()) == true) {

			sucess = "1";
			::memset(&buff, 0, sizeof(buff));//clear the buffer
			strcpy_s(buff, sucess.c_str());
			::hash.insert(pair<string, bool>(userName, 1));
			client->name = userName;
			queuePlayers.push(*client);
			checkQueue();
			//if register succes, will send for client '1' and '0' is fail
			client->sendAText(sucess);

			break;
		}
		else {
			sucess = "0";
			//if register succes, will send for client '1' and '0' is fail
			client->sendAText(sucess);
		}
	}

	::cout << client->name << " registered success !!\n";

	pthread_cancel(client->thread);
	
	return NULL;
}

void *startMatch(void *param) {

	int chessMan = 0;
	Match* game = (Match*)param;
	string text;

	while (true) {
		Player target;
		Map map;
		int n = 0;
		int check = 0;
		// Send which player plays before
		game->players[0].chessman = 'X';
		game->players[0].sendAText("0 " + game->players[1].name);
		game->players[1].chessman = 'O';
		game->players[1].sendAText("1 " + game->players[0].name);

		while (check == 0) {
			if (n % 2 == 0){
				check = communication(game->players[1], game->players[0], map);
			}
			else {
				check = communication(game->players[0], game->players[1], map);
			}
			n++;
		}

		// Check players plays continue
		int agree01 = 0, agree02 = 0;
		agree01 = playContinue(game->players[0]);
		agree02 = playContinue(game->players[1]);
		if (agree01 && agree02) {
			continue;
		}
		if (agree02) {
			queuePlayers.push(game->players[1]);
			checkQueue();
		}
		if (agree01) {
			queuePlayers.push(game->players[0]);
			checkQueue();
		}
		break;
	}
	pthread_cancel(game->thread);
	return NULL;
}

int communication(Player player01, Player player02, Map &game) {
	string data;
	int x, y, win;
	do {
		data = player01.receive();
		if (data == string()) {
			player02.sendAText("exit");
			cout << player02.name << " outed !!\n";
			return 2;
		}

		istringstream in(data);
		in >> x >> y;

	} while (!game.isValid(x, y));

	cout << player01.name << " sent (" << x << ", " << y << ")" << endl;

	game.chess(x, y, player01.chessman);
	win = game.isWin(x, y, player01.chessman);


	if (win == 1) {
		return 1;
		if (player01.sendXYWin(x, y, 1) == false) {
			player02.sendAText("exit");
		}
		if (player02.sendXYWin(x, y, -1) == false) {
			player01.sendAText("exit");
		}
	}
	else {
		if (player01.sendXYWin(x, y, 0) == false) {
			player02.sendAText("exit");
		}
		if (player02.sendXYWin(x, y, 0) == false) {
			player01.sendAText("exit");
		}
	}
	return 0;
}

int playContinue(Player &player) {
	string check = player.receive();
	if (check.empty()) {
		return 0;
	}
	if (check[0] == '1') {
		return 1;
	}
	if (check[0] == '0') {
		return 0;
	}
	return false;
}