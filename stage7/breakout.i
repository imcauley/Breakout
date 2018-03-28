# 1 "breakout.c" 1
# 1 "./render.h" 1
# 1 "./raster.h" 1
# 1 "./types.h" 1
# 22 "./types.h"
typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

typedef int bool;
# 22 "./raster.h" 2


void clear_screen(UINT32 *base);
void plot_char(UINT8 *base, int x, int y, int character);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height);
void draw_64rect(UINT32 *base, int x, int y, int height, bool clear);
void draw_8rect(UINT8 *base, int x, int y, int height, bool clear);
UINT16 *get_video_base();
# 22 "./render.h" 2
# 1 "./model.h" 1
# 1 "./types.h" 1
# 19 "./model.h" 2
# 25 "./model.h"
typedef struct Brick
{
    int x, y;
    bool broken;
    unsigned int width, height;
} Brick;

typedef struct Ball
{
    int x, y;
    unsigned int x_speed, y_speed;
    int x_direction, y_direction;
    unsigned int width, height;
    bool launch;
    bool launched;
} Ball;

typedef struct Paddle
{
	int x, y;
    int speed;
    int direction;
    unsigned int width, height;
} Paddle;

typedef struct Board
{
	unsigned int x, y;
    unsigned int width, height;
} Board;

typedef struct Score
{
    unsigned int x, y;
    int score[4];
} Score;

typedef struct Lives
{
    unsigned int x, y;
    bool lives[3];
    bool game_over;
} Lives;

typedef struct Header
{
    unsigned int x, y;
} Header;

typedef struct Model
{
    Brick bricks[5 ][20 ];
    Ball ball;
    Paddle paddle;
    Board board;
    Score score;
    Lives lives;
    Header header;
} Model;

void move_ball(Ball *ball, Brick bricks[][], Paddle *paddle);
bool ball_collides_top(Ball *ball, Brick bricks[5 ][20 ], Paddle *paddle);
bool ball_collides_bottom(Ball *ball, Brick bricks[5 ][20 ], Paddle *paddle);
char ball_collides_bricks(Ball *ball, Brick bricks[5 ][20 ], Paddle *paddle, Score *score);
bool ball_collides_right(Ball *ball);
bool ball_collides_left(Ball *ball);
bool paddle_collides(Paddle *paddle);
void move_paddle(Paddle *paddle);
void launch_ball(Paddle *paddle, Ball *ball);
void create_bricks(Brick bricks[5 ][20 ]);
void start_game(Model *game);
bool ball_collides_paddle(Ball *ball, Brick bricks[5 ][20 ], Paddle *paddle);
void add_score(Score *score);
bool game_over(Lives *lives);
# 23 "./render.h" 2


void render(UINT8 *base8, UINT32 *base32, Model *game);
void render_paddle(UINT32 *base, Paddle *paddle);
void render_ball(UINT8 *base, Ball *ball);
void render_bricks(UINT32 *base, Brick bricks[][]);
void render_hud(UINT8 *base, Header *header, Lives *lives, Score *score);
void remove_brick(UINT32 *base, int row, int col);
void start_render(UINT32 *base32, Model *game);
void render_clear(UINT8 *base8, UINT32 *base32, Model *game);
void simple_render(UINT8 *base8, UINT32 *base32, Model *game);
void render_splash_screen(UINT32 *base32);
void render_game_over(UINT8 *base8, Score *score);
# 19 "breakout.c" 2
# 1 "./input.c" 1
# 1 "C:/c68/include/osbind.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 9 "C:/c68/include/osbind.h" 2
# 1 "C:/c68/include/ostruct.h" 1
# 22 "C:/c68/include/ostruct.h"
typedef struct {
    long b_free;
    long b_total;
    long b_secsiz;
    long b_clsiz;
} _DISKINFO;


typedef struct {
  short time;
  short date;
} _DOSTIME;


