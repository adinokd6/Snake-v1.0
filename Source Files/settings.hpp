#ifndef settings_hpp
#define settings_hpp


#include <Windows.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>


using namespace sf;



class Settings
{
    private:
    std::fstream settings_directory;
    std::vector <std::string> saved;
    sf::RenderWindow *window;
    sf::Font *font1;
    public:

    Settings(sf::RenderWindow &win, sf::Font &fon);


    void settings();
};


#endif // settings_hpp
