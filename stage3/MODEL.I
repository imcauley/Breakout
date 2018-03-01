# 1 "model.c" 1
# 1 "C:/c68/include/stdlib.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 9 "C:/c68/include/stdlib.h" 2
# 18 "C:/c68/include/stdlib.h"
typedef unsigned long  size_t;




typedef char  wchar_t;
# 44 "C:/c68/include/stdlib.h"
typedef struct {
    int		quot;
    int		rem;
} div_t;

typedef struct {
    long	quot;
    long	rem;
} ldiv_t;

 double atof (const char *s) ;
 int atoi (const char *str) ;
 long atol (const char *str) ;
 long int strtol (const char *nptr, char **endptr, int base) ;
 unsigned long int strtoul (const char *nptr, char **endptr, int base) ;
 double strtod (const char *s, char **endptr) ;

 void srand (unsigned int seed) ;
 int rand (void) ;

 void *malloc (size_t n) ;
 void free (void *param) ;
 void *realloc (void *_r, size_t n) ;
 void *calloc (size_t n, size_t sz) ;





 void *alloca (size_t) ;
# 89 "C:/c68/include/stdlib.h"
 void  abort (void) ;


 int atexit (void (*)(void)) ;

 void  exit (int) ;

 char *getenv (const char *tag) ;
 int system (const char *s) ;

 void *bsearch (const void *key, const void *base, size_t num, size_t size, int (*cmp )(const void *, const void *)) ;
 void qsort (void *base, size_t total_elems, size_t size, int (*cmp )(const void *, const void *)) ;

 int abs (int x) ;
 long labs (long x) ;

 div_t div (int num, int denom) ;
 ldiv_t ldiv (long num, long denom) ;

 int mblen (const char *, size_t) ;
 size_t mbstowcs (wchar_t *, const char *, size_t) ;
 int mbtowc (wchar_t *, const char *, size_t) ;
 size_t wcstombs (char *, const wchar_t *, size_t) ;
 int wctomb (char *, wchar_t) ;

 wchar_t *wcscat (wchar_t *, const wchar_t *) ;
 int wcscmp (const wchar_t *, const wchar_t *) ;
 wchar_t *wcscpy (wchar_t *, const wchar_t *) ;
 size_t wcslen (const wchar_t *) ;
 wchar_t *wcsncat (wchar_t *, const wchar_t *, size_t) ;
 int wcsncmp (const wchar_t *, const wchar_t *, size_t) ;
 wchar_t *wcsncpy (wchar_t *, const wchar_t *, size_t) ;
# 1 "model.c" 2
# 1 "C:/c68/include/stdio.h" 1
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
# 2 "model.c" 2
# 1 "./model.h" 1



typedef int bool;




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
    char score[4];
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
    Ball *ball;
    Paddle *paddle;
    Board *board;
    Score *score;
    Lives *lives;
    Header *header;
} Model;

void move_ball(Ball *ball, Brick *bricks, Paddle *paddle);
bool ball_collides(Ball *ball, Brick bricks[5 ][20 ], Paddle *paddle);
bool paddle_collides(Paddle *paddle);
void move_paddle(Paddle *paddle);
void launch_ball(Paddle *paddle, Ball *ball);
void create_bricks(Brick bricks[5 ][20 ]);
# 3 "model.c" 2





void create_bricks(Brick bricks[5 ][20 ])
{
	int r,c = 0;

	for(r=0;r < 5 ;r++)
	{
		for(c=0;c < 20 ; c++)
		{
			(bricks[r][c]).x = (r * 20);
			(bricks[r][c]).y = c * 5 ;
			(bricks[r][c]).broken = 0 ;
			(bricks[r][c]).width = 32;
			(bricks[r][c]).height = 16;
		}
	}
}

void move_ball(Ball *ball, Brick *bricks, Paddle *paddle)
{
        ball->x += ball->x_speed * ball->x_direction;
        ball->y += ball->y_speed * ball->y_direction;

        ball_collides(ball, bricks, paddle);
}

bool ball_collides(Ball *ball, Brick bricks[5 ][20 ], Paddle *paddle)
{
    int x;
    int y;

    if (ball->y  <= paddle->y)
    {
		if((ball->x >= paddle->x) && (ball->x <= (paddle->x + paddle->width)))
		{
			ball->y_direction = -1;
			return 1 ;
		}
    }

    if (ball->x <= 0 || ball->x + ball->width >= 640)
    {
        ball->x_direction *= -1;
        return 1 ;
    }

    if (ball->y <= 0 || ball->y + ball->height >= 400)
    {
        ball->y_direction *= -1;
        return 1 ;
    }

    if (ball->y <= 120)
    {
        unsigned int x_pos = ball-> x / 32;
        unsigned int y_pos = ball-> y / 16;

        if (bricks[x_pos][y_pos].broken == 0 )
        {
            bricks[x_pos][y_pos].broken = 1 ;

            if (ball->y <= bricks[x_pos][y_pos].y + bricks[x_pos][y_pos].height ||
                ball->y + ball->height >= bricks[x_pos][y_pos].y)
                ball->y_direction *= -1;
            else
                ball->x_direction *= -1;
            return 1 ;
        }
    }
# 117 "model.c"
    return 0 ;
}
void move_paddle(Paddle *paddle)
{
	paddle->x += (paddle->speed * paddle->direction);
    paddle_collides(paddle);
}

bool paddle_collides(Paddle *paddle)
{
    if ((paddle->x) < 0)
    {
        (paddle->x) = 0;
        return 1 ;
    }

	else if ((paddle->x + paddle->width) > 640)
	{
		paddle->x = (640 - paddle->width);
		return 1 ;
	}
    return 0 ;
}

void launch_ball(Paddle *paddle, Ball *ball)
{
    int random = rand() % 2;
    ball->x = paddle->x + (1.0/2.0) * paddle->width;
    ball->y = paddle->y + ball->height;
    ball->x_speed = 10;
    ball->y_speed = 10;
    ball->y_direction = 1;
    ball->x_direction = random;
}