typedef struct
{
        unsigned char maxlen;
        unsigned char actuallen;
        char    buffer[255];
} _CCONLINE;
# 48 "C:/c68/include/ostruct.h"
typedef struct _dta {
    char 	    dta_buf[21];
    char            dta_attribute;
    unsigned short  dta_time;
    unsigned short  dta_date;
    long            dta_size;
    char            dta_name[14];
} _DTA;
# 98 "C:/c68/include/ostruct.h"
typedef struct {
  short recsiz;
  short clsiz;
  short clsizb;
  short rdlen;
  short fsiz;
  short fatrec;
  short datrec;
  short numcl;
  short bflags;
} _BPB;




typedef struct _md {
    struct _md	*md_next;
    long	 md_start;
    long	 md_length;
    long	 md_owner;
} _MD;


typedef struct {
    _MD *mp_free;
    _MD *mp_used;
    _MD *mp_rover;
} _MPB;
# 141 "C:/c68/include/ostruct.h"
typedef struct {
    char    *ibuf;
    short   ibufsiz;
    volatile short   ibufhd;
    volatile short   ibuftl;
    short   ibuflow;
    short   ibufhi;
} _IOREC;


typedef struct {
	char	topmode;
	char	buttons;
	char	xparam;
	char	yparam;
	short	xmax;
	short	ymax;
	short	xstart;
	short	ystart;
} _PARAM;


typedef struct {
    void    (*midivec)	(void) ;
    void    (*vkbderr)	(void) ;
    void    (*vmiderr)	(void) ;
    void    (*statvec)	(void *) ;
    void    (*mousevec)	(void *) ;
    void    (*clockvec)	(void *) ;
    void    (*joyvec)	(void *) ;
    long    (*midisys)	(void) ;
    long    (*ikbdsys)	(void) ;
    char    kbstate;
} _KBDVECS;


typedef struct {
    void *unshift;
    void *shift;
    void *caps;
} _KEYTAB;


typedef struct
{
        void    *pb_scrptr;
        int     pb_offset;
        int     pb_width;
        int     pb_height;
        int     pb_left;
        int     pb_right;
        int     pb_screz;
        int     pb_prrez;
        void    *pb_colptr;
        int     pb_prtype;
        int     pb_prport;
        void    *pb_mask;
} _PBDEF;
# 17 "C:/c68/include/osbind.h" 2
# 33 "C:/c68/include/osbind.h"
 long _trap_1_w		(short) ;
 long _trap_1_ww	(short,short) ;
 long _trap_1_wl	(short,long) ;
 long _trap_1_wlw	(short,long,short) ;
 long _trap_1_wwll	(short,short,long,long) ;
 long _trap_1_wlww	(short,long,short,short) ;
 long _trap_1_www	(short,short,short) ;
 long _trap_1_wll	(short,long,long) ;
 long _trap_1_wwlll	(short,short,long,long,long) ;
 long _trap_1_wwwll	(short,short,short,long,long) ;
 long _trap_13_wl	(short,long) ;
 long _trap_13_w	(short) ;
 long _trap_13_ww	(short,short) ;
 long _trap_13_www	(short,short,short) ;
 long _trap_13_wwlwww	(short,short,long,short,short,short) ;
 long _trap_13_wwl	(short,short,long) ;
 long _trap_14_wwl	(short,short,long) ;
 long _trap_14_wwll	(short,short,long,long) ;
 long _trap_14_ww	(short,short) ;
 long _trap_14_w	(short) ;
 long _trap_14_wllw	(short,long,long,short) ;
 long _trap_14_wl	(short,long) ;
 long _trap_14_www	(short,short,short) ;
 long _trap_14_wllwwwww (short,long,long,short,short,short,short,short) ;
 long _trap_14_wllwwwwlw (short,long,long,short,short,short,short,long,short) ;
 long _trap_14_wllwwwwwlw (short,long,long,short,short,short,short,short,long,short) ;
 long _trap_14_wwwwwww	(short,short,short,short,short,short,short) ;
 long _trap_14_wlll	(short,long,long,long) ;
 long _trap_14_wllww	(short,long,long,short,short) ;
 long _trap_14_wwwwl	(short,short,short,short,long) ;
 long _trap_14_wwwl	(short,short,short,long) ;
 long _trap_14_wlwlw	(short,long,short,long,short) ;
