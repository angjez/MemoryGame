#include "display.hpp"

void initiateDisplay (Deck deck) {
    int count =0, points=0;
    Game game;
    
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
    std::vector <float> coordinates;
    while(1)
    {
        loadCardBacks(image);
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
            if (coordinates.size() < 2) {
                coordinates.push_back(state.x);
                coordinates.push_back(state.y);
            }
            else if (coordinates.size() < 4) {
                if(coordinates[0]!=state.x)
                    coordinates.push_back(state.x);
                if(coordinates[1]!=state.y)
                    coordinates.push_back(state.y);
            }
            else {
                coordinates = manageClick(coordinates);
                uncoverCard(deck, coordinates[0], coordinates[1]);
                uncoverCard(deck, coordinates[2], coordinates[3]);
                game.move(deck, count, points, coordinates[0], coordinates[2], coordinates[1], coordinates[3]);
                coordinates.clear();
            }
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

std::vector <float> manageClick (std::vector <float> coordinates) {
    int x1 = 80, y1 = 240, x2 = 80+160, y2 = 240+160;
    for (int i = 0; i < 6; i++) {
        y1 = 240;
        y2 = 240+160;
        for (int j = 0; j < 6; j++) {
            if(x1 < coordinates[0] && coordinates[0] < x2 && y1 < coordinates[1] && coordinates[1] < y2) {
                coordinates[0] = i;
                coordinates[1] = j;
            }
            else if(x1 < coordinates[2] && coordinates[2] < x2 && y1 < coordinates[3] && coordinates[3] < y2) {
                coordinates[2] = i;
                coordinates[3] = j;
            }
            y1 = y1 + 200;
            y2 = y1 +160;
        }
        x1 = x1 + 320;
        x2 = x1 +160;
    }
    
    return coordinates;
}

void uncoverCard (Deck deck, int x, int y) {
    std::string name = deck.cards[x][y].name;
    ALLEGRO_BITMAP * img = al_load_bitmap(name.c_str());
    al_draw_bitmap(img, 0, 0, 0);
    al_flip_display();
    al_rest(3);
    al_destroy_bitmap(img);
}
