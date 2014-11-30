#include<stdio.h>
#define SIZE 1000003


typedef unsigned long board_t;
board_t targetboard = 0x1c3e7f777f3e1c;
board_t startboard = 0x8000000;
board_t northedgei = 0x1c3e6341000000;
board_t southedgei = 0x41633e1c;
board_t eastedge = 0x18306060603018;
board_t westedge = 0x18306060603018;

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
	if (checkhash(currentboard) != NULL) 
		return 0;
	
	if (checkwin(currentboard) == 1){
		add2solution(currentboard);
		return 1;
	
	}
	for (int i = 0; i < 64; i ++){
		if ((currentboard >> i) & 1 == 1){
			if (squaresexist(currentboard, i, NORTH) 
                & squaresempty(currentboard, i, NORTH) == 1){			
				if (move(currentboard ^ 0x10101 << i) == 1){
					add2solution(currentboard);
					return 1;
				}
			}
			if (squaresexist(currentboard, i, SORTH) 
                & squaresempty(currentboard, i, SORTH) == 1){			
				if (move(currentboard ^ 0x10101 << i-16) == 1){
					add2solution(currentboard);
					return 1;
				}
			}
			if (squaresexist(currentboard, i, EAST) 
                & squaresempty(currentboard, i, EAST) == 1){			
				if (move(currentboard ^ 0x7 << i-2) == 1){
					add2solution(currentboard);
					return 1;
				}
			}
			if (squaresexist(currentboard, i, WEST) 
                & squaresempty(currentboard, i, WEST) == 1){			
				if (move(currentboard ^ 0x7 << i) == 1){
					add2solution(currentboard);
					return 1;
				}
			}
		}
	}
	add2hash(currentboard);
	return 0;
	

}
/*
int trymove(board_t currentboard, )
{

}

int makemove()
{

}
*/

int checkwin(board_t currentboard)
{

//checks win contition, returns 1 or 0
	if (currentboard == targetboard)
		return 1;
	else
		return 0;

}

int hash(board_t value)
{
	return value%SIZE;
}

int squaresexist(board_t currentboard, int tomove, direction_t direction)
{
//checks if squares exist (and are not off the board), returns 1 or 0
	return ((currentboard ^= edgemask(direction)) >> tomove) & 1;
}

int squaresempty(board_t currentboard, int tomove, direction_t direction)
{
//checks if squares are empty (and move was possible), returns 1 or 0
	if (currentboard ^ isemptymask(direction, tomove) == currentboard)
		return 1;
	else
		return 0;
}

board_t isemptymask(direction_t dir, int tomove)
{
// returns boardmask of squares that must be empty

	switch(direction){
		case NORTH:
			return 0x10100 << tomove; 
		case SOUTH:
			return 0x10100 << (tomove - 16);
		case EAST:
			return 0x6 << (tomove -2);
		case WEST:
			return 0x6 << tomove;
	}

}

board_t edgemask(direction_t direction)
{
//returns boardmask of squares that are too close to the edge
	switch(direction){
	case NORTH:
		return northedge;
	case SOUTH:
		return southedge;
	case EAST:
		return eastedge;
	case WEST:
		return westedge;
	}

}

void add2hash(board_t currentboard)
{
// adds currentboard to the table
// checking may be redundant, depending on our implementation.
	if (checkhash(currentboard) != NULL)
		return;

	board_t[8] compliments;
	transform(currentboard, &compliments[0]);	
	for (int i =0; i < 8; i++){

		h = hash(compliments[i]);
		List_t *newcell;
		newlist = malloc(sizeof(List_t));
		newlist.board = compliments[i];

		newcell->next = table[h];
		table[h] = newcell;
	}	
}

void add2soultion(board_t currentboard)
{
	for (int i = 0; i < 35; i++){
		if (solution[i] == NULL){
			solution[i] = currentboard;
			return;	
		}
	}
}

list_t checkhash(board_t currentboard)
{
	//checks if currentboard is in hash
	for (List_t i = table[hash(currentbard)]; i != NULL; i = i->next){
		if (i.board == currentboard)
			return i;
	} 
	return NULL;
}

/* fuck this it's too hard and might not be worth it
void transform(board_t currentboard, board_t *compliments)
{
//fills passes array with compliments of currentboard
	compliments[0] = currentboard;
	 
	// mirror
	for (int i = 0; i < 8; i++){
		compliments[1]	

	}

}
*/
