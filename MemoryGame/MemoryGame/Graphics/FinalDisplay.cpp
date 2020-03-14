#include "FinalDisplay.h"

void FinalDisplay::initializeFinalDisplay (ALLEGRO_DISPLAY *display, int points) {
    
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_flip_display();
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_flip_display();
    
//    add screen title
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon
    ALLEGRO_FONT *titleFont = al_load_ttf_font("orangejuice.ttf", 180, 180);
    al_draw_text(titleFont, al_map_rgb(106, 133, 178), 960, (40),ALLEGRO_ALIGN_CENTRE, "You won!");
    
//    add scoreboard
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d.%m.%Y %H:%M:%S");
    auto time = oss.str();
    scoreboard.insert(std::pair<int, std::string>(points, time));
    loadScoreboard();
    displayScoreboard();
    saveScoreboard();
    
//    add user hint
    ALLEGRO_FONT *hintFont = al_load_ttf_font("orangejuice.ttf", 120, 120);
    al_draw_text(hintFont, al_map_rgb(106, 133, 178), 960, (1200),ALLEGRO_ALIGN_CENTRE, "Click anywhere to play again!");
    
    
//    add sound effect
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);
    ALLEGRO_SAMPLE *wonSound = al_load_sample("wonSound.wav");
    al_play_sample(wonSound, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE,NULL);
    
    al_flip_display();
    
    ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    ALLEGRO_TIMEOUT timeout;
    al_init_timeout(&timeout, 0.06);
    al_install_mouse();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    while(1) {
        ALLEGRO_EVENT event;
        bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);
        if(get_event && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
           break;
        }
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            WelcomeDisplay welcomeDisplay;
            welcomeDisplay.initializeWelcomeDisplay();
        }
    }
    
    al_destroy_display(display);
//    saveScoreboard();
}

void FinalDisplay::loadScoreboard () {
    std::ifstream scoreboardFile;
    std::string time, points;
    scoreboardFile.open("scoreboard.txt");
    if(scoreboardFile.fail())
    {
        std::cerr<<"Could not open file!\n";
        exit(1);
    }

    while(!scoreboardFile.eof())
    {
        getline(scoreboardFile, points);
        getline(scoreboardFile, time);
        if(points!=""&&points!="\n"&&points!="\t"&&points!=" "&&time!=""&&time!="\n"&&time!="\t"&&time!=" ")
        { scoreboard.insert(std::pair<int, std::string>(std::stoi(points), time)); }
    }
    scoreboardFile.close();
}

void FinalDisplay::saveScoreboard () {
    std::ofstream scoreboardFile;
    scoreboardFile.open ("scoreboard.txt");
    std::multimap<int, std::string>::iterator it;
    for (it=scoreboard.begin(); it!=scoreboard.end(); ++it)
       scoreboardFile << (*it).first << '\n' << (*it).second << '\n';
    scoreboardFile.close();
}

void FinalDisplay::displayScoreboard () {
    ALLEGRO_FONT *font = al_load_ttf_font("OpenSans.ttf", 40, 40);
    ALLEGRO_FONT *titleFont = al_load_ttf_font("OpenSans.ttf", 80, 80);
    
    al_draw_text(titleFont, al_map_rgb(106, 133, 178), 960, (320),ALLEGRO_ALIGN_CENTRE, "Scoreboard:");
    
    int i = 0;
    std::map<int,std::string>::reverse_iterator rit;
    for (rit=scoreboard.rbegin(); rit!=scoreboard.rend(); ++rit) {
        if (i==5)
            break;
        std::string points = std::to_string(rit->first);
        al_draw_text(font, al_map_rgb(106, 133, 178), 720, (460+i*120),ALLEGRO_ALIGN_CENTRE, points.c_str());
        al_draw_text(font, al_map_rgb(106, 133, 178), 1060, (460+i*120),ALLEGRO_ALIGN_CENTRE, (rit->second).c_str());
        i++;
    }
}
