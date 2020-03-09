#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <random>
#include <chrono>
#include "Card.h"
class Deck
{

	public:
    static const int ROWS=6;
    static const int COLS=6;
	Card cards[ROWS][COLS];
	Deck();
	void addCards(std::string fileName);
};

#endif
