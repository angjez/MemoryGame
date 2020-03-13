#ifndef Game_h
#define Game_h

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <exception>
#include "Deck.h"

class Game{
    public:
    bool move(Deck & deck, int & count, int & points, int firstPos1, int firstPos2, int secPos1, int secPos2);
};

#endif /* Game_h */
