#include<stdio.h>
#include<stdlib.h>
#include"pegSolitare.h"
#define SIZE 1000003


typedef unsigned long board_t;
board_t targetboard = 0x1c1c7f777f1c1c;
board_t startboard = 0x8000000;
board_t northedge = 0x1c1c6363000000;
board_t southedge = 0x63631c1c;
board_t eastedge = 0xc0c0303030c0c;
board_t westedge = 0x18186060601818;
board_t solution[32];

List_t *table[SIZE];


int main()
{
	move(startboard);
	printanswer();

	return 0;
}

void printboard(board_t currentboard)
{
	int r = 0;
	for (int i=0; i<64; i++){ 
		
		if (currentboard & 1)
			printf("0");
		else 
			printf("-");
		currentboard >>= 1;
		if (++r == 8){
			r = 0;
			printf("\n");
		}
	}
	printf("\n\n");
	return;
 // prints a given board in human-readable form
}

void printanswer()
{
	//pritns the answer
	for (int i = 0; i < 32; i++){
		printboard(solution[i]);
	}

}

int move(board_t currentboard)
{
	int a;
	if (checkhash(currentboard) != NULL) 
		return 0;
	
	if (checkwin(currentboard) == 1){
		add2solution(currentboard);
		return 1;
	
	}
	board_t nextmove = currentboard;
	int i = 0;
	for (int iter = 0; iter < 64; iter ++){
		nextmove >>= 1;
		i++;
		if (nextmove & 1 == 1){
			if (squaresexist(currentboard, i , NORTH) 
					& squaresempty(currentboard, i, NORTH) == 1){
				board_t newboard = currentboard ^ ((long)0x10101 << i);
				if (move(newboard) == 1){
					add2solution(currentboard);
					return 1;
				}
			}
		
			if (squaresexist(currentboard, i, SOUTH) 
            	    & squaresempty(currentboard, i, SOUTH) == 1){
					board_t newboard = currentboard ^ ((long)0x10101 << (i-16));
					if (move(newboard) == 1){
					add2solution(currentboard);
					return 1;
					}
			}

			if (squaresexist(currentboard, i, WEST) 
    	           & squaresempty(currentboard, i, WEST) == 1){
					board_t newboard = currentboard ^ ((long)0x7 << (i));
					if (move(newboard) == 1){
					add2solution(currentboard);
					return 1;
				}
			}

			if (squaresexist(currentboard, i, EAST) 
        	       & squaresempty(currentboard, i, EAST) == 1){			
					board_t newboard = currentboard ^ ((long)0x7 << (i-2));
					if (move(newboard) == 1){
					add2solution(currentboard);
					return 1;
				}
			}
		}
	}
	add2hash(currentboard);
	return 0;
	

}

int checkwin(board_t currentboard)
{

//checks win contition, returns 1 or 0
	if (currentboard == targetboard){		
		printf("success!\n");
		printboard(currentboard);
		return 1;
	
	}
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
	return ((edgemask(direction)) >> tomove) ^ 1;
}

int squaresempty(board_t currentboard, int tomove, direction_t direction)
{

	if ((isemptymask(direction, tomove) | currentboard) == ((isemptymask(direction, tomove)) ^ currentboard))
		return 1;
	else
		return 0;
}

board_t isemptymask(direction_t dir, int tomove)
{
// returns boardmask of squares that must be empty

	switch(dir){
	case NORTH:
		return (long)0x10100 << tomove; 
	case SOUTH:
		return (long)0x101 << (tomove - 16);
	case EAST:
		return (long)0x6 << (tomove -3);
	case WEST:
		return (long)0x6 << tomove;
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
	return 0;
}

void add2hash(board_t currentboard)
{
	if (checkhash(currentboard) != NULL)
		return;

		int h = hash(currentboard);
		List_t *newlist = malloc(sizeof(List_t));
		if (!newlist){
			printf("malloc no workie");
			return;	
		}
		newlist->board = currentboard;

		newlist->next = table[h];
		table[h] = newlist;
}

void add2solution(board_t currentboard)
{
	for (int i = 0; i < 35; i++){
		if (solution[i] == NULL){
			solution[i] = currentboard;
			return;	
		}
	}

}

List_t *checkhash(board_t currentboard)
{
	//checks if currentboard is in hash
	for (List_t *i = table[hash(currentboard)]; i != NULL; i = i->next){
		if (i->board == currentboard)
			return i;
	} 
	return NULL;
}

