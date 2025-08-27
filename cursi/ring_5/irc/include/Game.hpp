#ifndef GAME_HPP
#define GAME_HPP

#include <string>

class Game {
private:
	char board[9];
	bool userTurn;
	bool active;

public:
	Game();
	void reset();
	bool isUserTurn() const;
	void setUserTurn(bool turn);
	bool isActive() const;
	void setActive(bool state);
	char getCell(int index) const;
	void setCell(int index, char value);
	int checkWin() const;
	std::string drawBoard(std::string nick);
};

#endif