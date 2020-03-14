#include "FinalDisplay.h"

void FinalDisplay::initializeFinalDisplay (ALLEGRO_DISPLAY *display, int points) {
    
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_flip_display();
    
//    add screen title
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon
    ALLEGRO_FONT *titleFont = al_load_ttf_font("orangejuice.ttf", 180, 180);
    al_draw_text(titleFont, al_map_rgb(106, 133, 178), 960, (40),ALLEGRO_ALIGN_CENTRE, "You won!");
    
//    add scoreboard
    time_t gameTime = time(NULL);
    scoreboard.insert(std::pair<int, std::string>(points, ctime(&gameTime)));
    loadScoreboard();
    saveScoreboard();
    
    
//    add sound effect
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);
    ALLEGRO_SAMPLE *wonSound = al_load_sample("wonSound.wav");
    al_play_sample(wonSound, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE,NULL);
    
    al_flip_display();
    
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
    
}
