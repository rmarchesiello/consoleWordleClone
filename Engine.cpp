#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include "Engine.h"

Engine::Engine(std::set<std::string> _possGuess, std::string _word, char _emptyChar) : possibleGuesses(_possGuess), word(_word), emptyChar(_emptyChar), wordSize(_word.size()) {
	gameScore.resize(6, std::vector<char>(5, emptyChar));
	gameState.resize(6, std::vector<char>(5, emptyChar));
}

void Engine::printInstructions() { // Print the game's instructions
	std::cout << "You have 6 tries to guess the word!" << std::endl;
	std::cout << "Each guess will return to you which letters" << std::endl;
	std::cout << "are in the correct position (G) or are in " << std::endl;
	std::cout << "the word, but not in the correct position (Y)." << std::endl;
	std::cout << "All other letters will have a blank character (" << this->emptyChar << ")." << std::endl;
}

void Engine::printCurrentState() { // Print the game's state with guessed letters on board
	std::cout << "Current game state: " << std::endl;
	for (int r = 0; r < 6; r++) {
		for (int c = 0; c < 5; c++) {
			std::cout << this->gameState[r][c] << " ";
		}
		std::cout << std::endl;
	}
}

void Engine::printCurrentScore() { // Print the game's state with appraisal
	std::cout << "Current game score: " << std::endl;
	for (int r = 0; r < 6; r++) {
		for (int c = 0; c < 5; c++) {
			std::cout << this->gameScore[r][c] << " ";
		}
		std::cout << std::endl;
	}
}

void Engine::play() { // play the game, include IO
	this->printInstructions();
	std::cout << std::endl;

	do {
		std::string playerGuess;

		std::cout << "Guess a " << this->wordSize << "-letter word: ";
		std::cin >> playerGuess;

		if (std::cin.fail()) { // checks to make sure that the user entered an string value
			std::cin.clear();
			std::cin.ignore(2147483647, '\n');
			std::cout << "Error: invalid input; please enter a string." << std::endl << std::endl;
			continue;
		}

		if (playerGuess.size() != 5) {
			std::cin.clear();
			std::cin.ignore(2147483647, '\n');
			std::cout << "Error: Please enter a 5-letter word." << std::endl << std::endl;
			continue;
		}

		transform(playerGuess.begin(), playerGuess.end(), playerGuess.begin(), ::toupper);

		if (possibleGuesses.count(playerGuess) == 0) {
			std::cin.clear();
			std::cin.ignore(2147483647, '\n');
			std::cout << "Error: Not in word list." << std::endl << std::endl;
			continue;
		}

		checkWord(playerGuess);

		printCurrentState();
		std::cout << std::endl;
		printCurrentScore();
		std::cout << std::endl;

	} while (!gameOver());

	if (!fail) {
		std::cout << "Congratulations! You got the answer in " << turns << " turns!" << std::endl;
	} else {
		std::cout << "You lose! The word was \"" << word << "\"." << std::endl;
	}
}

void Engine::checkWord(std::string playerWord) { // check player word
	if (turns < 6) {
		int i = 0;
		for (auto& cell : gameState[turns]) {
			cell = playerWord[i];
			i++;
		}

		i = 0;
		for (auto& searchChar : playerWord) {
			size_t foundPos = word.find(searchChar);
			if (foundPos != std::string::npos) {
				if (foundPos == i) {
					gameScore[turns][i] = 'G';
				} else {
					gameScore[turns][i] = 'Y';
				}
			}
			i++;
		}

		turns++;
	}
}

bool Engine::gameOver() { // checks if game is over
	for (auto& row : gameScore) {
		int gCount = 0;
		for (auto& col : row) {
			if (col == 'G') {
				gCount++;
			}
		}
		if (gCount == 5) {
			return true;
		}
	}

	if (turns >= 6) {
		fail = true;
		return fail;
	}

	return false;
}
