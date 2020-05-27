#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int N=30,M=20;
int size=16;
int w = size*N;
int h = size*M;

int dir,num=4;

struct make
{ int x,y;}  s[100];

struct Fruit
{ int x,y;} f;

void Tick()
 {
    for (int i=num;i>0;--i)
     {s[i].x=s[i-1].x; s[i].y=s[i-1].y;}

    if (dir==0) s[0].y+=1;
    if (dir==1) s[0].x-=1;
    if (dir==2) s[0].x+=1;
    if (dir==3) s[0].y-=1;

    if ((s[0].x==f.x) && (s[0].y==f.y))
     {num++; f.x=rand()%N; f.y=rand()%M;}

    if (s[0].x>N) s[0].x=0;  if (s[0].x<0) s[0].x=N;
    if (s[0].y>M) s[0].y=0;  if (s[0].y<0) s[0].y=M;

    for (int i=1;i<num;i++)
     if (s[0].x==s[i].x && s[0].y==s[i].y)  num=i;
 }

