#include "Game.hpp"
#include <sstream> 

Game::Game() : userTurn(true), active(true) {
	for (int i = 0; i < 9; ++i)
		board[i] = ' ';
}

void Game::reset() {
	userTurn = true;
	active = true;
	for (int i = 0; i < 9; ++i)
		board[i] = ' ';
}

bool Game::isUserTurn() const {
	return userTurn;
}

void Game::setUserTurn(bool turn) {
	userTurn = turn;
}

bool Game::isActive() const {
	return active;
}

void Game::setActive(bool state) {
	active = state;
}

char Game::getCell(int index) const {
	if (index < 0 || index >= 9)
		throw std::out_of_range("Index out of range");
	return board[index];
}

void Game::setCell(int index, char value) {
	if (index < 0 || index >= 9)
		throw std::out_of_range("Index out of range");
	if (value != 'X' && value != 'O' && value != ' ')
		throw std::invalid_argument("Invalid cell value");
	board[index] = value;
}

int Game::checkWin() const {
	const int lines[8][3] = {
		{0, 1, 2}, {3, 4, 5}, {6, 7, 8},
		{0, 3, 6}, {1, 4, 7}, {2, 5, 8},
		{0, 4, 8}, {2, 4, 6}
	};
	for (int l = 0; l < 8; ++l) {
		char a = board[lines[l][0]];
		if (a != ' ' && a == board[lines[l][1]] && a == board[lines[l][2]])
			return a == 'X' ? 1 : 2;
	}
	bool full = true;
	for (int i = 0; i < 9; ++i) {
		if (board[i] == ' ') {
			full = false;
			break;
		}
	}
	return full ? 3 : 0;
}

std::string Game::drawBoard(std::string nick) {
	std::ostringstream o;
	o << "[🤖] BEEP-BEEP! " << nick << " player board:\n";
	for (int i = 0; i < 9; ++i) {
		o << (board[i] == ' ' ? char('1'+i) : board[i]);
		if (i%3==2) o << (i==8?"":"\n"); else o << " | ";
	}
	return o.str();
}
