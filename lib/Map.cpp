/*
* This's the map for caro
* @author
* - Nguyen Phuc Loi Hai
* - 1660321
* @email
* - nploi1998@gmail.com
*/


#include "Map.h"

Map::Map() {
	map.resize(MAX_SIZE);
	for (int i = 0; i < map.size(); i++) {
		map[i].resize(MAX_SIZE);
		for (int j = 0; j < map[i].size(); j++){
			map[i][j] = ' ';
		}
	}
}

void Map::display() {
	system("cls");
	cout << "    ";
	for (int i = 0; i < map.size(); i++){
		cout << '-' << i;
	}
	cout << "- Y" << endl;
	cout << "    ";
	for (int i = 0; i <= map.size() * 2; i++){
		cout << '-';
	}
	for (int i = 0; i < map.size(); i++) {
		cout << endl << i << " - |";
		for (int j = 0; j < map[i].size(); j++){
			cout << map[i][j] << '|';
		}
		cout << endl << "    ";
		for (int i = 0; i <= map.size() * 2; i++){
			cout << "-";
		}
	}
	cout << "\nX";
}

bool Map::chess(int x, int y, char c){

	if ((x >= map.size() || x < 0 || y >= map[0].size() || y < 0) || map[x][y] != ' ') {
		return false;
	}

	map[x][y] = c;
	return true;
}

int Map::isWin(int x, int y, char c) {
	int countLess = 0, countGreat = 0;
	// check x to top and (x + 1) to down
	for (int i = x; i >= 0; i--){
		if (map[i][y] != c)
			break;
		countLess++;
	}
	for (int i = x + 1; i < map.size(); i++){
		if (map[i][y] != c)
			break;
		countGreat++;
	}
	if (countLess + countGreat >= WIN)
		return true;

	//check y to left and y + 1 to right
	countLess = 0, countGreat = 0;
	for (int i = y; i >= 0; i--){
		if (map[x][i] != c)
			break;
		countLess++;
	}
	for (int i = y + 1; i < map[0].size(); i++){
		if (map[x][i] != c)
			break;
		countGreat++;
	}
	if (countLess + countGreat >= WIN)
		return true;

	// check diagonal
	countLess = 0, countGreat = 0;
	for (int i = x, j = y; isValid(i, j); i--, j--) {
		if (map[i][j] != c)
			break;
		countGreat++;
	}

	for (int i = x + 1, j = y + 1; isValid(i, j); i++, j++) {
		if (map[i][j] != c)
			break;
		countGreat++;
	}

	if (countLess + countGreat >= WIN)
		return true;


	// check diagonal
	countLess = 0, countGreat = 0;
	for (int i = x, j = y; isValid(i, j); i++, j--) {
		if (map[i][j] != c)
			break;
		countGreat++;
	}

	for (int i = x - 1, j = y + 1; isValid(i, j); i--, j++) {
		if (map[i][j] != c)
			break;
		countGreat++;
	}

	if (countLess + countGreat >= WIN)
		return true;

	return false;
}


bool Map::isValid(int x, int y) {
	if (x < 0 || x >= map.size() || y < 0 || y >= map.size())
		return false;
	return true;
}

bool Map::isChess(int x, int y) {
	if (map[x][y] != 'O' && map[x][y] != 'X'){
		return true;
	}
	return false;
}

Map::~Map(){
	if (map.empty())
		return;
	for (int i = 0; i < map.size(); i++){
		if (map[i].empty())
			continue;
		map[i].clear();
	}
	map.clear();
}