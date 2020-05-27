#include "settings.hpp"

using namespace sf;

std::string str[]={"Audio On","Play with frames On","Bomb On","Exit"};

Settings::Settings(sf::RenderWindow &win, sf::Font &fon)
{
    window=&win;
    font1=&fon;
    std::string str[] = {"Audio On","Play with frames On","Bomb On"};
    for(int i=0;i<3;i++)
    {
        saved.push_back(str[i]);
    }
}






void Settings::settings()
{
    bool menu=false;
        int settings_modes=4;
            Text tekst[settings_modes];

            settings_directory.open("Settings and ranking\\settings directory.txt",std::ios::in);
            while(!settings_directory.eof())
            {
                getline(settings_directory,saved[0]);
                getline(settings_directory,saved[1]);
                getline(settings_directory,saved[2]);
            }
            settings_directory.close();

            for(int i=0;i<settings_modes;i++)
            {
                tekst[i].setFont(*font1);
                tekst[i].setCharacterSize(65);
                tekst[i].setString(str[i]);
                tekst[i].setPosition(1280/2-tekst[i].getGlobalBounds().width/2,250+i*120);
            }

                while(!menu)
                {
                    Vector2f mouse(Mouse::getPosition(*window));
                    Event event;

                    while(window->pollEvent(event))
                    {
                        if(event.type==Event::Closed||event.type==Event::KeyPressed&&event.key.code==Keyboard::Escape)
                        {
                            window->close();
                            menu=true;
                        }


                        else if(tekst[0].getGlobalBounds().contains(mouse)&&event.type==Event::MouseButtonReleased&&event.key.code==Mouse::Left)
                        {
                            if(str[0]=="Audio On")
                            {
                                tekst[0].setString("Audio Off");
                                str[0]="Audio Off";
                                saved[0]="Audio Off";
                            }
                            else
                            {
                                tekst[0].setString("Audio On");
                                str[0]="Audio On";
                                saved[0]="Audio On";
                            }

                        }

                        else if(tekst[1].getGlobalBounds().contains(mouse)&&event.type==Event::MouseButtonReleased&&event.key.code==Mouse::Left)
                        {
                            if(str[1]=="Play with frames On")
                            {
                                tekst[1].setString("Play with frames Off");
                                str[1]="Play with frames Off";
                                saved[1]="Play with frames Off";
                            }
                            else
                            {
                                tekst[1].setString("Play with frames On");
                                str[1]="Play with frames On";
                                saved[1]="Play with frames On";
                            }
                        }

                        else if(tekst[2].getGlobalBounds().contains(mouse)&&event.type==Event::MouseButtonReleased&&event.key.code==Mouse::Left)
                        {
                            if(str[2]=="Bomb On")
                            {
                                tekst[2].setString("Bomb Off");
                                str[2]="Bomb Off";
                                saved[2]="Bomb Off";
                            }
                            else
                            {
                                tekst[2].setString("Bomb On");
                                str[2]="Bomb On";
                                saved[2]="Bomb On";
                            }
                        }

                        else if(tekst[3].getGlobalBounds().contains(mouse)&&event.type==Event::MouseButtonReleased&&event.key.code==Mouse::Left)
                        {
                            menu=true;
                        }
                    }

                    for(int i=0;i<settings_modes;i++)
                    if(tekst[i].getGlobalBounds().contains(mouse))
                        tekst[i].setColor(Color::Cyan);
                    else tekst[i].setColor(Color::Black);

                    window->clear(Color::White);


                    settings_directory.open("Settings and ranking\\settings directory.txt",std::ios::out);
                    for(int i=0;i<saved.size();i++)
                    {

                        settings_directory<<str[i];
                        settings_directory<<std::endl;

                    }
                    settings_directory.close();



                    for(int i=0;i<settings_modes;i++)
                    window->draw(tekst[i]);

                    window->display();
                }
}

