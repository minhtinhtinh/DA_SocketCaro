#include "Player.h"


Player::Player()
{
}

string Player::receive() {
	char str[MAX_TEXT];
	int check = recv(socket, str, sizeof(str), 0);
	if (check == SOCKET_ERROR) {
		closesocket(socket);
		return string();
	}
	str[check] = NULL;
	return string(str);
}

bool Player::sendAText(string text) {
	int check = send(socket, text.c_str(), text.size(), 0);

	if (check != SOCKET_ERROR) {
		return 1;
	}
	closesocket(socket);
	return 0;
}

Player::~Player()
{
}

bool Player::sendXYWin(int x, int y, int win) {
	std::ostringstream os;
	os << x << " " << y << " " << win;
	cout << "Sent to " << name << " : " << os.str() << endl;
	if (!this->sendAText(os.str())){
		cout << name << " outed !!\n";
		return false;
	}
	return true;
}
