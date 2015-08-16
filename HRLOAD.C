#define HR_LOAD

#include <dir.h>
#include <alloc.h>
#include <string.h>
#include <conio.h>
#include <bios.h>
#include <ctype.h>
#include "reader.h"

static unsigned char *mask;
static unsigned char fullname[80],dir[MAXPATH],FileName[13]={"*.TXT"};
static int file_total,total_f,total_d,first;

int file_select(void);
int find_name(int p,char ch);
void file_list(void);
void sort(char *address,int begin,int end);
void selected(int x,int y,int p);
void noselect(int x,int y,int p);
void disp_line(int x,int y,int line);
void clrwin(void);
void dispwin(int p);
void make_name(unsigned char *string,unsigned char *name);
void RetPath(void);
void GoPath(unsigned char *string);
void dline(void);

int load_file(void)
{int r;
 file_total=0,total_f=0,total_d=0,first=1;
 make_name(fullname,FileName);
 make_name(dir,"*.*");
 textbackground(BLACK);
 textcolor(LIGHTGRAY);
 clrscr();
 gotoxy(15,1);
 cputs("*********     The HyperReader 2000     *********");
 gotoxy(5,24);
 cprintf("Version  %s",Version);
 gotoxy(62,24);
 cprintf("%s",Update);
 win(3,3,75,23,LIGHTGRAY,BLACK);
 win(4,6,74,20,LIGHTGRAY,BLACK);
 gotoxy(5,4);
 cputs("Directory:");
 gotoxy(5,5);
 cprintf("File Name: %s",FileName);
 gotoxy(5,21);
 cprintf("File Total: %d",total_f);
 gotoxy(5,22);
 cprintf("Directory Total: %d",total_d);
 gotoxy(39,21);
 cputs("Change File Name  ---  <F4>");
 gotoxy(40,22);
 cputs("Change Directory  ---  <F2>");
 file_list();
 r=file_select();
 free(mask);
 textbackground(BLACK);
 textcolor(LIGHTGRAY);
 return r;
}

void file_list(void)
{struct ffblk fb;
 int done,i=0,j;
 unsigned char name[15];
 file_total=0,total_f=0,total_d=0;
 make_name(dir,"*.*");
 done=findfirst(fullname,&fb,0);
 while (!done)
 {file_total++,total_f++;
  done=findnext(&fb);
 }
 done=findfirst(dir,&fb,0x10);
 while (!done)
 {if (((fb.ff_attrib&0xf0)==16) && strcmp(fb.ff_name,".")) file_total++,total_d++;
  done=findnext(&fb);
 }
 if (file_total==0)
 {gotoxy(16,4);
  cputs(Path);
  clrwin();
  gotoxy(6,7);
  cputs("Can't find file!");
  gotoxy(17,21);
  cputs("0     ");
  gotoxy(22,22);
  cputs("0     ");
  return;
 }
 if (first)
 {first=0;
  mask=(unsigned char *)malloc(file_total*15);
 }
 else
 {free(mask);
  mask=(unsigned char *)malloc(file_total*15);
 }
 done=findfirst(fullname,&fb,0);
 while (!done)
 {strcpy(mask+i*15,fb.ff_name);
  i++;
  done=findnext(&fb);
 }
 sort(mask,0,i);
 j=i;
 done=findfirst(dir,&fb,0x10);
 while (!done)
 {if (((fb.ff_attrib&0xf0)==16) && strcmp(fb.ff_name,"."))
  {*name='[';
   strcpy(name+1,fb.ff_name);
   strcat(name,"]");
   memcpy(mask+i*15,name,15);
   i++;
  }
  done=findnext(&fb);
 }
 sort(mask,j,file_total);
 gotoxy(16,4);
 textbackground(LIGHTGRAY);
 textcolor(BLACK);
 dline();
 gotoxy(16,4);
 cputs(Path);
 clrwin();
 dispwin(0);
 gotoxy(17,21);
 cprintf("%d     ",total_f);
 gotoxy(22,22);
 cprintf("%d     ",total_d);
}

