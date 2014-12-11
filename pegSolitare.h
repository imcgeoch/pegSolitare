typedef enum {NORTH,SOUTH,EAST,WEST} direction_t;
typedef unsigned long board_t;

typedef struct list{
    board_t board;
    struct list *next;
}List_t;

void printboard(board_t currentboard);
void printanswer();
int move(board_t currentboard);

int checkwin(board_t currentboard);

int hash(board_t value);

int squaresexist(board_t currentboard, int tomove, direction_t direction);
int squaresempty(board_t currentboard, int tomove, direction_t direction);

board_t isemptymask(direction_t dir, int tomove);

board_t edgemask(direction_t direction);

void add2hash(board_t currentboard);

void add2solution(board_t currentboard);

List_t *checkhash(board_t currentboard);
