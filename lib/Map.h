#pragma once
/*
* This's the map for caro
* @author
* - Nguyen Phuc Loi
* - 1660321
* @email
* - nploi1998@gmail.com
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define WIN 4
#define MAX_SIZE 10

class Map {
public:
	/*
	* init size MAX_SIZE x MAX_SIZE
	*/
	Map();

	/*
	*  - Display map of CARO
	*   exp: 3-3
	*   -------
	*   | | | |
	*   -------
	*   | | | |
	*   -------
	*   | | | |
	*   -------
	*/
	void display();

	/*
	*@Params
	*   x: integer
	*   y: integer
	*   c: character
	*   (x,y) is location of map
	*   c: is character of client
	*/
	bool chess(int x, int y, char c);

	/*
	*@Params
	*   x: integer
	*   y: integer
	*   c: character
	*   (x,y) is location of map
	*   c: is X or O/
	*@return
	* win or not win (true or false)
	*/
	int isWin(int x, int y, char c);


	/*
	*@Params
	*   x: integer
	*   y: integer
	* Check location is valid or invalid
	*@return
	*   (true or false)
	*/
	bool isValid(int x, int y);

	bool isChess(int x, int y);

	~Map();
private:
	std::vector<vector<char> > map;
};

//int main() {
//
//	/*
//	* Init values
//	*/
//	Map m;
//	int n = 0, isWin = 0;
//
//	/*
//	* Logic games
//	*/
//	while (true){
//		m.display();
//		if (isWin){
//			cout << (((n - 1) % 2 == 0) ? "\n\nPlayer 1 (X)" : "\n\nPlayer 2 (O)") << " is Win !!\n";
//			break;s
//		}
//		int x, y, check = 1;
//		do {
//			cout << ((n % 2 == 0) ? "\n\nPlayer 1 (X)" : "\n\nPlayer 2 (O)");
//			cout << "\n(x, y) >>";
//			cin >> x >> y;
//			check = m.chess(x, y, ((n % 2 == 0) ? 'X' : 'O'));
//
//			if (check)
//			{
//				isWin = m.isWin(x, y, ((n % 2 == 0) ? 'X' : 'O'));
//				break;
//			}
//			cout << "you select is wrong!!\nTry again\n";
//		} while (true);
//
//		n++;
//	}
//	system("pause");
//	return 0;
//}