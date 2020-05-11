#include "point.hpp"
#include <iostream>
#include <windows.h>

#define bonus 1
#define snake_head 2
#define snake_body 3


Point::Point()
{

}


Point::Point(int x,int y)
{
    position_x=x;
    position_y=y;
}


int Point::pos_x()
{
    return position_x;
}
int Point::pos_y()
{
    return position_y;
}

void Point::go_down()
{
    position_y++;
}

void Point::go_up()
{
    position_y--;
}

void Point::go_right()
{
    position_x++;
}

void Point::go_left()
{
    position_x--;
}

void Point::draw(int type)
{
    set_cursor_position(position_x,position_y);
    switch(type)
    {
        case bonus:
            {
                std::cout<<"T";
                break;
            }
        case snake_head:
            {
                std::cout<<"O";
                break;
            }
        case snake_body:
            {
                std::cout<<"o";
                break;
            }

    }

}



void Point::change_position_x(int x)
{
    position_x=x;
}

void Point::change_position_y(int y)
{
    position_y=y;
}

void Point::set_cursor_position(int x,int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}



Point& Point::operator =(Point &received)
{
    received.position_x=position_x;
    received.position_y=position_y;
    return received;
}
