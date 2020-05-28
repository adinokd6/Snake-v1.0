#include "Menu.hpp"


#define closing_window -1

RenderWindow window;




Menu::Menu(void)
{
    window.create(VideoMode(1280,720),"SNAKE v1.0 by adinokd6",Style::Default);

    state=END;
    window.setFramerateLimit(60);


    if(!font.loadFromFile("Fonts\\arial.ttf"))
    {
        MessageBox(NULL,"Font not found! You need to add font.ttf in game directory","ERROR",NULL);
        return;
    }

    if (!buffer.loadFromFile("Music\\menu.wav"))
	{
		std::cout << "ERROR" << std::endl;
	}

    state=MENU;
}

//Destructor
Menu::~Menu(void)
{
}

//Funcion responsible for checking the menu status
void Menu::runMenu()
{

     while(state!=END)
     {
        switch (state)
        {
            case MENU:
                menu();
                break;

            case SETTINGS:
                settings();
                break;

            case RANKING:
                ranking();
                break;

            case GAME:
                play();
                break;
        }
     }
}



//Main function showing the game menu
void Menu::menu()
{
    sf::Sound sound;

    sound.setLoop(true);
	sound.setBuffer(buffer);

    Text title("SNAKE",font,100); //Setting title
    title.setStyle(Text::Bold);
    title.setColor(Color::Red);

    title.setPosition(1280/2-title.getGlobalBounds().width/2,20);

    const int modes=4;

     Text tekst[modes];

     std::string str[] = {"Play","Settings","Ranking","Exit"};
     for(int i=0;i<modes;i++) //Setting menu option texts
     {
        tekst[i].setFont(font);
        tekst[i].setCharacterSize(65);
        tekst[i].setString(str[i]);
        tekst[i].setPosition(1280/2-tekst[i].getGlobalBounds().width/2,250+i*120);

     }
    sound.play();

 while(state==MENU) //If menu is true then..
 {
    Vector2f mouse(Mouse::getPosition(window));
    Event event;

      while(window.pollEvent(event)) //If mouse is on text it change the color of it
      {

           if(event.type==Event::Closed||event.type==Event::KeyPressed&&event.key.code==Keyboard::Escape)
           {
               state=END;
           }

           else if(tekst[0].getGlobalBounds().contains(mouse)&&event.type==Event::MouseButtonReleased&&event.key.code==Mouse::Left)
           {
            state=GAME;
           }

           else if(tekst[1].getGlobalBounds().contains(mouse)&&event.type==Event::MouseButtonReleased&&event.key.code==Mouse::Left)
           {
            state=SETTINGS;
           }

           else if(tekst[2].getGlobalBounds().contains(mouse)&&event.type==Event::MouseButtonReleased&&event.key.code==Mouse::Left)
           {
            state=RANKING;
           }

           else if(tekst[3].getGlobalBounds().contains(mouse)&&event.type==Event::MouseButtonReleased&&event.key.code==Mouse::Left)
           {
            state=END;
           }
    }

          for(int i=0;i<modes;i++)
          {
                if(tekst[i].getGlobalBounds().contains(mouse))
                {
                    tekst[i].setColor(Color::Red);
                }
                else
                {
                    tekst[i].setColor(Color::Black);
                }
          }

          window.clear(Color::White);

          window.draw(title);
          for(int i=0;i<modes;i++)
          {
              window.draw(tekst[i]);
          }


          window.display();
     }


}

//Funcion calling settings
void Menu::settings()
{
    Settings settings(window,font);
    settings.settings();
    state=MENU;
}

//Funcion calling game window
void Menu::play()
{
    Text game_over; //Text which is showed when the game is ended.
    game_over.setFont(font);
    game_over.setCharacterSize(50);
    game_over.setStyle(Text::Bold);
    game_over.setColor(Color::White);

    std::string score_to_string="To exit press Enter\nGAME OVER! Your Score: ";
    game_over.setPosition(300,250);

    int tmp; //Temporary int which help to end game when it is closed by X
    Event event;
    Gameview game(window,font);

    tmp=game.runGame();
    //If the game window is closed
    if(tmp==closing_window)
    {
        state=END;
    }
    //Else sort the score etc
    else
    {
        score_to_string+=std::to_string(tmp);
        game_over.setString(score_to_string);

            while(event.type!=sf::Event::Closed)
            {
                window.waitEvent(event);
                window.clear();
                window.draw(game_over);
                window.display();
                if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    break;
                }
            }


        score_board.push_back(tmp);


    }
    if(event.type==sf::Event::Closed)
    {
        state=END;
        sorting();
    }
    else
    {
       state=MENU;
       sorting();
    }

}


