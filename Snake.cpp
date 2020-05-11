#include "Snake.hpp"
#include "point.hpp"


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

void Snake::move(int game_height,int game_width)
{
    for(int i=body.size()-1;i>0;i--)
    {
        body[i-1]=body[i];
    }

    if(kbhit())
    {
        switch(getch())
            {
            case 'a':
                if(direction!=right)
                direction=left;
                break;
            case 'd':
                if(direction!=left)
                direction=right;
                break;
            case 'w':
                if(direction!=down)
                direction=up;
                break;
            case 's':
                if(direction!=up)
                direction=down;
                break;
            }
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

    if(get_pos_y()>=game_height)
    {
        body[0].change_position_y(0);
    }
    else if(get_pos_y()<0)
    {
        body[0].change_position_y(game_height-1);
    }
    else if(get_pos_x()>=game_height)
    {
        body[0].change_position_x(0);
    }
    else if(get_pos_x()<0)
    {
        body[0].change_position_x(game_width-1);
    }



}


int Snake::get_pos_x()
{
    return body[0].pos_x();
}

int Snake::get_pos_y()
{
    return body[0].pos_y();
}
