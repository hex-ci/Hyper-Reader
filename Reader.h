/*

   The Hyper-Reader   Ver 4.10
       Update: 2000-12-17
     Produced by Zhao Chang
      Compile by TC++ 3.0

*/

#define HR_PATH "C:\\HREADER\\"
#define INI_NAME "HR.INI"
#define DEFAULT_HZK "HZK16"
#define LABEL_EXT ".LBL"
#define LABEL_FILE_HEAD "The Hyper-Reader Label File.Produced by Zhao Chang.\x1a"
#define TEMP_FILE "HR_TEMP!.$$$"
#define XWID 4
#define S_XWID 1
#define YWID 4
#define X_S 20
#define Y_S 10
#define NORMAL 0
#define INVERSE 1
#define PGUP 0x4900
#define PGDN 0x5100
#define INSERT 0x5200
#define ESC 0x011b
#define ENTER 0x1c0d
#define BACKSPACE 0x0e08
#define UP 0x4800
#define DOWN 0x5000
#define LEFT 0x4b00
#define RIGHT 0x4d00
#define HOME 0x4700
#define END 0x4f00
#define DELETE 0x5300
#define SPACE 0x3920
#define CTRL_Q 0x1011
#define CTRL_BACKSPACE 0x0e7f
#define CTRL_Y 0x1519
#define CTRL_FXG 0x2b1c
#define F1 0x3b00
#define F2 0x3c00
#define F3 0x3d00
#define F4 0x3e00
#define F5 0x3f00
#define F10 0x4400

int input(unsigned char *string,int lenth,int x,int y,int bco,int fco);
int load_file(void);
void image(void);
void HyperReader_init(void);
void graph_init(void);
void set_graph(void);
void alloc_mem(void);
void read_HZK(void);
void read_file(void);
void read_LabelFile(void);
void read_ini(void);
void print(unsigned char *String,int x,int y);
void read_story(unsigned char *story);
void win(int x1,int y1,int x2,int y2,int cor,int co);
void graph_window(int x1,int y1,int x2,int y2);
void edit_label(void);
void bof_eof(void);
void wait(void);
void quit(void);
void OpenCur(void);
void CloseCur(void);
void clear(void);
void PutPoint(int x,int y,int color);
void small_display(unsigned char *String,int x,int y);
void pexit(void);
void ClearKey(void);
void ClrScr(void);
void GetPath(unsigned char *path,unsigned char *filename);
void Load(void);
void WriteINI(void);


#if defined(HR_MAIN)

 FILE *story_file,*label_file,*temp_file;
 int xx=X_S,yy=Y_S,ARGC,History=0;
 int label_open=0,label_find=0,temp_open=0,ini_open=0,ini_find=0;
 int file_b=1,file_e=0;
 int label_total=0,SetType=1;
 long pointer=0,page0,page1,story_size,last_position=0;
 unsigned char *ARGV,*CMD,story[350],story_name[70],label_name[70],temp_name[70],header[54]={"The Hyper-Reader Label File. Produced by Zhao Chang.\x1a"};
 unsigned char HZK[70],LABEL_PATH[70],TEMP_PATH[70],Path[80],text[80],text2[80],HISTORY[80];
 char *Version="4.10",*Update="2000.12.17";
 char *Memory;
 char Screen[4096];
 unsigned char INI_PATH[80];

#endif

#if defined(HR_GRAPHICS)

 extern long page0,page1,story_size;
 extern int xx,yy,SetType;

#endif

#if defined(HR_READ)

 extern FILE *story_file,*label_file,*temp_file;
 extern unsigned char story_name[70],label_name[70],temp_name[70];
 extern long story_size,last_position;
 extern int label_find,label_open,label_total,temp_open,ARGC,History;
 extern char *ARGV,*CMD,HZK[70],LABEL_PATH[70],TEMP_PATH[70],Path[80],HISTORY[80];
 extern char huge *Memory;

#endif

#if defined(HR_LABEL)

 extern FILE *label_file,*temp_file,*story_file;
 extern long page0,page1,pointer,story_size;
 extern int label_total,label_open,temp_open,label_find,file_e,file_b;
 extern unsigned char story_name[70],story[350],label_name[70],header[54],temp_name[70];
 extern char Screen[4096];

#endif

#if defined(HR_QUIT)

 extern char huge *Memory;
 extern FILE *temp_file;
 extern unsigned char temp_name[70];
 extern int temp_open;

#endif

#if defined(HR_READ_STORY)

 extern FILE *story_file;
 extern long pointer,story_size,page0,page1;
 extern unsigned char story[350];
 extern int file_b,file_e,SetType;

#endif

#if defined(HR_WAIT)

 extern int file_b,file_e,label_open,xx,yy,SetType;
 extern long pointer,story_size,page0,last_position;
 extern FILE *story_file;
 extern unsigned char story[350];

#endif

#if defined(HR_LOAD)

 extern unsigned char story_name[70],Path[80];
 extern char *Version,*Update;

#endif

#if defined(HR_INI)

 extern unsigned char *CMD;
 extern int ini_find,ini_open,History;
 extern unsigned char HZK[70],LABEL_PATH[70],TEMP_PATH[70],text[80],text2[80];
 extern unsigned char HISTORY[80],INI_PATH[80],Path[80];

#endif

#if defined(HR_INPUT)

#endif

#if defined(HR_IMAGE)

 extern char *Version,*Update;

#endif
