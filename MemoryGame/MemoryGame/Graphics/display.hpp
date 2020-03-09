#ifndef display_hpp
#define display_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "Deck.h"
#include "Card.h"
#include "Game.hpp"

class Game;

void initiateDisplay (Deck deck);
void loadCardBacks (ALLEGRO_BITMAP * image);
std::vector <int> manageClick (std::vector <int> coordinates, int x, int y);
void uncoverCard (Deck deck, int x, int y);

#endif /* display_hpp */
