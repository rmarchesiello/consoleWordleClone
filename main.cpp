#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include "Engine.h"

using namespace std;

int main() {
    
    srand(time(0));

    vector<string> wordsVec;
    set<string> guessesSet;

    ifstream wordsTxt;
    ifstream guessesTxt;

    string wordsPath = "words.txt";
    string word;

    string guessPath = "guesses.txt";
    string guess;

    wordsTxt.open(wordsPath);
    guessesTxt.open(guessPath);

    while (wordsTxt >> word) {
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        wordsVec.push_back(word);
    }

    while (guessesTxt >> guess) {
        transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
        guessesSet.insert(guess);
    }

    wordsTxt.close();
    guessesTxt.close();

    int randomIndex = rand() % wordsVec.size();

    Engine game1(guessesSet, wordsVec[randomIndex], '-');

    game1.play();

}