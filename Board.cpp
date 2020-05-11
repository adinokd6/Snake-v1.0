#include "Board.hpp"

Board::Board(int x,int y): snake(x,y),bonus(rand()%x,rand()%y)
{
    game_width=x;
    game_height=y;
    field=new char *[game_height];
    for(int i=0;i<game_height;i++)
    {
        field[i]=new char[game_width];
    }
}


void Board::game()
{
    system("cls");
    snake.move(game_height,game_width);
    for(int i=0;i<game_height;i++)
    {
        for(int j=0;j<game_width;j++)
        {
            field[i][j]=NULL;
            std::cout<<field[i][j];
        }
        std::cout<<std::endl;

    }

    bonus.draw(1);
    if(snake.get_pos_y()==bonus.pos_y()&& snake.get_pos_x()==bonus.pos_x())
    {
        snake.add_cell(snake.get_pos_y(),snake.get_pos_x());
        bonus.change_position_x(rand()%game_width);
        bonus.change_position_y(rand()%game_height);
        bonus.draw(1);
    }
    for(int i=0;i<snake.body.size();i++)
    {
        snake.body[i].draw(3);
    }


}



