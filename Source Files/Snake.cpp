#include "Snake.hpp"
#include "point.hpp"


#define normal_game 0
#define frame_game 1

Snake::Snake(): Point()
{

}


Snake::Snake(int start_position_x,int start_position_y)
{
    Point head(rand()%start_position_x,rand()%start_position_y);
    body.push_front(head);
}


void Snake::add_cell(int x,int y)
{
    Point cell(x,y);
    body.push_back(cell);
}

//Direction{up=0,down,right,left,stop};
void Snake::dir(int key)
{
    switch(key)
    {
            case left:
                if(direction!=right)
                direction=left;
                break;
            case right:
                if(direction!=left)
                direction=right;
                break;
            case up:
                if(direction!=down)
                direction=up;
                break;
            case down:
                if(direction!=up)
                direction=down;
                break;
    }
}


void Snake::move(int game_height,int game_width)
{
    for(int i=body.size()-1;i>0;i--)
    {
        body[i-1]=body[i];
    }

    switch(direction)
    {
        case left:
        {
            body[0].go_left();
            break;
        }
        case right:
        {
            body[0].go_right();
            break;
        }
        case up:
        {
            body[0].go_up();
            break;
        }
        case down:
        {
            body[0].go_down();
            break;
        }

    }

        if(pos_x(0)>=game_height)
        {
            body[0].change_position_x(0);
        }
        else if(pos_x(0)<0)
        {
            body[0].change_position_x(game_height);
        }
        else if(pos_y(0)>=game_width)
        {
        body[0].change_position_y(0);
        }
        else if(pos_y(0)<0)
        {
            body[0].change_position_y(game_width);
        }

}

int Snake::pos_x(int j)
{
    return body[j].position_x;
}

int Snake::pos_y(int j)
{
    return body[j].position_y;
}

int Snake::size_snake()
{
    return body.size();
}


//int Snake::get_pos_x()
//{
//    return body[0].pos_x();
//}
//
//int Snake::get_pos_y()
//{
//    return body[0].pos_y();
//}
