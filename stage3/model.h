#define BRICK_ROWS 5
#define BRICK_COLS 20

typedef struct Position
{
    unsigned int x, y;
} Position;

typedef struct Brick
{
    Position pos;
    bool broken;
    unsigned int width, height;
} Brick;

typedef struct Ball
{
    Position pos;
    unsigned int x_speed, y_speed;
    int x_direction, y_direction;       /* -1 for up/left, 1 for right/down */
    unsigned int width, height;
} Ball;

typedef struct Paddle
{
    Position pos;
    unsigned int speed;
    int direction;
    unsigned int width, height;
} Paddle;

typedef struct Board
{
    Position pos;                       /* Where the board starts */
    unsigned int width, height;
} Board;

typedef struct Score
{
    Position pos;
    char score[3];                      /* to store 4 digit score */
} Score;

typedef struct Lives
{
    Position pos;
    char lives[2];                      /* maybe just use 3 X's for lives? */
} Lives;

typedef struct Header
{
    Position pos;                       /* where dividing line is drawn */
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


