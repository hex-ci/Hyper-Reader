#define HR_IMAGE

#include <math.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include "reader.h"

void Delay(clock_t t);
void ChangeColor(void);
void book(void);
void people(void);
void delaykey(int t);

char *Title[12]={"Hyper","R","e","a","d","e","r","2000",
		 "Produced by Zhao Chang.",
		 "Copyright (C)  2000",
		 "ALL RIGHTS RESERVED.",
		 "Press any key . . ."};
int Swap=0;

void image()
{int i;
 randomize();
 settextstyle(1,HORIZ_DIR,9);
 for (i=-250;i<10;i+=5)
 {setcolor(BLACK);
  outtextxy(i-5,0,*Title);// "Hyper"
  setcolor(LIGHTBLUE);
  outtextxy(i,0,*Title);// "Hyper"
  Delay(1);
 }
 Delay(300);
 setcolor(LIGHTRED);
 settextstyle(3,HORIZ_DIR,16);
 for (i=1;i<7;i++)
 {outtextxy(210+i*60,60,*(Title+i));// "Reader"
  Delay(400);
 }
 Delay(100);
 for (i=1;i<7;i++)
 {settextstyle(4,0,i);
  setcolor(LIGHTCYAN);
  outtextxy(450,190,*(Title+7));// "2000"
  Delay(300);
  setcolor(BLACK);
  settextstyle(4,HORIZ_DIR,i);
  outtextxy(450,190,*(Title+7));// "2000"
 }
 setcolor(LIGHTCYAN);
 settextstyle(4,HORIZ_DIR,i);
 outtextxy(450,190,*(Title+7));// "2000"
 Delay(400);
 setcolor(BLUE);
 line(10,140,250,140);
 line(250,140,250,200);
 line(250,200,400,200);
 line(400,200,400,280);
 line(400,280,600,280);
 Delay(800);
 setcolor(LIGHTGREEN);
 settextstyle(2,0,7);
 outtextxy(20,200,*(Title+8));// "Produced by Zhao Chang."
 Delay(500);
 outtextxy(40,225,*(Title+9));// "Copyright (C)  2000"
 Delay(500);
 outtextxy(37,250,*(Title+10));// "ALL RIGHTS RESERVED."
 Delay(500);
 setcolor(LIGHTMAGENTA);
 settextstyle(1,0,2);
 outtextxy(340,350,*(Title+11));// "Press any key . . ."
 setcolor(WHITE);
 settextstyle(2,0,5);
 outtextxy(142,450,"Version");
 outtextxy(205,450,Version);
 outtextxy(377,450,"Update:");
 outtextxy(435,450,Update);
 people();
 book();
 Delay(2000);
 ClearKey();
 while (!kbhit())
 {ChangeColor();
  book();
  people();
  delaykey(30);
 }
 getch();
 restorecrtmode();
}

void ChangeColor()
{int t;
 settextstyle(1,HORIZ_DIR,9);
 setcolor(random(7)+9);
 outtextxy(5,0,"Hyper");

 settextstyle(3,HORIZ_DIR,16);
 setcolor(random(7)+9);
 for (t=1;t<7;t++) outtextxy(210+t*60,60,*(Title+t));// "Reader"

 settextstyle(4,HORIZ_DIR,7);
 setcolor(random(7)+9);
 outtextxy(450,190,"2000");
}

void book()
{setcolor(random(7)+9);
 arc(110,360,50,130,50);
 arc(177,360,50,130,50);
 line(77,323,77,411);
 line(80,321,80,408);
 line(143,323,143,411);
 line(207,321,207,408);
 line(210,323,210,411);
 arc(110,448,50,125,50);
 arc(177,448,55,130,50);
 arc(110,456,52,125,55);
 arc(177,456,54,126,55);
}

void people()
{settextstyle(1,0,5);
 switch (Swap)
 {case 0:
   setcolor(BLACK);
   outtextxy(453,30,"-");
   setcolor(random(7)+9);
   outtextxy(440,20,"^^");
   outtextxy(454,30,"o");
  break;
  case 1:
   setcolor(BLACK);
   outtextxy(454,30,"o");
   setcolor(random(7)+9);
   outtextxy(440,20,"^^");
   outtextxy(453,30,"-");
 }
 Swap=abs(Swap-1);
}

void delaykey(int t)
{int i;
 for (i=0;i<t;i++)
 {if (kbhit()) break;
  Delay(1);
 }
}

void Delay(clock_t t)
{clock_t old=clock();
 while ((clock()-old)/CLK_TCK*1000<t);
}
