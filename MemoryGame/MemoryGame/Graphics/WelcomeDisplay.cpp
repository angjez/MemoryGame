#include "WelcomeDisplay.h"

void WelcomeDisplay::initializeWelcomeDisplay () {
    
    ALLEGRO_DISPLAY *display = NULL;
    if(!al_init()) {
       fprintf(stderr, "failed to initialize allegro!\n");
    }
    
    display = al_create_display(1920, 1440);
    al_clear_to_color(al_map_rgb(255, 255, 255));
    
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT *titleFont = al_load_ttf_font("orangejuice.ttf", 480, 480);
    al_draw_text(titleFont, al_map_rgb(106, 133, 178), 960, (320),ALLEGRO_ALIGN_CENTRE, "Memory");
    
    al_flip_display();
    
    al_rest(3);

    al_clear_to_color(al_map_rgb(255, 255, 255));
    GameDisplay gameDisplay;
    gameDisplay.initializeDisplay(display);
}
