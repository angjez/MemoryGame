#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <exception>
#include "Deck.h"


class Game{
    public:
        void startGame(Deck deck);
};

#endif /* Game_hpp */
