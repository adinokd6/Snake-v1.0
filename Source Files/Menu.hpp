#ifndef Menu_hpp
#define Menu_hpp
#include "Gameview.hpp"
#include "settings.hpp"

 #include <Windows.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <fstream>



using namespace sf;

class Menu
{


    private:
        Font font;
        sf::SoundBuffer buffer;
        std::vector <int> score_board;
        std::fstream ranking_directory;



    public:
        Menu(void);
        ~Menu(void);
        void runMenu();
        void menu();
        void play();
        void settings();
        void ranking();
        void sorting();

    protected:
        enum MenuState{MENU,GAME,SETTINGS,RANKING,END};
        MenuState state;





};


#endif // Menu_hpp