void sort(char *address,int begin,int end)
{register int i,j;
 unsigned char temp[15];
 for (i=begin;i<end-1;i++)
  for (j=i+1;j<end;j++)
   if (strcmp(address+i*15,address+j*15)>0)
   {strcpy(temp,address+i*15);
    memcpy(address+i*15,address+j*15,15);
    memcpy(address+j*15,temp,15);
   }
}

void selected(int x,int y,int p)
{register int i,j=15-strlen(mask+p*15);
 if (file_total<1) return;
 textbackground(BLACK);
 textcolor(WHITE);
 gotoxy(x-1,y);
 cprintf(" %s",mask+p*15);
 for (i=0;i<j;i++) putch(' ');
}

void noselect(int x,int y,int p)
{register int i,j=15-strlen(mask+p*15);
 textbackground(LIGHTGRAY);
 textcolor(BLACK);
 gotoxy(x-1,y);
 cprintf(" %s",mask+p*15);
 for (i=0;i<j;i++) putch(' ');
}

void disp_line(int x,int y,int line)
{register int i,j,p=line*4;
 for (i=p;i<p+4 && i<file_total;i++) noselect(x+(i-p)*17,y,i);
 for (j=i;j<p+4;j++) cputs("                 ");
}

void clrwin(void)
{textbackground(LIGHTGRAY);
 textcolor(BLACK);
 window(5,7,73,19);
 clrscr();
 window(1,1,80,25);
}

void dispwin(int p)
{register int x,y,i=p;
 for (y=7;y<20;y++)
  for (x=6;x<58;x+=17)
  {if (i>file_total-1) return;
   noselect(x,y,i);
   i++;
  }
}

