#define BRICK_ROWS 5
#define BRICK_COLS 20

typedef int bool;

#define True 1
#define False 0

typedef struct Brick
{
    bool broken;
    unsigned int width, height;
    unsigned int x, y;
} Brick;

typedef struct Ball
{
    unsigned int x_speed, y_speed;
    int x_direction, y_direction;       /* -1 for up/left, 1 for right/down */
    unsigned int width, height;
    unsigned int x, y;
} Ball;

typedef struct Paddle
{
    unsigned int speed;
    int direction;
    unsigned int width, height;
    unsigned int x, y;
} Paddle;

typedef struct Board
{
    unsigned int width, height;
    unsigned int x, y;
} Board;

typedef struct Score
{
    unsigned int x, y;
    char score[3];                      /* to store 4 digit score */
} Score;

typedef struct Lives
{
    unsigned int x, y;
    char lives[2];                      /* maybe just use 3 X's for lives? */
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