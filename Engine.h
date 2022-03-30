#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

class Engine {
private:
	std::string word;
	int wordSize;
	char emptyChar;
	std::vector<std::vector<char>> gameState;
	std::vector<std::vector<char>> gameScore;
	int turns = 0;
	bool fail = false;
	std::set<std::string> possibleGuesses;

public:
	Engine(
		std::set<std::string> _possGuess,
		std::string _word = "TRAIL",
		char _emptyChar = '-'
	);

	void printInstructions(); // Print the game's instructions
	void printCurrentState(); // Print the game's state with guessed letters on board
	void printCurrentScore(); // Print the game's state with appraisal
	void play(); // play the game, include IO
	void checkWord(std::string playerWord); // check player word
	bool gameOver(); // checks if game is over
};