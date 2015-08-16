#define HR_LABEL

#include <dir.h>
#include <bios.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "reader.h"

int verify(unsigned char *string,int record);
int label_input(unsigned char *string,int record);
int is_ok(int x,int y,char *string);
int find_label(int record,char ch);
int menu(void);
void read_label(int record);
void write_label(int record);
void edit(unsigned char *string);
void insert(void);
void append(void);
void ldelete(void);
void update(unsigned char *string);
void list(int start);
void cls(int x1,int y1,int x2,int y2);
void disp_bar(void);
void normal(void);
void inverse(void);
void exist(void);
void bar_mode(int mode);
void message(int mode);
void Load(void);
void delete_all(void);
void select(void);

struct story_label {
 long position;
 unsigned char info[66];
}label;

static int Record=0,Y=4,label_page=0;

void edit_label(void)
{int key,r;
 textbackground(BLACK);
 textcolor(LIGHTGRAY);
 clrscr();
 cprintf(" **********   LABEL   **********");
 win(1,2,80,23,BLACK,LIGHTGRAY);
 win(2,3,79,18,BLACK,LIGHTGRAY);
 win(2,19,79,22,BLACK,LIGHTGRAY);
 if (label_total<1)
 {gotoxy(3,4);
  cprintf("(NONE)");
 }
 else
 {list(label_page);
  read_label(Record);
  inverse();
 }
 message(1);
 while (1)
 {key=bioskey(0);
  if (key==F10)
  {if (menu()) break;
   message(1);
   continue;
  }
  if (key==UP && label_open)
  {if (Record<1) continue;
   normal();
   Record--,Y--;
   read_label(Record);
   if (Y<4)
   {Y=4,label_page--;
    movetext(4,4,70,16,4,5);
   }
   inverse();
   continue;
  }
  if (key==DOWN && label_open)
  {if (Record+1>=label_total) continue;
   normal();
   Record++,Y++;
   read_label(Record);
   if (Y>17)
   {Y=17;
    label_page++;
    movetext(4,5,70,17,4,4);
   }
   inverse();
   continue;
  }
  if (key==HOME && label_total>0)
  {if (Record<1) continue;
   cls(3,4,78,17);
   list(0);
   Record=0,Y=4;
   read_label(Record);
   inverse();
   continue;
  }
  if (key==END && label_total>0)
  {if (Record+1>=label_total) continue;
   cls(3,4,78,17);
   if (Y+label_total-Record<19)
   {Y+=label_total-Record-1;
    list(label_page);
   }
   else
   {list(label_total-14);
    Y=17;
   }
   Record=label_total-1;
   read_label(Record);
   inverse();
   continue;
  }
  if (key==PGUP && label_total>0)
  {if (Record<1) continue;
   cls(3,4,78,17);
   if (label_page<14)
   {list(0);
    Record=0,Y=4;
   }
   else
   {list(label_page-14);
    Record=label_page+Y-4;
   }
   read_label(Record);
   inverse();
   continue;
  }
  if (key==PGDN && label_total>0)
  {if (Record+1>=label_total) continue;
   cls(3,4,78,17);
   if (Y+label_total-Record<19)
   {Y+=label_total-Record-1;
    Record=label_total-1;
    list(label_page);
   }
   else
   {list(label_page+14);
    Record=label_page+Y-4;
    if (label_page+Y>label_total+3)
    {Y=label_total-label_page+3;
     Record=label_total-1;
    }
   }
   read_label(Record);
   inverse();
   continue;
  }
  if (key==ENTER && label_total>0)
  {select();
   break;
  }
  if (key==ESC)
  {gettext(1,1,80,25,Screen);
   textcolor(LIGHTGRAY);
   textbackground(BLACK);
   clrscr();
   pexit();
   puttext(1,1,80,25,Screen);
   continue;
  }
  if (key==F1) break;
  if (key==SPACE)
  {append();
   message(1);
   continue;
  }
  if (key==INSERT)
  {insert();
   message(1);
   continue;
  }
  if (key==DELETE && label_total>0 && temp_open)
  {ldelete();
   continue;
  }
  if (key==F2 && label_total>0)
  {edit(label.info);
   message(1);
   continue;
  }
  if (key==F3 && label_total>0)
  {update(label.info);
   message(1);
   continue;
  }
  if (key==F4 && label_find && label_open)
  {delete_all();
   message(1);
   continue;
  }
  if (key==F5)
  {Load();
   break;
  }
  if (label_total<2) continue;
  normal();
  r=find_label(Record,(char)key);
  Y+=r-Record;
  Record=r;
  if (Y<4)
  {Y=4;
   cls(3,4,78,17);
   list(Record);
  }
  if (Y>17)
  {Y=17;
   cls(3,4,78,17);
   list(Record-13);
  }
  read_label(Record);
  inverse();
 }
}

