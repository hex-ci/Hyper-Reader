#define HR_INPUT

#include <dos.h>
#include <bios.h>
#include <conio.h>
#include <string.h>
#include "reader.h"

void middle(unsigned char *string,int m);
void CurSize(int begin,int end);

int input(unsigned char *string,int lenth,int x,int y,int bco,int fco)
{int msg,ins=1,i=strlen(string),len=strlen(string),j,time=1;
 unsigned char ch;
 gotoxy(x,y);
 textbackground(fco);
 textcolor(bco);
 cputs(string);
 OpenCur();
 CurSize(11,12);
 while (1)
 {gotoxy(i+x,y);
  msg=bioskey(0);
  ch=(char)msg;
  if (time)
  {time=0;
   gotoxy(x,y);
   textbackground(bco);
   textcolor(fco);
   if (ch>=32 && ch<=255)
   {*string=0;
    len=0,i=0;
    for (j=0;j<lenth;j++) putch(' ');
    gotoxy(x,y);
   }
   else
    cputs(string);
  }
  if (msg==ESC)
  {len=0;
   break;
  }
  if (msg==ENTER)
  {*(string+len)=0;
   break;
  }
  if (msg==INSERT)
  {ins=!ins;
   if (ins)
    CurSize(11,12);
   else
    CurSize(0,12);
   continue;
  }
  if (msg==LEFT && i>0)
  {i--;
   continue;
  }
  if (msg==RIGHT && i<len)
  {i++;
   continue;
  }
  if (msg==HOME && i>0)
  {i=0;
   continue;
  }
  if (msg==END && i<len)
  {i=len;
   continue;
  }
  if (msg==BACKSPACE && i>0)
  {for (j=--i;j<len;j++) *(string+j)=*(string+j+1);
   len--;
   gotoxy(i+x,y);
   middle(string,i);
   putch(' ');
   continue;
  }
  if (msg==CTRL_BACKSPACE && i>0)
  {for (j=i;j<=len;j++) *(string+j-i)=*(string+j);
   len-=i;
   i=0;
   gotoxy(x,y);
   for (j=0;j<lenth;j++) putch(' ');
   gotoxy(x,y);
   middle(string,0);
   continue;
  }
  if (msg==CTRL_FXG && i<len)
  {*(string+i)=0;
   len=i;
   for (j=i;j<lenth+x;j++) putch(' ');
   continue;
  }
  if (msg==CTRL_Y && len>0)
  {*string=0;
   len=0,i=0;
   gotoxy(x,y);
   for (j=0;j<lenth;j++) putch(' ');
   continue;
  }
  if (msg==DELETE && i<len)
  {for (j=i;j<len;j++) *(string+j)=*(string+j+1);
   len--;
   gotoxy(i+x,y);
   middle(string,i);
   putch(' ');
   continue;
  }
  if (i<lenth && ch>=32 && ch<=255)
  {if (ins && len<lenth)
   {for (j=++len;j>i;j--) *(string+j)=*(string+j-1);
    *(string+(i++))=ch;
    putch(ch);
    middle(string,i);
    continue;
   }
   if (!ins)
   {*(string+(i++))=ch;
    if (i>len) *(string+(len=i))=0;
    putch(ch);
   }
  }
 }
 CurSize(11,12);
 CloseCur();
 textbackground(bco);
 textcolor(fco);
 gotoxy(x,y);
 cputs(string);
 if (len==0)
  return 1;
 else
  return 0;
}

void middle(unsigned char *string,int m)
{int i,j=strlen(string);
 for (i=m;i<j;i++) putch(*(string+i));
}

void CurSize(int begin,int end)
{_AH=1;
 _CH=begin;
 _CL=end;
 geninterrupt(0x10);
}