# 103 "C:/c68/include/osbind.h"
 long _trap_1_ 	(short,...) ;
 long _trap_14_ 	(short,...) ;
 long _trap_13_ 	(short,...) ;
# 19 "./input.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 20 "C:/c68/include/stdio.h"
typedef unsigned long  size_t;
# 69 "C:/c68/include/stdio.h"
typedef	struct
	{
	long		_cnt;
	unsigned char	*_ptr;
	unsigned char	*_base;
	unsigned int	_flag;
	int		_file;
	long		_bsiz;
	unsigned char	_ch;
	}
	FILE;


typedef unsigned long fpos_t;
# 92 "C:/c68/include/stdio.h"
extern	FILE	_iob[];
# 108 "C:/c68/include/stdio.h"
 char *	ctermid	(char *) ;




 int	remove	(const char *) ;
 int	rename	(const char *, const char *) ;
 char *	tmpnam	(char *) ;
 FILE *	tmpfile	(void) ;

 int	fclose	(FILE *) ;
 int	fflush	(FILE *) ;

 FILE *	fopen	(const char *, const char *) ;
 FILE *	freopen	(const char *, const char *, FILE *) ;

 void	setbuf	(FILE *, char *) ;
 int	setvbuf	(FILE *, char *, int, size_t) ;
# 132 "C:/c68/include/stdio.h"
 int  fscanf  (FILE *, const char *, ...) ;
 int  scanf   (const char *, ...) ;
 int  sscanf  (const char *, const char *, ...) ;


 int	fprintf	(FILE *, const char *, ...) ;
 int	printf	(const char *, ...) ;
 int	sprintf	(char *, const char *, ...) ;

 int 	vfprintf (FILE *, const char *, char * ) ;
 int 	vprintf	 (const char *, char * ) ;
 int 	vsprintf (char *, const char *, char * ) ;

 int	vscanf  (const char *, char * ) ;
 int	vfscanf (FILE *, const char *, char * ) ;
 int	vsscanf	(const char *, const char *, char * ) ;


 int	fgetc	(FILE *) ;
 char	*fgets	(char *, int, FILE *) ;
 char	*gets	(char *) ;
 int	fputc	(int c, FILE *) ;
 int	fputs	(const char *, FILE *) ;
 int	puts	(const char *) ;

 size_t	fread	(void *, size_t, size_t, FILE *) ;
 size_t	fwrite	(const void *, size_t, size_t, FILE *) ;

 int	fgetpos	(FILE *, fpos_t *) ;
 int	fsetpos	(FILE *, fpos_t *) ;

 int	fseek	(FILE *, long, int) ;
 long	ftell	(FILE *) ;
 void	rewind	(FILE *) ;

 void	perror	(const char *) ;


 FILE	*fdopen	(int, const char *) ;


 FILE *	fopenp	(const char *, const char *) ;
 int 	fungetc	(int, FILE *) ;
 int	pclose	(FILE *) ;
 FILE *	popen	(const char *, const char *) ;
 void	setlinebuf	(FILE *) ;

 void	_binmode	(int) ;
 long 	getl	(FILE *) ;
 long 	putl	(long, FILE *) ;
 short 	getw	(FILE *) ;
 short 	putw	(short, FILE *) ;
 void	_getbuf	(FILE *fp) ;
# 192 "C:/c68/include/stdio.h"
 int	_filbuf	(FILE *) ;
# 20 "./input.c" 2
# 1 "./types.h" 1
# 21 "./input.c" 2


long get_input();
bool key_pressed();


long get_input()
{
	return _trap_1_w((short)0x08) ;
}

