#ifndef gameview_hpp
#define gameview_hpp



#include "Snake.hpp"
#include "point.hpp"

#include <Windows.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <vector>





class Gameview
{
    private:
        sf::RenderWindow *window;
        sf::Font *font; //Normal font sent by menu
        sf::Texture head,body,frames,background,bonus,diax,tnt;
        sf::SoundBuffer buffer;

        enum Game{PLAY,PAUSE,GAME_OVER};
        Game state;

        int game_type;
        float delay_level=0.07;
        int game_width=720;
        int game_height=1280;
        int score;
        bool is_over;
        bool paused;
        bool menu;
        bool audio_on;
        bool bomb_on;

        std::fstream settings_directory;


        Snake snake;
        Point apple;
        Point diamond;
        Point bomb;


    public:
        Gameview(sf::RenderWindow &win, sf::Font &fon);
        int runGame();



};

#endif // gameview_hpp
