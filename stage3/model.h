#define BRICK_ROWS 5
#define BRICK_COLS 20

typedef int bool;

#define True 1
#define False 0

typedef struct Brick
{
    unsigned int x, y;
    bool broken;
    unsigned int width, height;
} Brick;

typedef struct Ball
{
    int x, y;
    unsigned int x_speed, y_speed;
    int x_direction, y_direction;       /* -1 for up/left, 1 for right/down */
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
    char score[4];                      /* to store 4 digit score */
} Score;

typedef struct Lives
{
    unsigned int x, y;
    char lives[3];                      /* maybe just use 3 X's for lives? */
} Lives;

typedef struct Header
{
    unsigned int x, y;                      /* where dividing line is drawn */
} Header;

typedef struct Model
{
    Brick bricks[BRICK_ROWS][BRICK_COLS];
    Ball ball;
    Paddle paddle;
    Board board;
    Score score;
    Lives lives;
    Header header;
} Model;

void move_ball(Ball *ball, Brick bricks[], Paddle *paddle);
bool ball_collides(Ball *ball, Brick *bricks, Paddle *paddle);
bool paddle_collides(Paddle *paddle);
void move_paddle(Paddle *paddle);
void launch_ball(Paddle *paddle, Ball *ball);
