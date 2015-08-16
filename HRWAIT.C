#define HR_WAIT

#include <stdio.h>
#include <dos.h>
#include <bios.h>
#include <math.h>
#include <conio.h>
#include <graphics.h>
#include "reader.h"

int pageup(FILE *fp);

void wait(void)
{int ch;
 while (1)
 {ClearKey();
  ch=bioskey(0);
  if (ch==PGUP && !file_b)
  {if (pageup(story_file))
   {rewind(story_file);
    file_b=1;
   }
   break;
  }
  if (ch==PGDN && !file_e) break;
  if (ch==HOME && !file_b)
  {file_b=1;
   rewind(story_file);
   break;
  }
  if (ch==END && !file_e)
  {fseek(story_file,0L,SEEK_END);
   if (pageup(story_file))
   {rewind(story_file);
    file_b=1;
   }
   file_e=1;
   break;
  }
  if (ch==ENTER && page0!=last_position && label_open)
  {fseek(story_file,last_position,SEEK_SET);
   break;
  }
  if (ch==F1)
  {restorecrtmode();
   CloseCur();
   edit_label();
   setgraphmode(2);
   setcolor(LIGHTGRAY);
   settextstyle(TRIPLEX_FONT,0,1);
   print(story,xx,yy);
   continue;
  }
  if (ch==F2)
  {restorecrtmode();
   CloseCur();
   Load();
   rewind(story_file);
   setgraphmode(2);
   setcolor(LIGHTGRAY);
   settextstyle(TRIPLEX_FONT,0,1);
   break;
  }
  if (ch==SPACE)
  {SetType=abs(SetType-1);
   fseek(story_file,page0,SEEK_SET);
   break;
  }
  if (ch==ESC)
  {restorecrtmode();
   CloseCur();
   pexit();
   setgraphmode(2);
   setcolor(LIGHTGRAY);
   settextstyle(TRIPLEX_FONT,0,1);
   print(story,xx,yy);
   continue;
  }
 }
 pointer=ftell(story_file);
}

void CloseCur(void)
{_AH=1;
 _CH=0x20;
 geninterrupt(0x10);
}

void OpenCur(void)
{_AH=1;
 _CH=12;
 _CL=13;
 geninterrupt(0x10);
}

int pageup(FILE *fp)
{long i;
 unsigned char ch,ch1;
 long size;
 size=ftell(fp);
 for (i=size-1;i>size-611;i--)
 {if (fseek(fp,i,SEEK_SET)) return 1;
  ch=fgetc(fp);
  if (fseek(fp,i,SEEK_SET)) return 1;
  if (ch>127)
  {if (fseek(fp,-1L,SEEK_CUR)) return 1;
   ch1=fgetc(fp);
   if (ch1>127)
   {i--;
    if (fseek(fp,i,SEEK_SET)) return 1;
   }
  }
 }
 return 0;
}

void pexit(void)
{int key,x=34,p=0;
 char *s[2]={" Yes "," No "};
 win(30,8,51,15,BLACK,LIGHTGRAY);
 gotoxy(36,8);
 textcolor(BLACK);
 textbackground(LIGHTGRAY);
 cprintf("   EXIT   ");
 textcolor(LIGHTGRAY);
 textbackground(BLACK);
 gotoxy(34,10);
 cprintf("Are you sure?");
 gotoxy(35,13);
 cprintf("Yes      No");
 gotoxy(x,13);
 textcolor(BLACK);
 textbackground(LIGHTGRAY);
 cputs(s[p]);
 while (1)
 {key=bioskey(0);
  if (key==ESC) break;
  if ((char)key=='y' || (char)key=='Y') quit();
  if ((char)key=='n' || (char)key=='N') break;
  if (key==LEFT)
  {gotoxy(x,13);
   textcolor(LIGHTGRAY);
   textbackground(BLACK);
   cputs(s[p]);
   x-=9,p--;
   if (p<0) x=43,p=1;
   gotoxy(x,13);
   textcolor(BLACK);
   textbackground(LIGHTGRAY);
   cputs(s[p]);
   continue;
  }
  if (key==RIGHT)
  {gotoxy(x,13);
   textcolor(LIGHTGRAY);
   textbackground(BLACK);
   cputs(s[p]);
   x+=9,p++;
   if (p>1) x=34,p=0;
   gotoxy(x,13);
   textcolor(BLACK);
   textbackground(LIGHTGRAY);
   cputs(s[p]);
   continue;
  }
  if (key==ENTER)
  {if (p==0) quit();
   if (p==1) break;
  }
 }
}

void ClearKey(void)
{_AH=0x0c;
 geninterrupt(0x21);
}

void ClrScr(void)
{textbackground(BLACK);
 textcolor(LIGHTGRAY);
 clrscr();
}
