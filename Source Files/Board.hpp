#ifndef board_hpp
#define board_hpp
////////////////////////////////
#include "Snake.hpp"
#include "point.hpp"
///////////////////////////////
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <windows.h>




class Board
{
    private:
        Snake snake;
        Point bonus;
        char **field;
        int score;
        int game_type;
        int delay_level;
        int game_width;
        int game_height;
        bool game_status;
    public:
        Board(int x,int y);
        void change_size(int height_received,int width_received);
        void game(int game_type);
        void set_cursor_position(int x,int y);

};


#endif // board_cpp
