#define HR_INI

#include <dir.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "reader.h"

void ReadINI(void);
void ReadText(char *string);
void GetPath(unsigned char *path,unsigned char *filename);
void zl(char *path);
int pdini(unsigned char *string,int len,unsigned char *str);

FILE *ini_file;

void read_ini(void)
{char name[60],*path;
 printf("Reading the INI file . . .          ");
 GetPath(name,CMD);
 strcat(name,INI_NAME);
 if ((ini_file=fopen(name,"r"))!=NULL)
 {ini_find=1,ini_open=1;
  strcpy(INI_PATH,name);
 }
 else
 {path=searchpath(INI_NAME);
  if (path==NULL)
   ini_find=0,ini_open=0;
  else
  {ini_file=fopen(path,"r");
   ini_find=1,ini_open=1;
   strcpy(INI_PATH,path);
  }
 }
 if (ini_open)
  ReadINI();
 else
 {strcpy(HZK,"C:\\HREADER\\HZK16");
  strcpy(LABEL_PATH,"C:\\HREADER\\LABEL\\");
  strcpy(TEMP_PATH,"C:\\HREADER\\TEMP\\");
  History=0;
 }
 fclose(ini_file);
}

void GetPath(unsigned char *path,unsigned char *filename)
{register int i;
 strcpy(path,filename);
 for (i=strlen(filename);i>=0;i--) if (*(path+i)=='\\') break;
 *(path+i+1)=0;
}

void ReadINI(void)
{if (pdini("HZKFILE=",8,text))
  strcpy(HZK,text);
 else
  strcpy(HZK,"C:\\HREADER\\HZK16");
 if (pdini("LABELPATH=",10,text))
 {strcpy(LABEL_PATH,text);
  zl(LABEL_PATH);
 }
 else
  strcpy(LABEL_PATH,"C:\\HREADER\\LABEL\\");
 if (pdini("TEMPPATH=",9,text))
 {strcpy(TEMP_PATH,text);
  zl(TEMP_PATH);
 }
 else
  strcpy(TEMP_PATH,"C:\\HREADER\\TEMP\\");
 if (pdini("HISTORY=",8,text))
 {strcpy(HISTORY,text);
  History=1;
 }
 else
  History=0;
 printf("OK!\n");
}

void ReadText(char *string)
{int i,c;
 for (i=0;i<80;i++)
 {c=fgetc(ini_file);
  if (feof(ini_file) || c=='\n') break;
  *(string+i)=c;
 }
 *(string+i)=0;
 strupr(string);
}

void zl(char *path)
{if (*(path+(strlen(path)-1))!='\\') strcat(path,"\\");
}

int pdini(unsigned char *string,int len,unsigned char *str)
{int ret=0;
 rewind(ini_file);
 while (!feof(ini_file))
 {ReadText(text2);
  if (strnicmp(text2,string,len)==0)
  {strcpy(str,text2+len);
   ret=1;
   break;
  }
 }
 return ret;
}

void WriteINI(void)
{if (ini_find)
 {if ((ini_file=fopen(INI_PATH,"w"))!=NULL)
  {fprintf(ini_file,"HzkFile=%s\n",HZK);
   fprintf(ini_file,"LabelPath=%s\n",LABEL_PATH);
   fprintf(ini_file,"TempPath=%s\n",TEMP_PATH);
   fprintf(ini_file,"History=%s\n",Path);
  }
  else
   return;
 }
 else
 {if ((ini_file=fopen(INI_NAME,"w"))!=NULL)
  {fprintf(ini_file,"HzkFile=%s\n",HZK);
   fprintf(ini_file,"LabelPath=%s\n",LABEL_PATH);
   fprintf(ini_file,"TempPath=%s\n",TEMP_PATH);
   fprintf(ini_file,"History=%s\n",Path);
  }
  else
   return;
 }
 fclose(ini_file);
}
