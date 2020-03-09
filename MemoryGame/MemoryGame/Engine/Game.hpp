#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <exception>
#include "Deck.h"
//#include "display.hpp"

class Game{
    public:
    void move(Deck & deck, int & count, int & points, int firstPos1, int firstPos2, int secPos1, int secPos2);
};

#endif /* Game_hpp */
