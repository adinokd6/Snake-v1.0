#include "Board.hpp"
#include "point.hpp"
#include "Snake.hpp"



#include <windows.h>
#include <iostream>
#include <conio.h>
#include "Gameview.hpp"

int main()
{
    int x,y;
    std::cout<<"Podaj wielkosc swojej planszy [Szerokosc x Wysokosc]\n";
    std::cin>>x;
    std::cin>>y;
    Board d(x,y);
    while(true)
    {
        d.game();
        Sleep(100);
    }



    return 0;
}
