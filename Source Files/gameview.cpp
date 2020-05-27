#include "Gameview.hpp"


#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>

#define closing_window -1

int size=16;//Size [in px] of 1 texture


enum GameType{normal=0,frame=1};

using namespace sf;

Gameview::Gameview(sf::RenderWindow &win, sf::Font &fon): snake((rand()%(game_width/16)),(rand()%(game_width/16))),apple((rand()%(game_width/16)-2),(1+rand()%(game_width/16))-2),diamond(40,40),bomb(1000,1000)
{
    window=&win;
    font=&fon;

    //Loading every textures from folders

    if(!frames.loadFromFile("Texture\\frame.png"))
    {
        MessageBox(NULL,"Font not found! You need to add frame.png in game directory","ERROR",NULL);
        return;
    }


    if(!body.loadFromFile("Texture\\body.bmp"))
    {
        MessageBox(NULL,"Font not found! You need to add body.bmp in game directory","ERROR",NULL);
        return;
    }


    if(!head.loadFromFile("Texture\\head.bmp"))
    {
        MessageBox(NULL,"Font not found! You need to add head.bmp in game directory","ERROR",NULL);
        return;
    }


    if(!background.loadFromFile("Texture\\background.png"))
    {
        MessageBox(NULL,"Font not found! You need to add background.png in game directory","ERROR",NULL);
        return;
    }


    if(!bonus.loadFromFile("Texture\\bonus.png"))
    {
        MessageBox(NULL,"Font not found! You need to add font.ttf in game directory","ERROR",NULL);
        return;
    }

    if(!tnt.loadFromFile("Texture\\bomb.png"))
    {
        MessageBox(NULL,"Font not found! You need to add font.ttf in game directory","ERROR",NULL);
        return;
    }

    if(!diax.loadFromFile("Texture\\diamond.png"))
    {
        MessageBox(NULL,"Font not found! You need to add font.ttf in game directory","ERROR",NULL);
        return;
    }

    if(!buffer.loadFromFile("Music\\game.wav"))
	{
		std::cout << "ERROR" << std::endl;
	}


    //Setting the main settings if they hasn't been loaded from the file or if the file is broken
    game_type=normal;
    bomb_on=true;
    audio_on=true;
    is_over=false;
    paused=false;
    menu=false;//Setting if the game need to return to the menu or not
    score=0;

    std::string tmp_set[3];
    int line_number=1;
    std::string line;
    settings_directory.open("Settings and ranking\\settings directory.txt",std::ios::in);
    while(getline(settings_directory,line))
    {
        switch (line_number)
        {
            case 1: tmp_set[0]=line; break;
            case 2: tmp_set[1]=line; break;
            case 3: tmp_set[2]=line; break;
        }
        line_number++;
    }
    settings_directory.close();

    if(tmp_set[0].compare("Audio Off")==0)
    {
        audio_on=false;
    }
    else
    {
        audio_on=true;
    }

    if(tmp_set[1].compare("Play with frames On")==0)
    {
        game_type=frame;
    }
    else
    {
        game_type=normal;
    }

    if(tmp_set[2].compare("Bomb On")==0)
    {
        bomb_on=true;
    }
    else
    {
        bomb_on=false;
    }

}


//Main game loop