//Function which is responsible for sorting scores from the file
void Menu::sorting()
{

    std::cout<<"Ile razy sie wykonuje>";
    std::string tmp; //Temporary string to save data from the file


    ranking_directory.open("Settings and ranking\\ranking directory.txt",std::ios::in);//Reading the scores
    while(!ranking_directory.eof())
    {
        getline(ranking_directory,tmp);
        score_board.push_back(atoi(tmp.c_str()));
    }
    ranking_directory.close();

    for(int i=0;i<score_board.size();i++)
    {
        std::cout<<score_board[i]<<std::endl;
    }

    std::sort(score_board.begin(),score_board.end(),std::greater<>());
    auto last=std::unique(score_board.begin(),score_board.end());
    score_board.erase(last,score_board.end());


    if(score_board.size()>10) //If the number of scores is higher than 10 then erase it
    {
        score_board.erase(score_board.begin()+10,score_board.end());
    }

    ranking_directory.open("Settings and ranking\\ranking directory.txt",std::ios::out); //Saving sorted scores to file
    for(int i=0;i<score_board.size();i++)
    {
//        if(score_board[i]>0)
//        {
            ranking_directory<<score_board[i];
            ranking_directory<<std::endl;
        //}
    }
    ranking_directory.close();


}

//Function which show score ranking
void Menu::ranking()
{

    Event event;

    Vector2f mouse(Mouse::getPosition(window));
    Text scores[10];

    Text exit_tekst; //Settings for exit text
    exit_tekst.setFont(font);
    exit_tekst.setCharacterSize(40);
    exit_tekst.setString("EXIT");
    exit_tekst.setPosition(1280/2-exit_tekst.getGlobalBounds().width/2,600);


    std::string scores_brd[10];


    for(int i=0;i<10;i++) //It help to get scores in such type  1.Your score
    {
        scores_brd[i]+=std::to_string(i+1);
        scores_brd[i]+=".";
    }

    std::string line;
    int line_num=1;

    ranking_directory.open("Settings and ranking\\ranking directory.txt",std::ios::in); //Reading scores from file to string
    while(getline(ranking_directory,line))
    {
        switch (line_num)
        {
            case 1: scores_brd[0]+=line; break;
            case 2: scores_brd[1]+=line; break;
            case 3: scores_brd[2]+=line; break;
            case 4: scores_brd[3]+=line; break;
            case 5: scores_brd[4]+=line; break;
            case 6: scores_brd[5]+=line; break;
            case 7: scores_brd[6]+=line; break;
            case 8: scores_brd[7]+=line; break;
            case 9: scores_brd[8]+=line; break;
            case 10: scores_brd[9]+=line; break;
        }
        line_num++;
    }
    ranking_directory.close();

    for(int i=0;i<10;i++)
    {
        scores[i].setString(scores_brd[i]);
    }

    for(int i=0;i<10;i++)
    {
        scores[i].setFont(font);
        scores[i].setCharacterSize(20);
        scores[i].setPosition(1280/2-scores[i].getGlobalBounds().width/2,100+i*50);
        scores[i].setColor(Color::White);
    }

    while(window.pollEvent(event))
    {
        window.clear();

        if(exit_tekst.getGlobalBounds().contains(mouse))
        {
            exit_tekst.setColor(Color::Red);
        }
        else
        {
            exit_tekst.setColor(Color::White);
        }

        for(int i=0;i<10;i++)
        {
            window.draw(scores[i]);
        }

        window.draw(exit_tekst);
        window.display();




        if(exit_tekst.getGlobalBounds().contains(mouse)&&event.type==Event::MouseButtonReleased&&event.key.code==Mouse::Left)
        {
            state=MENU;
            break;
        }
        if(event.type==sf::Event::Closed)
        {
            state=END;
        }

    }

}
