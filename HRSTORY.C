#define HR_READ_STORY

#include <stdio.h>
#include "reader.h"

void read_story(unsigned char *story)
{int i,le=0,col=0;
 long k;
 unsigned char str[5],ch;
 for (i=0;i<340 && pointer<story_size;i++)
 {if (le>11) break;
  ch=fgetc(story_file);
  pointer++,col++;
  if (ch>127)
  {*(story+i)=ch;
   i++;
   ch=fgetc(story_file);
   pointer++;
   col++;
  }
  if (col>29) le++,col=0;
  if (ch=='\n' && SetType)
  {for (k=pointer;k<pointer+2 && k<story_size;k++) *(str+(k-pointer))=fgetc(story_file);
   *(str+(k-pointer))=0;
   fseek(story_file,pointer-k,SEEK_CUR);
   if (*str=='\n' || ((*str==32 || *str==161) && (*(str+1)==32 || *(str+1)==161)))
   {*(story+i)='\n';
    le++,col=0;
   }
   else
    i--;
   continue;
  }
  if (ch=='\n' && !SetType)
  {*(story+i)='\n';
   le++,col=0;
   continue;
  }
  *(story+i)=ch;
 }
 *(story+i)=0;
}

void bof_eof()
{if (page0==0)
  file_b=1;
 else
  file_b=0;
 if (feof(story_file) || pointer>=story_size || page0>=story_size || page1>=story_size)
  file_e=1;
 else
  file_e=0;
}