int Gameview::runGame()
{
    Event event;
    Clock clock;
    sf::Sound sound;
    sound.setLoop(true);//Sound loop is true now. It will play againg when it end
    sound.setBuffer(buffer); //Setting audio to play while playing the game


//Setting the pause text options
    Text pause_text;
    pause_text.setFont(*font);
    pause_text.setCharacterSize(65);
    pause_text.setString("PAUSE");
    pause_text.setPosition(1280/2-pause_text.getGlobalBounds().width/2,20);
    pause_text.setColor(Color::White);

//Setting the score text
Text score_text;
score_text.setFont(*font);
score_text.setCharacterSize(50);
score_text.setPosition(score_text.getGlobalBounds().width,660);
score_text.setColor(Color::Red);








//Sprite which represent each texture of the game
    Sprite sprite1(background);
	Sprite sprite2(head);
	Sprite sprite3(body);
	Sprite sprite4(frames);
	Sprite sprite5(bonus);
	Sprite sprite6(tnt);
	Sprite sprite7(diax);


//Timer which help game to make delay level
	float timer=0;


//Audio is on or off
if(audio_on==true)
{
    sound.play();
}



//The main loop of the game
    while(menu==false)
    {




        while(window->pollEvent(event));
        {


            std::string score_to_string="Score: "; //Text showing the current score of the player
            score_to_string+=std::to_string(score);


            if(Keyboard::isKeyPressed(Keyboard::Escape)) //If escape key has been pressed the game end
            {
                menu=true;
            }


            if(Keyboard::isKeyPressed(Keyboard::P)) //If P key has been pressed the game pause
            {
                paused=true;
            }

            if(event.type==sf::Event::Closed)
            {
                menu=true;
                return closing_window;
            }


            if(game_type==frame) //If the game type is playing with frames after the reaching wall the game will end.
            {

                if(snake.pos_x(0)==game_height/16-1)
                {
                    menu=true;
                }
                else if(snake.pos_x(0)==1)
                {
                    menu=true;
                }
                else if(snake.pos_y(0)==game_width/16-1)
                {
                    menu=true;
                }
                else if(snake.pos_y(0)==1)
                {
                    menu=true;
                }

            }








            if(paused==true) //If game is paused it show pause menu
            {
                while(event.type!=sf::Event::Closed)
                {
                    window->waitEvent(event);
                    window->clear();
                    window->draw(pause_text);
                    window->display();

                    if(Keyboard::isKeyPressed(Keyboard::O)) //To end pause press O-key
                    {
                         paused=false;
                         break;
                    }
                }

                if(event.type==sf::Event::Closed)
                {
                    menu=true;
                    return closing_window;
                }

            }



            enum Direction{up=0,down,right,left,stop}; //Enumeration of the snake direction

            if(Keyboard::isKeyPressed(Keyboard::Left))
            {
                snake.dir(left);
            }
            else if(Keyboard::isKeyPressed(Keyboard::Right))
            {
                snake.dir(right);
            }
            else if(Keyboard::isKeyPressed(Keyboard::Up))
            {
                snake.dir(up);
            }
            else if(Keyboard::isKeyPressed(Keyboard::Down))
            {
                snake.dir(down);
            }



            float time=clock.getElapsedTime().asSeconds(); //Clock which help game to set the current speed
            clock.restart();
            timer+=time;


            if(timer>delay_level)
            {
                timer=0;
                snake.move(game_height/16,game_width/16);
            }


            window->clear();



            //Drawing the map of the game
            for (int i=0;i<game_height/16; i++)
            {
                for (int j=0;j<game_width/16; j++)
                {
                    if(game_type==frame)
                    {
                        if(j==0||i==0||i==game_height/16-1||j==game_width/16-1)
                        {
                            sprite4.setPosition(i*size,j*size);//Frames
                            window->draw(sprite4);
                        }
                        else
                        {
                            sprite1.setPosition(i*size,j*size); window->draw(sprite1);//Background
                        }
                    }
                    else
                    {
                        sprite1.setPosition(i*size,j*size); window->draw(sprite1);//Background
                    }


                }
            }

            //Drawing snake,body,food etc.
            for(int i=0;i<snake.size_snake(); i++)
            {
                if(i==0)
                {
                    sprite2.setPosition(snake.pos_x(0)*size, snake.pos_y(0)*size);//Head
                    window->draw(sprite2);
                }
                else
                {
                    sprite3.setPosition(snake.pos_x(i)*size, snake.pos_y(i)*size);//Body
                    window->draw(sprite3);
                }
            }

            sprite5.setPosition(apple.pos_x()*size,apple.pos_y()*size); window->draw(sprite5);//Apple
            sprite6.setPosition(bomb.pos_x()*size,bomb.pos_y()*size); //Bomb
            sprite7.setPosition(diamond.pos_x()*size,diamond.pos_y()*size); //Diamond



            if(snake.pos_y(0)==apple.pos_y()&& snake.pos_x(0)==apple.pos_x()) //If snake hit the apple it gets premium points and change the position of apple and bomb
            {
                snake.add_cell(1000,1000);
                apple.change_position_x(1+rand()%(game_height/16-2));
                apple.change_position_y(1+rand()%(game_width/16-2));
                if(bomb_on==true)
                {
                    bomb.change_position_x(rand()%(game_height/16)-2);
                    bomb.change_position_y(rand()%(game_width/16)-2);
                }

                int is_stop=0;
                if(is_stop==0&&score%100==0&&delay_level>=0.02) //If delay level is higher than 0.02 it makes snake after he eat an apple
                {
                    delay_level=delay_level-0.005;
                    is_stop++;

                }
                is_stop=0;

                score+=25;

            }

            if(score>300) //If score is higher than 300 draw diamond which give you 40 points
            {
               window->draw(sprite7);
            }





            for(int i=3;i<snake.size_snake();i++) //Checking if snake hit itself
            {
                if(snake.pos_x(0)==snake.pos_x(i)&&snake.pos_y(0)==snake.pos_y(i))
                {
                    menu=true;
                }
            }

            if(score>300&&bomb_on==true) //Set the position of the bomb
            {
                window->draw(sprite6);
            }

            if(snake.pos_y(0)==bomb.pos_y()&&snake.pos_x(0)==bomb.pos_x()) //If snake hit the bomb game end
            {
                menu=true;
            }

            if(snake.pos_y(0)==diamond.pos_y()&&snake.pos_x(0)==diamond.pos_x()) //If snake eat diamond...
            {
                snake.add_cell(1000,1000);
                diamond.change_position_x(rand()%(game_height/16-2));
                diamond.change_position_y(rand()%(game_width/16-2));
                score+=40;
            }

            score_text.setString(score_to_string);
            window->draw(score_text);






        }



    window->display();//Display the window
    }

    return score;
}