int file_select(void)
{int x=6,y=7,p=0,line=0,msg;
 unsigned char temp[15];
 if (file_total>0) selected(x,y,p);
 while (1)
 {msg=bioskey(0);
  if (msg==ESC) return 1;
  if (msg==LEFT && file_total)
  {if (p<1) continue;
   noselect(x,y,p);
   p--,x-=17;
   if (x<6) x=57,y--,line--;
   if (y<7)
   {y=7;
    movetext(5,7,73,18,5,8);
    disp_line(6,y,line);
   }
   selected(x,y,p);
   continue;
  }
  if (msg==RIGHT && file_total)
  {if (p+2>file_total) continue;
   noselect(x,y,p);
   p++,x+=17;
   if (x>57) x=6,y++,line++;
   if (y>19)
   {y=19;
    movetext(5,8,73,19,5,7);
    disp_line(6,y,line);
   }
   selected(x,y,p);
   continue;
  }
  if (msg==UP && file_total)
  {if (p<4) continue;
   noselect(x,y,p);
   p-=4,y--,line--;
   if (y<7)
   {y=7;
    movetext(5,7,73,18,5,8);
    disp_line(6,y,line);
   }
   selected(x,y,p);
   continue;
  }
  if (msg==DOWN && file_total)
  {if (p+5>file_total)
   {if (line*4+5<=file_total && y==19)
    {noselect(x,y,p);
     movetext(5,8,73,19,5,7);
     disp_line(6,y,line+1);
     y--;
     selected(x,y,p);
    }
    continue;
   }
   noselect(x,y,p);
   p+=4,y++,line++;
   if (y>19)
   {y=19;
    movetext(5,8,73,19,5,7);
    disp_line(6,y,line);
   }
   selected(x,y,p);
   continue;
  }
  if (msg==PGUP && file_total)
  {if (line<1) continue;
   if (line-y<6)
   {if (y-line<7)
    {clrwin();
     dispwin(0);
    }
    else
     noselect(x,y,p);
    line=0,y=7,p=(x-6)/17;
   }
   else
   {line-=13;
    p=line*4+((x-6)/17);
    clrwin();
    dispwin((line-y+7)*4);
   }
   selected(x,y,p);
   continue;
  }
  if (msg==PGDN && file_total)
  {if (y+(file_total-1)/4-line<20)
   {noselect(x,y,p);
    p=(file_total-1)/4*4+((x-6)/17);
    if (p>file_total-1) p-=4;
    y+=p/4-line;
    line=p/4;
   }
   else
   {clrwin();
    line+=13;
    p=line*4+((x-6)/17);
    if (line>=(file_total-1)/4)
    {y-=line-(file_total-1)/4;
     line=(file_total-1)/4;
     p=line*4+((x-6)/17);
     if (p>file_total-1)
     {p-=4,line--,y--;
      if (y<7) y=7;
     }
    }
    dispwin((line-y+7)*4);
   }
   selected(x,y,p);
   continue;
  }
  if (msg==HOME && file_total)
  {if (p<1) continue;
   if (y-line<7)
   {clrwin();
    dispwin(0);
   }
   else
    noselect(x,y,p);
   p=0,line=0,y=7,x=6;
   selected(x,y,p);
   continue;
  }
  if (msg==END && file_total)
  {if (p==file_total-1) continue;
   if (y+(file_total-1)/4-line<20)
   {noselect(x,y,p);
    p=file_total-1;
    y+=p/4-line;
    line=p/4;
    x=6+(p-line*4)*17;
   }
   else
   {y=19;
    p=file_total-1;
    line=p/4;
    x=6+(p-line*4)*17;
    clrwin();
    dispwin(line*4-48);
   }
   selected(x,y,p);
   continue;
  }
  if (msg==ENTER && file_total)
  {strcpy(temp,mask+p*15);
   if (*temp=='[')
   {x=6,y=7,p=0,line=0;
    if (*(temp+1)=='.')
     RetPath();
    else
     GoPath(temp);
    make_name(fullname,FileName);
    file_list();
    selected(x,y,p);
   }
   else
   {make_name(story_name,temp);
    return 0;
   }
   continue;
  }
  if (msg==F2)
  {unsigned char tmp[MAXPATH];
   strcpy(tmp,Path);
   if (input(tmp,59,16,4,LIGHTGRAY,BLACK))
   {gotoxy(16,4);
    dline();
    gotoxy(16,4);
    cputs(Path);
    continue;
   }
   strcpy(Path,tmp);
   strupr(Path);
   make_name(fullname,FileName);
   x=6,y=7,p=0,line=0;
   file_list();
   selected(x,y,p);
   continue;
  }
  if (msg==F4)
  {unsigned char tmp[13];
   strcpy(tmp,FileName);
   if (input(tmp,12,16,5,LIGHTGRAY,BLACK))
   {gotoxy(16,5);
    cputs("             ");
    gotoxy(16,5);
    cputs(FileName);
    continue;
   }
   strcpy(FileName,tmp);
   strupr(FileName);
   gotoxy(16,5);
   cputs("             ");
   gotoxy(16,5);
   cputs(FileName);
   make_name(fullname,FileName);
   x=6,y=7,p=0,line=0;
   file_list();
   selected(x,y,p);
   continue;
  }
  if (file_total<2) continue;
  noselect(x,y,p);
  p=find_name(p,toupper((char)msg));
  y+=p/4-line;
  line=p/4;
  x=p*17-line*68+6;
  if (y>19)
  {y=19;
   clrwin();
   dispwin(line*4-48);
  }
  if (y<7)
  {y=7;
   clrwin();
   dispwin(line*4);
  }
  selected(x,y,p);
 }
}

void make_name(unsigned char *string,unsigned char *name)
{strcpy(string,Path);
 if (*(Path+(strlen(Path)-1))!='\\') strcat(string,"\\");
 strcat(string,name);
}

void RetPath(void)
{register int i,len=strlen(Path);
 for (i=len-1;i>0;i--)
  if (*(Path+i)=='\\')
  {*(Path+i)=0;
   break;
  }
 if (strlen(Path)<3)
 {*(Path+2)='\\';
  *(Path+3)=0;
 }
}

void GoPath(unsigned char *string)
{make_name(Path,string+1);
 *(Path+(strlen(Path)-1))=0;
}

void dline(void)
{register int i;
 for (i=0;i<59;i++) putch(' ');
}

int find_name(int p,char ch)
{register int i=p+1,j,r,k=0,find=0;
 if (i>=file_total) i=0,k=1;
 while (1)
 {for (j=i;j<file_total;j++)
   if (ch==*(mask+j*15))
   {find=1,r=j;
    break;
   }
  if (find)
   break;
  else
   if (k)
   {r=p;
    break;
   }
   else
   {k=1,i=0;
    continue;
   }
 }
 return r;
}
