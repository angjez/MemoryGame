#ifndef FinalDisplay_h
#define FinalDisplay_h

#include <stdio.h>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

class FinalDisplay {
    public:
    std::multimap<int, std::string> scoreboard;
    void initializeFinalDisplay (ALLEGRO_DISPLAY *display, int points);
    void loadScoreboard();
    void saveScoreboard ();
    void displayScoreboard();
};

#endif /* FinalDisplay_h */
