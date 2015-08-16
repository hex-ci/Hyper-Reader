/*

   The Hyper-Reader   Ver 4.10
     Produced by Zhao Chang
   Compile Date:   2000-12-17
      Compile by TC++ 3.0

*/

#define HR_MAIN

#include <stdio.h>
#include "reader.h"

void main(int argc,char *argv[])
{ARGC=argc;
 CMD=argv[0];
 if (ARGC>1)
  ARGV=argv[1];
 else
  ARGV=NULL;
 HyperReader_init();
 set_graph();
 while (1)
 {page0=ftell(story_file);
  read_story(story);
  page1=ftell(story_file);
  print(story,xx,yy);
  bof_eof();
  wait();
  clear();
 }
}

void HyperReader_init(void)
{CloseCur();
 ClrScr();
 puts("\nWelcome to the HyperReader 2000");
 puts("=========================================");
 read_ini();
 alloc_mem();
 read_HZK();
 graph_init();
 image();
 CloseCur();
 read_file();
 read_LabelFile();
}
