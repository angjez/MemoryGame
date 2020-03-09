#include "display.hpp"

void initiateDisplay () {
    ALLEGRO_DISPLAY *display = NULL;
    
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize image addon
    

    if(!al_init()) {
       fprintf(stderr, "failed to initialize allegro!\n");
    }
    
    display = al_create_display(1920, 1440);
    al_clear_to_color(al_map_rgb(255, 255, 255));

//    add game title
    ALLEGRO_FONT *font = al_load_ttf_font("orangejuice.ttf", 180, 180);
    al_draw_text(font, al_map_rgb(106, 133, 178), 960, (40),ALLEGRO_ALIGN_CENTRE, "Memory");
//    load card backs
    ALLEGRO_BITMAP * image = al_load_bitmap("CardBack.png");
    loadCardBacks(image);
    
    al_flip_display();
    
//    add event queue
    ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    
    ALLEGRO_EVENT event;
    al_install_mouse();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    while(1)
    {
        ALLEGRO_MOUSE_STATE state;
        al_get_mouse_state(&state);
        
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.06);
        
        bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

        if(get_event && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
           break;
        }
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            std::cout<<std::endl<<">>CLICKED<<" <<state.x<<":"<<state.y << std::endl;
        }
    }
    
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(image);
    al_uninstall_mouse();
}

void loadCardBacks (ALLEGRO_BITMAP * image) {
    int x1 = 1920-240, y1 = 1440-200;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            al_draw_bitmap(image, x1 - i*320, y1-j*200,0);
        }
    }
}
