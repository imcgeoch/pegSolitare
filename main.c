#include<stdio.h>
#include<stdlib.h>
#include"pegSolitare.h"
#define SIZE 1000003


typedef unsigned long board_t;
board_t targetboard = 0x1c3e7f777f3e1c;
board_t startboard = 0x8000000;
board_t northedge = 0x1c3e6341000000;
board_t southedge = 0x41633e1c;
board_t eastedge = 0xc06030303060c;
board_t westedge = 0x18306060603018;
board_t solution[35];




List_t *table[SIZE];


int main()
{
	printf("NSEW\n");
    printboard(northedge);
	printboard(southedge);
	printboard(eastedge);
	printboard(westedge);

	move(startboard);
	printanswer();

	return 0;
//exactly what it looks like
}

void printboard(board_t currentboard)
{
	int r = 0;
	for (int i=0; i<64; i++){ //while (currentboard){
		
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
	for (int i = 0; i < 35; i++){
		printboard(solution[i]);
	}

}

int move(board_t currentboard)
{
//the heart of the program. moves through recursively, returns 1 or 0
//	printf("moving!\n\n");
	printboard(currentboard);
	
//	printboard(currentboard);
	int a;
	//scanf("%d", &a);
	if (checkhash(currentboard) != NULL) 
		return 0;
	
	if (checkwin(currentboard) == 1){
		add2solution(currentboard);
		return 1;
	
	}
	board_t nextmove = currentboard;
	int i = 0;
//	while ((signed long)nextmove > 0){
	for (int iter = 0; iter < 64; iter ++){
//		printf("%d\n", nextmove);	
		nextmove >>= 1;
		i++;
//		printf("square %d\n" , i++);	
		if (nextmove & 1 == 1){
//			printf("nextmove &1 ==1\n");
			if (squaresexist(currentboard, i , NORTH) 
					& squaresempty(currentboard, i, NORTH) == 1){
				board_t newboard = currentboard ^ ((long)0x10101 << i);
	//			if (newboard == currentboard)
//					printf("oh no!");
				if (move(newboard) == 1){
					add2solution(currentboard);
					return 1;
				}
			}
		
			if (squaresexist(currentboard, i, SOUTH) 
            	    & squaresempty(currentboard, i, SOUTH) == 1){
					board_t newboard = currentboard ^ ((long)0x10101 << (i-16));
	//				if (newboard == currentboard)
//						printf("oh no!");
					if (move(newboard) == 1){
					add2solution(currentboard);
					return 1;
					}
			}

			if (squaresexist(currentboard, i, WEST) 
    	           & squaresempty(currentboard, i, WEST) == 1){
					board_t newboard = currentboard ^ ((long)0x7 << (i));
//					printf("west");
	//				if (newboard == currentboard)
//						printf("oh no!");
					if (move(newboard) == 1){
					add2solution(currentboard);
					return 1;
				}
			}

			if (squaresexist(currentboard, i, EAST) 
        	       & squaresempty(currentboard, i, EAST) == 1){			
					board_t newboard = currentboard ^ ((long)0x7 << (i-2));
//					printf("east");
	//				if (newboard == currentboard)
//						printf("oh no!");
					if (move(newboard) == 1){
					add2solution(currentboard);
					return 1;
				}
			}
//			printf("no if statements worked!\n");
		}
//		else
//		printf("didn't look");
	}
//	printf("about to call add2hash");
	add2hash(currentboard);
//	printf("made it out of loop!\n");
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
//	printf("hash%d\n" ,value%SIZE);
	return value%SIZE;
}

int squaresexist(board_t currentboard, int tomove, direction_t direction)
{
//checks if squares exist (and are not off the board), returns 1 or 0
//	printf("edges...\n");	
//	printboard(currentboard);
//	printboard(edgemask(direction));
//	printf("%d",( (currentboard ^= edgemask(direction)) >> tomove)&1);
	return ((edgemask(direction)) >> tomove) ^ 1;
}

int squaresempty(board_t currentboard, int tomove, direction_t direction)
{
//checks if squares are empty (and move was possible), returns 1 or 0
//	printf("squaresempty\n");
//	printboard(currentboard);
//	printf("mask:\n");
//	printboard(isemptymask(direction, tomove));
//	printf("combined:\n");
//	printboard(isemptymask(direction, tomove) | currentboard);
//	printboard(isemptymask(direction, tomove) ^ currentboard);
	


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

// BIG PROBLEM HERE!
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
//	printf("direction called\n");
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
// adds currentboard to the table
// checking may be redundant, depending on our implementation.
//	printf("checking hash\n");
	if (checkhash(currentboard) != NULL)
		return;

		int h = hash(currentboard);
		List_t *newlist = malloc(sizeof(List_t));
//		printf("trying to hashtable");
		if (!newlist){
			printf("malloc no workie");
			return;	
		}
//		printf("still trying...\n");
		newlist->board = currentboard;

		newlist->next = table[h];
		table[h] = newlist;
//		printf("table[%d] set to %d\n", h, (int)newlist);
}

void add2solution(board_t currentboard)
{
/*	for (int i = 0; i < 35; i++){
		if (solution[i] == NULL){
			solution[i] = currentboard;
			return;	
		}
	}
*/
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
