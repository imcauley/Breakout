# 1 "render.c" 1
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
# 1 "render.c" 2
# 1 "./render.h" 1
# 1 "./raster.h" 1
# 1 "./types.h" 1



typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

typedef int bool;
# 4 "./raster.h" 2


void draw_hori_line(UINT16 *base, int x, int y, int length);
void draw_vert_line(UINT16 *base, int x, int y, int length);
void plot_pixel(UINT16 *base, int x, int y);
void clear_screen(UINT32 *base);
void draw_rect(UINT16 *base, int x, int y, int length, int height);
void plot_char(UINT8 *base, int x, int y, int character);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height);
void draw_64rect(UINT32 *base, int x, int y, int height, bool clear);
void draw_8rect(UINT8 *base, int x, int y, int height, bool clear);
# 4 "./render.h" 2
# 1 "./model.h" 1
# 1 "./types.h" 1
# 1 "./model.h" 2
# 7 "./model.h"
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
    char lives[3];
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
bool ball_collides_walls(Ball *ball, Brick bricks[5 ][20 ], Paddle *paddle);
bool ball_collides_top(Ball *ball, Brick bricks[5 ][20 ], Paddle *paddle);
bool ball_collides_bottom(Ball *ball, Brick bricks[5 ][20 ], Paddle *paddle);
char ball_collides_bricks(Ball *ball, Brick bricks[5 ][20 ], Paddle *paddle, Score *score);
bool paddle_collides(Paddle *paddle);
void move_paddle(Paddle *paddle);
void launch_ball(Paddle *paddle, Ball *ball);
void create_bricks(Brick bricks[5 ][20 ]);
void start_game(Model *game);
void add_score(Score *score);
# 5 "./render.h" 2


void render(Model *game, Model *snap);
void render_paddle(UINT32 *base, Paddle *paddle);
void render_ball(UINT8 *base, Ball *ball);
void render_bricks(UINT32 *base, Brick bricks[][]);
void render_hud(UINT8 *base, Header *header, Lives *lives, Score *score);
void remove_brick(UINT32 *base, int row, int col);
void start_render(Model *game);
void render_clear(Model *game);
void simple_render(UINT8 *base8, UINT32 *base32, Model *game);
# 2 "render.c" 2
# 11 "render.c"
void simple_render(UINT8 *base8, UINT32 *base32, Model *game)
{
	clear_screen(base32);
	render_bricks(base32, (*game).bricks);
	render_paddle(base32, &((*game).paddle));
	render_ball(base8, &((*game).ball));
	render_hud(base8, &((*game).header), &((*game).lives), &((*game).score));
}

void render(Model *game, Model *snap)
{
	UINT8 *base8 = (UINT8 *) (void*)_trap_14_w((short)0x2) ;
	UINT32 *base32 = (UINT32 *) (void*)_trap_14_w((short)0x2) ;
	int col, row;

	render_clear(snap);
	render_paddle(base32, &((*game).paddle));
	render_ball(base8, &((*game).ball));

	for(row = 0; row < 5 ; row++)
	{
		for(col =0; col < 20 ; col++)
		{
			if(((*game).bricks[row][col].broken) && !((*snap).bricks[row][col].broken))
			{
				remove_brick(base32, row, col);
			}
		}
	}

}

void start_render(Model *game)
{
	UINT8 *base8 = (UINT8 *) (void*)_trap_14_w((short)0x2) ;
	UINT16 *base16 = (UINT16 *) (void*)_trap_14_w((short)0x2) ;
	UINT32 *base32 = (UINT32 *) (void*)_trap_14_w((short)0x2) ;

	clear_screen(base32);
	render_bricks(base32, (*game).bricks);
	render_paddle(base32, &((*game).paddle));
	render_ball(base8, &((*game).ball));

}

void render_clear(Model *game)
{
	UINT8 *base8 = (UINT8 *) (void*)_trap_14_w((short)0x2) ;
	UINT32 *base32 = (UINT32 *) (void*)_trap_14_w((short)0x2) ;

	Paddle *paddle = &(game->paddle);
	Ball *ball = &(game->ball);

	draw_64rect(base32, paddle->x, paddle->y, paddle->height, 1 );
	draw_8rect(base8, ball->x, ball->y, ball->height, 1 );
}

void render_paddle(UINT32 *base, Paddle *paddle)
{
	draw_64rect(base, paddle->x, paddle->y, paddle->height, 0 );
}

void render_ball(UINT8 *base, Ball *ball)
{
	draw_8rect(base, ball->x, ball->y, ball->height, 0 );
}

void render_bricks(UINT32 *base, Brick bricks[5 ][20 ])
{

    int r, c;

    UINT32 brick_bitmap[16 ] =
    {
        0xFFFFFFFF,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0xFFFFFFFF
    };


    for(r = 0; r < 5 ; r++)
    {
        for(c = 0; c < 20 ; c++)
        {
            if(!(bricks[r][c]).broken)
            {
                plot_bitmap_32(base, (c*32 ), ((r*16 ) + 40 ),
                    brick_bitmap, 16 );
            }
        }
    }


}

void remove_brick(UINT32 *base, int row, int col)
{
	UINT32 clear_bitmap[16 ] =
	{
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF
	};

	plot_bitmap_32(base, (col*32 ), ((row*16 ) + 40 ),
                    clear_bitmap, 16);
}

void render_hud(UINT8 *base8, Header *header, Lives *lives, Score *score)
{
	plot_char(base8, 2, 16, 35);
	plot_char(base8, 3, 16, 19);
	plot_char(base8, 4, 16, 31);
	plot_char(base8, 5, 16, 34);
	plot_char(base8, 6, 16, 21);

	plot_char(base8, 8, 16, (score->score[3]));
	plot_char(base8, 9, 16, (score->score[2]));
	plot_char(base8, 10, 16, (score->score[1]));
	plot_char(base8, 11, 16, (score->score[0]));
}
