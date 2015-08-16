#define HR_GRAPHICS

#include <alloc.h>
#include <graphics.h>
#include "reader.h"

extern char huge *Memory;
static char huge *Buffer;

void graph_init()
{int gd=DETECT,gm=2;
 registerfarbgidriver(EGAVGA_driver_far);
 registerfarbgifont(triplex_font_far);
 registerfarbgifont(small_font_far);
 registerfarbgifont(sansserif_font_far);
 registerfarbgifont(gothic_font_far);
 initgraph(&gd,&gm,"");
 cleardevice();
 setcolor(LIGHTGRAY);
 setbkcolor(BLACK);
 settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
}

void print(unsigned char *String,int x,int y)
{register i,j;
 int xt,yt,k1,k2;
 long Zcode,Bcode;
 unsigned char te[2];
 k1=(float)page0/(float)story_size*438+10;
 k2=(float)page1/(float)story_size*438+10;
 setbkcolor(BLUE);
 graph_window(615,9,625,439);
 if (SetType)
  setfillstyle(1,WHITE);
 else
  setfillstyle(11,WHITE);
 if (k2>438)
 {k1=438-k2+k1;
  k2=438;
 }
 if (k1<10) k1=10;
 bar(616,k1,624,k2);
 line(20,445,608,445);
 small_display("F1=标签    F2=打开文件    PgUp=上翻页    PgDn=下翻页    空格=智能分段",30,450);
 for (;*String;String++)
 {if (x>562)
  {y+=YWID+32;
   x=X_S;
  }
  if (*String=='\n')
  {y+=YWID+32;
   x=X_S;
   continue;
  }
  if ((*String&0x80) && (*(String+1)&0x80))
  {Zcode=(*String-161)&0x7f;
   Bcode=(*(String+1)-161)&0x7f;
   Buffer=Memory+((Zcode*94+Bcode)<<5);
   for (i=0;i<32;i++)
    for (j=0;j<8;j++)
     if ((*(Buffer+i)>>(7-j))&0x01)
     {xt=x+i%2*16+j*2,yt=y+i/2*2;
      line(xt,yt,xt+1,yt);
      line(xt,yt+1,xt+1,yt+1);
     }
   x+=XWID+32;
   String++;
   continue;
  }
  if (*String>=' ' && *String<='~')
  {*te=*String;
   *(te+1)=0;
   outtextxy(x,y+2,te);
   x+=(XWID/2)+16;
  }
 }
 xx=X_S,yy=Y_S;
}

void graph_window(int x1,int y1,int x2,int y2)
{moveto(x1,y1);
 lineto(x2,y1);
 lineto(x2,y2);
 lineto(x1,y2);
 lineto(x1,y1);
}

void clear()
{cleardevice();
}

void set_graph()
{setgraphmode(2);
 setcolor(LIGHTGRAY);
 settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
}

void small_display(unsigned char *String,int x,int y)
{register i,j;
 int xt,yt,k1,k2;
 long Zcode,Bcode;
 unsigned char te[2];
 setcolor(LIGHTGRAY);
 settextstyle(SMALL_FONT,HORIZ_DIR,5);
 for (;*String;String++)
 {if ((*String&0x80) && (*(String+1)&0x80))
  {Zcode=(*String-161)&0x7f;
   Bcode=(*(String+1)-161)&0x7f;
   Buffer=Memory+((Zcode*94+Bcode)<<5);
   for (i=0;i<32;i++)
    for (j=0;j<8;j++)
     if ((*(Buffer+i)>>(7-j))&0x01)
     {xt=x+i%2*8+j,yt=y+i/2;
      putpixel(xt,yt,LIGHTGRAY);
     }
   x+=S_XWID+16;
   String++;
   continue;
  }
  if (*String>=' ' && *String<='~')
  {*te=*String;
   *(te+1)=0;
   outtextxy(x,y+2,te);
   x+=(S_XWID/2)+8;
  }
 }
 setcolor(LIGHTGRAY);
 settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
}