void list(int start)
{int i,end=start+13,y=4;
 struct story_label temp_label;
 if (end+1>label_total) end=label_total-1;
 label_page=start;
 fseek(label_file,start*70+60,SEEK_SET);
 for (i=start;;i++,y++)
 {fread(&temp_label,sizeof(temp_label),1,label_file);
  gotoxy(4,y);
  cprintf("%s",temp_label.info);
  if (i>=end) break;
 }
}

int verify(unsigned char *string,int record)
{register int i;
 for (i=0;i<label_total;i++)
 {if (i==record) continue;
  read_label(i);
  if (strcmp(string,label.info)==0) return 1;
 }
 return 0;
}

void bar_mode(int mode)
{switch (mode)
 {case NORMAL:
   textbackground(BLACK);
   textcolor(LIGHTGRAY);
  break;
  case INVERSE:
   textbackground(LIGHTGRAY);
   textcolor(BLACK);
 }
}

void read_label(int record)
{fseek(label_file,record*70+60,SEEK_SET);
 fread(&label,sizeof(label),1,label_file);
}

void write_label(int record)
{fseek(label_file,record*70+60,SEEK_SET);
 fwrite(&label,sizeof(label),1,label_file);
}

void disp_bar(void)
{register int i,len=75-strlen(label.info);
 cprintf(" %s",label.info);
 for (i=0;i<len;i++) putch(' ');
}

void inverse(void)
{bar_mode(INVERSE);
 gotoxy(3,Y);
 disp_bar();
}

void normal(void)
{bar_mode(NORMAL);
 gotoxy(3,Y);
 disp_bar();
}

void insert(void)
{register int i;
 unsigned char name[66];
 *name=0;
 bar_mode(NORMAL);
 cls(3,20,78,21);
 if (label_input(name,label_total)) return;
 for (i=label_total;i>Record;i--)
 {read_label(i-1);
  write_label(i);
 }
 label.position=page0;
 strcpy(label.info,name);
 write_label(Record);
 label_total++;
 read_label(Record);
 cls(3,4,78,17);
 list(Record-Y+4);
 inverse();
}

void append(void)
{unsigned char name[66];
 *name=0;
 bar_mode(NORMAL);
 cls(3,20,78,21);
 if (label_input(name,label_total)) return;
 label.position=page0;
 strcpy(label.info,name);
 write_label(label_total);
 label_total++;
 read_label(Record);
 cls(3,4,78,17);
 list(Record-Y+4);
 inverse();
}

void update(unsigned char *string)
{unsigned char name[66];
 strcpy(name,string);
 bar_mode(NORMAL);
 cls(3,20,78,21);
 if (label_input(name,Record)) return;
 label.position=page0;
 strcpy(label.info,name);
 write_label(Record);
 inverse();
}

void edit(unsigned char *string)
{unsigned char name[66];
 strcpy(name,string);
 bar_mode(NORMAL);
 cls(3,20,78,21);
 if (label_input(name,Record)) return;
 read_label(Record);
 strcpy(label.info,name);
 write_label(Record);
 inverse();
}

void ldelete(void)
{register int i;
 rewind(temp_file);
 for (i=0;i<label_total;i++)
 {if (i==Record) continue;
  read_label(i);
  fwrite(&label,sizeof(label),1,temp_file);
 }
 fclose(label_file);
 remove(label_name);
 if ((label_file=fopen(label_name,"wb+"))==NULL)
 {label_open=0;
  gotoxy(3,20);
  cprintf("Can't Delete!");
  gotoxy(3,21);
  cprintf("Press any key . . .");
  getch();
  return;
 }
 fwrite(header,60,1,label_file);
 label_total--;
 rewind(temp_file);
 for (i=0;i<label_total;i++)
 {fread(&label,sizeof(label),1,temp_file);
  write_label(i);
 }
 cls(3,4,78,17);
 if (label_total<1)
 {gotoxy(3,4);
  cprintf("(NONE)");
 }
 else
 {if (Record==label_total)
  {Record--,Y--;
   if (Y<4) Y=4;
  }
  list(Record-Y+4);
  read_label(Record);
  inverse();
 }
}

