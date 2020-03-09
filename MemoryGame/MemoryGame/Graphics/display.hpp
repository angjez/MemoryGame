#ifndef display_hpp
#define display_hpp

#include <stdio.h>
#include <iostream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

void initiateDisplay ();
void loadCardBacks (ALLEGRO_BITMAP * image);
void loadDisplayClosedEvent (ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_DISPLAY *display);

#endif /* display_hpp */
