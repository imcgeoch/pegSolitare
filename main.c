#include<stdio.h>
#define SIZE 1000003


typedef unsigned long board_t;
board_t targetboard;
board_t startboard;
board_t northedge;
board_t southedge;
board_t eastedge;
board_t westedge;

board_t[] soultion;

typedef enum {NORTH,SOUTH,EAST,WEST} direction_t;


typedef struct {
	board_t board;
	struct list *next;
}List_t;

List_t[SIZE] table;

hashtable
board[35] solution;

int main()
{
//exactly what it looks like
}

void printboard(board_t currentboard)
{
 // prints a given board in human-readable form
}

void printanswer()
{
	//pritns the answer
}

int move(board_t currentboard)
{
//the heart of the program. moves through recursively, returns 1 or 0
{


int checkwin(board_t currentboard)
{
//checks win contition, returns 1 or 0
}

int hash(board_t value)
{
	return value%SIZE;
}

int squaresexist(board_t currentboard, int tomove, direction_t direction)
{
//checks if squares exist (and are not off the board), returns 1 or 0
}

int squaresempty(board_t currentboard, int tomove, direction_t direction)
{
//checks if squares are empty (and move was possible), returns 1 or 0
}

board_t isemptymask(direction_t dir, int tomove)
{
// returns boardmask of squares that must be empty
}

int edgemask(direction)
{
//returns boardmask of squares that are too close to the edge
}

void add2hash(board_t currentboard)
{
// adds currentboard to the table
	h = hash(currentboard);
	List_t *newcell;
	newlist = malloc(sizeof(List_t))
	newlist.board = currentboard;
// to be completed
	
}

list_t checkhash(board_t currentboard)
{
	//checks if currentboard is in hash

}

void transform(board_t currentboard, boart_t *compliments)
{
//fills passes array with compliments of currentboard
}
