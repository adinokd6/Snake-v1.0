#include "Board.hpp"

#define frame_map 1
#define clear_map 0


Board::Board(int x,int y): snake(x,y),bonus((rand()%(x-2))+1,(rand()%(y-2))+1)
{
    game_width=x;
    game_height=y;
    field=new char *[game_height];
    for(int i=0;i<game_height;i++)
    {
        field[i]=new char[game_width];
    }
}


void Board::game(int game_type)
{
    system("cls");
    //snake.move(game_height,game_width);
    if(game_type==frame_map)
    {
        for(int i=0;i<game_height;i++)
        {
            for(int j=0;j<game_width;j++)
            {
                if(i==0||i==game_width-1)
                {
                    field[i][j]='*';
                }
                else if(j==0||j==game_height-1)
                {
                    field[i][j]='*';
                }
                else
                field[i][j]=NULL;
                std::cout<<field[i][j];
            }
                std::cout<<std::endl;
        }
    }
    else
    {
        for(int i=0;i<game_height;i++)
        {
            for(int j=0;j<game_width;j++)
            {
                field[i][j]=NULL;
                std::cout<<field[i][j];
            }
                std::cout<<std::endl;
        }
    }


    bonus.draw(1);
    if(snake.get_pos_y()==bonus.pos_y()&& snake.get_pos_x()==bonus.pos_x())
    {
        snake.add_cell(snake.get_pos_y(),snake.get_pos_x());
        bonus.change_position_x(rand()%(game_width-2)+1);
        bonus.change_position_y(rand()%(game_height-2)+1);
        bonus.draw(1);
    }
    for(int i=0;i<snake.body.size();i++)
    {
        snake.body[i].draw(3);
    }

}



void Board::change_size(int height_received,int width_received)
{
    game_height=height_received;
    game_width=width_received;
}