bool key_pressed()
{
	long input = (short)_trap_1_w((short)0x0B) ;
	if(input == 0)
	{
		return 0 ;
	}
	else
		return 1 ;
}
# 20 "breakout.c" 2
# 1 "./events.h" 1
# 19 "./events.h"
void asynch_events(Paddle *paddle, Ball *ball, long input);
void synch_events(Paddle *paddle, Ball *ball, Brick bricks[][]);
void condition_events(Paddle *paddle, Ball *ball, Brick bricks[][], Score *score, Lives *lives);
void die(Lives *lives);
# 21 "breakout.c" 2
# 1 "C:/c68/include/osbind.h" 1
# 22 "breakout.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 23 "breakout.c" 2
# 1 "C:/c68/include/string.h" 1
# 25 "C:/c68/include/string.h"
 void *memcpy (void *dst, const void *src, size_t size) ;
 void *memmove (void *dst, const void *src, size_t size) ;
 int memcmp (const void *s1, const void *s2, size_t size) ;
 void *memchr (const void *s, int ucharwanted, size_t size) ;
 void *memset (void *s, int ucharfill, size_t size) ;

 char *strcpy (char *dst, const char *src) ;
 char *strncpy (char *dst, const char *src, size_t n) ;
 char *strcat (char *dst, const char *src) ;
 char *strncat (char *dst, const char *src, size_t n) ;
 int strcmp (const char *scan1, const char *scan2) ;
 int strncmp (const char *scan1, const char *scan2, size_t n) ;
 int strcoll (const char *scan1, const char *scan2) ;
 size_t	strxfrm (char *to, const char *from, size_t maxsize) ;
 char *strchr (const char *s, int charwanted) ;
 size_t strcspn (const char *s, const char *reject) ;
 char *strpbrk (const char *s, const char *breakat) ;
 char *strrchr (const char *s, int charwanted) ;
 size_t strspn (const char *s, const char *accept) ;
 char *strstr (const char *s, const char *wanted) ;
 char *strtok (char *s, const char *delim) ;
 size_t strlen (const char *scan) ;
 char *strerror (int errnum) ;
# 54 "C:/c68/include/string.h"
 void *memccpy (void *dst, const void *src, int ucharstop, size_t size) ;
 char *strlwr (char *string) ;
 char *strupr (char *string) ;



 char *strrev (char *string) ;
 char *strdup (const char *s) ;




 char *index (const char *s, int charwanted) ;
 char *rindex (const char *s, int charwanted) ;
 void bcopy (const void *src, void *dst, size_t length) ;
 int bcmp (const void *src, const void *dst, size_t n) ;
 void bzero (void *b, size_t n) ;

 void _bcopy (const void *src, void *dst, unsigned long length) ;
 int  _bcmp (const void *s1, const void *s2, unsigned long length) ;
 void _bzero (void *dst, unsigned long length) ;

 int stricmp ( const char *, const char * ) ;
 int strnicmp ( const char *, const char *, size_t ) ;
 int strcmpi ( const char *, const char * ) ;
 int strncmpi ( const char *, const char *, size_t ) ;
# 24 "breakout.c" 2




UINT8 buffer2[32256];
UINT8 background[32256];

unsigned long get_time()
{
	unsigned long *timer;
	unsigned long timeNow;
	long old_ssp;
	old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
	timer = (unsigned long *)0x462;
	timeNow = *timer;
	_trap_1_wl((short)0x20,(long)(old_ssp)) ;
	return timeNow;
}
# 54 "breakout.c"
UINT8 *get_base(UINT8 buffer[])
{
	UINT8 *base;
	unsigned int difference;
	base = buffer;
	difference = (int) base;
	difference %= 0x100;
	difference = 0x100 - difference;
	return base + difference;
}

int main()
{

	UINT8 *buffer1_8 = (UINT8 *) get_video_base();
	UINT32 *buffer1_32 = (UINT32 *) get_video_base();



	UINT8 *buffer2_8 = get_base(buffer2);
	UINT32 *buffer2_32 = (UINT32 *) buffer2_8;


	UINT8 *background_8 = get_base(background);
	UINT32 *background_32 = (UINT32 *) background_8;


	UINT8 *render_base_8 = buffer2_8;
	UINT32 *render_base_32 = buffer2_32;


	Brick current[5][20];
	int x,y = -1;

	long input = 0;
	unsigned long timeThen, timeNow, timeElapsed = get_time();
	bool swap = 0 ;


	Model game;
	start_game(&game);


	memcpy(current, game.bricks, sizeof(current));

	render_splash_screen(buffer1_32);
# 189 "breakout.c"
	return 0;
}