void exist(void)
{if (label_find==0)
 {if ((label_file=fopen(label_name,"wb+"))==NULL)
   label_open=0;
  else
  {label_open=1;
   label_total=0;
   label_find=1;
   fwrite(header,54,1,label_file);
   if ((temp_file=fopen(temp_name,"wb+"))==NULL)
    temp_open=0;
   else
    temp_open=1;
  }
 }
}

int label_input(unsigned char *string,int record)
{unsigned char name[66];
 exist();
 strcpy(name,string);
 if (label_open==1)
 {gotoxy(3,20);
  cprintf("Please enter the Label-name:\n");
  gotoxy(3,21);
  if (input(name,65,3,21,BLACK,LIGHTGRAY)) return 1;
 }
 else
 {gotoxy(3,20);
  cprintf("Error:Don't open the Label-File!   -----   %s\n",label_name);
  gotoxy(3,21);
  cprintf("Press any key . . .");
  getch();
  return 1;
 }
 if (verify(name,record))
 {cls(3,20,78,21);
  gotoxy(3,20);
  cprintf("Label Existed!\n");
  gotoxy(3,21);
  cprintf("Press any key . . .");
  getch();
  return 1;
 }
 strcpy(string,name);
 return 0;
}

int is_ok(int x,int y,char *string)
{char ch;
 gotoxy(x,y);
 cputs(string);
 do
 {ch=toupper(getch());
 }while (ch!='Y' && ch!='N');
 putch(ch);
 if (ch=='Y')
  return 1;
 else
  return 0;
}

void cls(int x1,int y1,int x2,int y2)
{bar_mode(NORMAL);
 window(x1,y1,x2,y2);
 clrscr();
 window(1,1,80,25);
}

int find_label(int record,char ch)
{register int i=record+1,j,r,k=0,find=0;
 if (i>=label_total) i=0,k=1;
 while (1)
 {for (j=i;j<label_total;j++)
  {read_label(j);
   if (ch==*label.info)
   {find=1,r=j;
    break;
   }
  }
  if (find)
   break;
  else
   if (k)
   {r=record;
    break;
   }
   else
   {k=1,i=0;
    continue;
   }
 }
 return r;
}

int menu(void)
{int key,x=3,y=20,p=0,r=0;
 char *str[8]={" CREATE "," INSERT "," DELETE "," CLEAR  "," EDIT   "," UPDATE "," LOAD   "," SELECT "};
 message(2);
 bar_mode(INVERSE);
 gotoxy(x,y);
 cputs(str[p]);
 while (1)
 {key=bioskey(0);
  if (key==UP)
  {bar_mode(NORMAL);
   gotoxy(x,y);
   cputs(str[p]);
   y--,p-=4;
   if (y<20) y=21,p+=8;
   bar_mode(INVERSE);
   gotoxy(x,y);
   cputs(str[p]);
  }
  if (key==DOWN)
  {bar_mode(NORMAL);
   gotoxy(x,y);
   cputs(str[p]);
   y++,p+=4;
   if (y>21) y=20,p-=8;
   bar_mode(INVERSE);
   gotoxy(x,y);
   cputs(str[p]);
  }
  if (key==LEFT)
  {bar_mode(NORMAL);
   gotoxy(x,y);
   cputs(str[p]);
   x-=19,p--;
   if (x<3)
   {x=60;
    if (y==20)
     p=3;
    else
     p=7;
   }
   bar_mode(INVERSE);
   gotoxy(x,y);
   cputs(str[p]);
  }
  if (key==RIGHT)
  {bar_mode(NORMAL);
   gotoxy(x,y);
   cputs(str[p]);
   x+=19,p++;
   if (x>60)
   {x=3;
    if (y==20)
     p=0;
    else
     p=4;
   }
   bar_mode(INVERSE);
   gotoxy(x,y);
   cputs(str[p]);
  }
  if (key==ENTER)
  {if (p==0)
   {append();
    message(2);
    bar_mode(INVERSE);
    gotoxy(x,y);
    cputs(str[p]);
   }
   if (p==1)
   {insert();
    message(2);
    bar_mode(INVERSE);
    gotoxy(x,y);
    cputs(str[p]);
   }
   if (p==2 && label_total>0 && temp_open) ldelete();
   if (p==3 && label_find && label_open)
   {delete_all();
    message(2);
    bar_mode(INVERSE);
    gotoxy(x,y);
    cputs(str[p]);
   }
   if (p==4 && label_total>0)
   {edit(label.info);
    message(2);
    bar_mode(INVERSE);
    gotoxy(x,y);
    cputs(str[p]);
   }
   if (p==5 && label_total>0)
   {update(label.info);
    message(2);
    bar_mode(INVERSE);
    gotoxy(x,y);
    cputs(str[p]);
   }
   if (p==6)
   {Load();
    r=1;
    break;
   }
   if (p==7 && label_total>0)
   {select();
    r=1;
    break;
   }
  }
  if (key==ESC)
  {r=0;
   break;
  }
 }
 return r;
}

