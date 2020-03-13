#ifndef GameDisplay_h
#define GameDisplay_h

#include <stdio.h>
#include <iostream>
#include <vector>
#include "allegro5/allegro.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "Deck.h"
#include "Card.h"
#include "Game.h"

class Game;

void initializeDisplay (ALLEGRO_DISPLAY *display);
void mainLoop (int count, int points, Deck deck, Game game, ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_SAMPLE *clickSound, ALLEGRO_SAMPLE *matchedSound);
void loadDeck (Deck deck, int points);
std::vector <int> manageClick (std::vector <int> coordinates, int x, int y);

#endif /* GameDisplay_h */
