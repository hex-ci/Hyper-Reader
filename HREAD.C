#define HR_READ

#include <stdio.h>
#include <alloc.h>
#include <stdlib.h>
#include <string.h>
#include <dir.h>
#include <conio.h>
#include "reader.h"

void split(char *name);

FILE *Hzk16;

void alloc_mem(void)
{printf("Reading the Chinese-Library . . .   ");
 if ((Memory=(char huge *)farmalloc(267616L))==NULL)
 {printf("\nError:Not enough memory!\n");
  printf("Please exit some TSR!\n");
  OpenCur();
  exit(1);
 }
}

void read_HZK(void)
{unsigned char *path;
 if ((Hzk16=fopen(HZK,"rb"))==NULL)
 {GetPath(HZK,CMD);
  strcat(HZK,DEFAULT_HZK);
  if ((Hzk16=fopen(HZK,"rb"))==NULL)
  {path=searchpath(DEFAULT_HZK);
   if (path==NULL)
   {printf("Error!\n Can't open the Chinese-Library!\n");
    OpenCur();
    exit(1);
   }
   else
    Hzk16=fopen(path,"rb");
  }
 }
 fread((char far *)Memory,8363L,32L,Hzk16);
 fclose(Hzk16);
 printf("OK!\n");
}

void read_LabelFile(void)
{struct ffblk fb;
 char t[MAXFILE];
 split(t);
 strcpy(label_name,LABEL_PATH);
 strcat(label_name,t);
 strcat(label_name,LABEL_EXT);
 strcpy(temp_name,TEMP_PATH);
 strcat(temp_name,TEMP_FILE);
 if (!findfirst(label_name,&fb,0))
 {label_find=1;
  if ((label_file=fopen(label_name,"rb+"))==NULL)
   label_open=0;
  else
  {label_open=1;
   label_total=(fb.ff_fsize-60)/70;
   fseek(label_file,55L,SEEK_SET);
   fread(&last_position,sizeof(last_position),1,label_file);
   if ((temp_file=fopen(temp_name,"wb+"))==NULL)
    temp_open=0;
   else
    temp_open=1;
  }
 }
 else
  label_find=0;
}

void read_file(void)
{struct ffblk fb;
 if (History)
  strcpy(Path,HISTORY);
 else
  getcwd(Path,MAXPATH);
line1:
 if (ARGC>1)
  strcpy(story_name,ARGV);
 else
  if (load_file())
  {textcolor(LIGHTGRAY);
   textbackground(BLACK);
   clrscr();
   pexit();
   goto line1;
  }
 if ((story_file=fopen(story_name,"r"))==NULL)
 {ARGC=1;
  goto line1;
 }
 findfirst(story_name,&fb,0);
 story_size=fb.ff_fsize;
}

void split(char *name)
{char drive[MAXDRIVE],dir[MAXDIR],ext[MAXEXT];
 fnsplit(story_name,drive,dir,name,ext);
}
