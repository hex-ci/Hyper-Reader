#define HR_QUIT

#include <graphics.h>
#include <alloc.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "reader.h"

void quit(void)
{farfree((char far *)Memory);
 if (temp_open)
 {fclose(temp_file);
  remove(temp_name);
 }
 WriteINI();
 ClearKey();
 closegraph();
 window(1,1,80,25);
 textbackground(BLACK);
 textcolor(LIGHTGRAY);
 clrscr();
 OpenCur();
 exit(0);
}
