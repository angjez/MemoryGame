#include "GameDisplay.h"

void initializeDisplay (ALLEGRO_DISPLAY *display) {
    int count =0, points=0;
    Deck deck;
    deck.addCards("cards.txt");
    Game game;
    
    al_flip_display();
    
//    initializations // TODO: add exeptions
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize image addon

    loadDeck(deck, points);
    
    al_flip_display();
    
//    add event queue
    ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    
    al_install_mouse();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    
//    add sound effects
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);
    ALLEGRO_SAMPLE *clickSound = al_load_sample("clickSound.wav");
    ALLEGRO_SAMPLE *matchedSound = al_load_sample("matchedSound.wav");
    
    mainLoop(count, points, deck, game, event_queue, clickSound, matchedSound);
  
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_uninstall_mouse();
    al_destroy_sample(clickSound);
    al_destroy_sample(matchedSound);
    al_uninstall_audio();
}

void mainLoop (int count, int points, Deck deck, Game game, ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_SAMPLE *clickSound, ALLEGRO_SAMPLE *matchedSound) {
    ALLEGRO_EVENT event;
      std::vector <int> coordinates;
      while(count < 36)
      {
          int up1, up2, up3, up4;
          ALLEGRO_MOUSE_STATE state;
          al_get_mouse_state(&state);
          
          ALLEGRO_TIMEOUT timeout;
          al_init_timeout(&timeout, 0.06);
          
          bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

          if(get_event && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
             break;
          }
          if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
              loadDeck(deck, points);
              al_flip_display();
              if (coordinates.size() < 2) {
                  coordinates.push_back(state.x);
                  coordinates.push_back(state.y);
                  al_play_sample(clickSound, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE,NULL);
                  coordinates = manageClick(coordinates, 0, 1);
                  up1 = coordinates[0];
                  up2 = coordinates[1];
                  deck.cards[up1][up2].faceUp = true;
                  loadDeck(deck, points);
                  al_flip_display();
              }
              else if (coordinates.size() < 4 && coordinates[0]!=state.x && coordinates[1]!=state.y) {
                  coordinates.push_back(state.x);
                  coordinates.push_back(state.y);
                  al_play_sample(clickSound, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE,NULL);
                  coordinates = manageClick(coordinates, 2, 3);
                  up3 = coordinates[2];
                  up4 = coordinates[3];
                  deck.cards[up3][up4].faceUp = true;
                  loadDeck(deck, points);
                  al_flip_display();
              }
              else {
                  deck.cards[up1][up2].faceUp = false;
                  deck.cards[up3][up4].faceUp =false;
                  if(game.move(deck, count, points, coordinates[0], coordinates[1], coordinates[2], coordinates[3]))
                     al_play_sample(matchedSound, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE,NULL);
                  loadDeck(deck, points);
                  al_flip_display();
                  coordinates.clear();
              }
          }
      }
}

void loadDeck (Deck deck, int points) {
    al_clear_to_color(al_map_rgb(255, 255, 255));
//    add game title
    ALLEGRO_FONT *titleFont = al_load_ttf_font("orangejuice.ttf", 180, 180);
    al_draw_text(titleFont, al_map_rgb(106, 133, 178), 960, (40),ALLEGRO_ALIGN_CENTRE, "Memory");
    
//    add point counter
    std::string displayPoints = "Points: " + std::to_string(points);
    ALLEGRO_FONT *font = al_load_ttf_font("OpenSans.ttf", 40, 40);
    al_draw_text(font, al_map_rgb(106, 133, 178), 1600, (40),ALLEGRO_ALIGN_CENTRE, displayPoints.c_str());
    
    int x1 = 80, y1 = 240;
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<6; j++)
        {
            if(!deck.cards[i][j].faceUp){
                ALLEGRO_BITMAP * cardBack = al_load_bitmap("CardBack.png");
                al_draw_bitmap(cardBack, x1 + i*320, y1+j*200, 0);
            }
            else if (deck.cards[i][j].matched){
                std::string name = "Matched.png";
                ALLEGRO_BITMAP * cardFront = al_load_bitmap(name.c_str());
                al_draw_bitmap(cardFront, x1 + i*320, y1+j*200, 0);
            }
            else{
                std::string name = deck.cards[i][j].name;
                ALLEGRO_BITMAP * img = al_load_bitmap(name.c_str());
                al_draw_bitmap(img, x1 + i*320, y1+j*200, 0);
            }
        }
    }
}


std::vector <int> manageClick (std::vector <int> coordinates, int x, int y) {
    int x1 = 80, y1 = 240, x2 = 80+160, y2 = 240+160;
    for (int i = 0; i < 6; i++) {
        y1 = 240;
        y2 = 240+160;
        for (int j = 0; j < 6; j++) {
            if(x1 < coordinates[x] && coordinates[x] < x2 && y1 < coordinates[y] && coordinates[y] < y2) {
                coordinates[x] = i;
                coordinates[y] = j;
            }
            y1 = y1 + 200;
            y2 = y1 +160;
        }
        x1 = x1 + 320;
        x2 = x1 +160;
    }
    return coordinates;
}