void message(int mode)
{switch (mode)
 {case 1:
   cls(3,20,78,21);
   gotoxy(3,20);
   cputs(" F1-Return     F2-Edit          F3-Update       F4-Clear      F5-Load   ");
   gotoxy(3,21);
   cputs(" F10-Menu      Enter-Select     Space-Create    Ins-Insert    Del-Delete");
  break;
  case 2:
   cls(3,20,78,21);
   gotoxy(3,20);
   cputs(" CREATE             INSERT             DELETE             CLEAR");
   gotoxy(3,21);
   cputs(" EDIT               UPDATE             LOAD               SELECT");
 }
}

void Load(void)
{struct ffblk fb;
 fclose(story_file);
 if (label_open)
 {fseek(label_file,55L,SEEK_SET);
  fwrite(&page0,sizeof(page0),1,label_file);
  fclose(label_file);
 }
 if (temp_open)
 {fclose(temp_file);
  remove(temp_name);
 }
 label_open=0,label_find=0,temp_open=0;
 file_b=1,file_e=0;
 label_total=0;
 pointer=0,page0=0;
 Record=0,Y=4,label_page=0;
line2:
 if (load_file())
 {textcolor(LIGHTGRAY);
  textbackground(BLACK);
  clrscr();
  pexit();
  goto line2;
 }
 if ((story_file=fopen(story_name,"r"))==NULL) goto line2;
 findfirst(story_name,&fb,0);
 story_size=fb.ff_fsize;
 read_LabelFile();
 read_story(story);
 page1=pointer;
 bof_eof();
 bar_mode(NORMAL);
}

void delete_all(void)
{cls(3,20,78,21);
 gotoxy(3,20);
 cputs("The label-file will be deleted!");
 if (is_ok(3,21,"Are you sure? (Y/N) "))
 {fclose(label_file);
  remove(label_name);
  label_find=0,label_open=0,label_total=0,Record=0,Y=4;
  cls(3,4,78,17);
  gotoxy(3,4);
  cputs("(NONE)");
 }
}

void select(void)
{read_label(Record);
 page0=label.position,pointer=page0;
 fseek(story_file,page0,SEEK_SET);
 read_story(story);
 page1=pointer;
 bof_eof();
}

void win(int x1,int y1,int x2,int y2,int cor,int co)
{int i;
 window(x1,y1,x2,y2);
 highvideo();
 textbackground(cor);
 textcolor(co);
 clrscr();
 window(1,1,80,25);
 for (i=x1+1;i<=x2-1;i++)
 {gotoxy(i,y1);
  putch(0xc4);
  gotoxy(i,y2);
  putch(0xc4);
 }
 for (i=y1+1;i<=y2-1;i++)
 {gotoxy(x1,i);
  putch(0xb3);
  gotoxy(x2,i);
  putch(0xb3);
 }
 gotoxy(x1,y1);
 putch(0xda);
 gotoxy(x2,y1);
 putch(0xbf);
 gotoxy(x1,y2);
 putch(0xc0);
 gotoxy(x2,y2);
 putch(0xd9);
}
