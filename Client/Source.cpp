/*
* @author
* - Nguyen Nhut Minh
* - 1660345
* @email
* - nhutminh12a21998@gmail.com
*/


#include "SocketClient.h"
#include <sstream>

/*
@describe
	find opponent. if exists opponent return n (variable character 0 -> 'O' or 1 -> 'X'), else return -1;
@param
	socket & buff 
@return
	agree: 0 or 1
	not agree: -1
*/
int findPlayer(SocketClient &client, string buff, string &opponentName)
{
	int n;
	cout << "Finding player ..."<<endl;
	do {
		buff.clear();
		buff = client.Receive();
		if (buff.empty())
			return -1;
		n = (int)buff[0] - 48;
		opponentName = buff.substr(2,buff.length()-2);
		if (n == 0 || n == 1)
			break;
	} while (1);
	return n;
}

/*
@describe
	Ask player have play continue or haven't play conntinue. Player seclect 1 to continue or 0 to stop
@param
	socket & value continue
@return
	agree: return 1 if send to server success  
	not agree: return 0 if error
*/
int playContinue(SocketClient &client, int valContinue)
{
	string str;
	str += (char)(valContinue + 48);
	return client.Send(str.c_str());
}



int main()
{
	SocketClient client;
	string buff;
	int quanlityWin=0;
	int totalMatch=0;

	int Continue = 1;

	//init client
	try
	{
		client.InitClient(SERVER_ADDR, PORT);
	}
	catch (int exception)
	{
		if (exception == ERROR_INIT)
		{
			cout << "ERROR! cannot init client" << endl;
			closesocket(client.getClient());
			WSACleanup();
			system("pause");
			exit(1);
			return 0;
		}
		else
			cout << "Connected to server" << endl;
	}

	//register username
	string username;
	do
	{
		cout << "Username of Player: ";
		getline(cin, username);
		client.registerUsername(username);

		//receive result register username(1: success, 0: error. Do again)
		buff = client.Receive();

		if (buff.empty()){
			cout << "ERROR! cannot init client" << endl;
			closesocket(client.getClient());
			WSACleanup();
			system("pause");
			exit(1);
			break;
		}

		if ((int)buff[0] == '1')
		{
			cout << "Register success !!" << endl;
			break;
		}
		else
			cout << "Username existed. Please select username different!!!" << endl;
		buff.clear();
	} while (1);

	do
	{
		int n;
		string opponentName;
		n = findPlayer(client, buff, opponentName);
		if (n == -1)
		{
			Continue = 0;
			cout << "\nERROR!!\nDisconnect to server ... !\n";
			break;
		}
		system("cls");
		char chessMan1 = ((n % 2 == 0) ? 'X' : 'O');
		char chessMan2 = (!(n % 2 == 0) ? 'X' : 'O');
		totalMatch++;
		//communicate between two client
		int x, y;
		char point[2];
		int win;
		Map game;
		game.display();
		while (1)
		{
			cout << endl << "~*~*~*~ PLAY CHESS GAME ~*~*~*~" << endl;
			cout << username << " VS " << opponentName << endl;	//note name's player with name's opponent
			cout << "You: " << chessMan1 << endl;
			cout << opponentName + ": " << chessMan2 << endl;

			if (n % 2 != 0)
			{
				win = 0;
				do
				{
					cout << endl << ">>> Select cell (x, y): " << endl;
					cin >> x >> y;
					if (!game.isValid(x, y) || !game.isChess(x, y))
						cout << "Cell error!!! Please select cell again." << endl;
				} while (!game.isValid(x, y) || !game.isChess(x, y));
				memset(&buff, 0, sizeof(point));
				point[0] = (char)(x + 48);
				point[1] = ' ';
				point[2] = (char)(y + 48);
				int check = client.Send(point);

				if (check == 0) {
					Continue = 0;
					break;
				}

				game.chess(x, y, chessMan1);
				game.display();

				//receive result win
				buff.clear();
				buff = client.Receive();

				if ("exit" == buff.substr(0, 4)) 
				{
					cout << endl << "Congratulation!!! You win" << endl;
					break;
				}
				std::istringstream in(buff);
				in >> x >> y >> win;
				if (win == 1)
				{
					cout << endl << "You win!!! Congratulation" << endl;
					quanlityWin++;
					break;
				}
				else
				{
					if (win == -1)
					{
						cout << endl << "You lost!!!" << endl;
						break;
					}
				}
			}
			else
			{
				//receive point(x, y) from opponent
				cout << endl << ">>> Waiting " + opponentName + "...." << endl;
				win = 0;
				buff.clear();
				buff = client.Receive();

				if (buff.empty()) {
					Continue = 0;
					break;
				}

				std::istringstream in(buff);
				in >> x >> y >> win;
				game.chess(x, y, chessMan2);
				game.display();
				if (buff == "exit")
				{
					cout << endl << "Congratulation!!! You win" << endl;
					break;
				}
				if (win == 1)
				{
					cout << endl << "You win!!! Congratulation" << endl;
					quanlityWin++;
					break;
				}
				else
				{
					if (win == -1)
					{
						cout << endl << "You lost!!!" << endl;
						break;
					}
				}

			}
			n++;
		}

		if (Continue == 0)
		{
			cout << "\nERROR!!\nDisconnect to server ... !\n";
			break;
		}

		cout <<endl << "You Won " << quanlityWin << "/" << totalMatch << endl;

		//select continue
		int valContinue;
		while (1)
		{
			cout <<endl << "Do you want continue? Select 1 to continue or 0 to stop" << endl;
			cin >> valContinue;
			if (valContinue == 1 || valContinue == 0)
				break;
			cout << "Error!!! Only select 0 or 1" << endl;
		}
		playContinue(client, valContinue);
		if (valContinue == 1) {
			cout << "Continue play chess" << endl;
		}
		else
		{
			cout << "Stop!!!" << endl;
			break;
		}
	} while (1);

	closesocket(client.getClient());
	WSACleanup();
	system("pause");
	exit(1);
	return 0;
}