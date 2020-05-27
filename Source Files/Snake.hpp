#ifndef snake_hpp
#define snake_hpp
//////////////////////////
#include "point.hpp"
//////////////////////////
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include <iostream>
#include <deque>


enum Direction{up=0,down,right,left,stop};


class Snake : public Point
{
    private:
        std::deque <Point> body;
        int direction;
    public:

        friend class Board;
        Snake();
        Snake(int start_position_x,int start_position_y);
        void move(int game_height,int game_width);
        void draw();
        void add_cell(int x,int y);
        void gotoxy(int x,int y);
//        int get_0_pos();
//        int get_0_pos();
        int pos_x(int);
        int pos_y(int);
        int size_snake();
        void dir(int key);
};

#endif // snake_hpp
