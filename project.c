/* ENGGEN131 Project - C Project - 2019 */
/* The Warehouse */

/* Name - Henry Man, username - hman845, ID Number - 352599063 */

#include "project.h"

/* Helper function declarations */
int FindIndex(int warehouse[10][10], int tileType, int* row, int* col);
int AdjacentTile(int warehouse[10][10], int row, int col, char direction);
void MoveItem(int warehouse[10][10], int row, int col, int tileType, char move);

/*
TimeWorked is used to calculate the total time worked, in seconds, by a worker durin their shift.

This is done by first converting the amount of minutes worked into seconds (mins * 60) and then summing
that with the number of seconds worked for both the clock in and clock out times. The total time worked
will then be the difference between these times
*/
int TimeWorked(int minuteA, int secondA, int minuteB, int secondB)
{
	int timeA = (minuteA * 60) + secondA;
	int timeB = (minuteB * 60) + secondB;
	int totalTime = timeA - timeB;

	if (totalTime < 0) {//Converts time difference to positive if < 0
		totalTime *= -1;
	}

	return totalTime;
}

/*
WarehouseAddress is used to find the largest prime number which is less than the maximum parameter

This is done by dividing all numbers less than the maximum by integers between 2 and the number being tested
until either the number has been reached or a factor of that number has been reached. If a factor has been reached,
then the number is not prime and will check the next number, if a factor has not been found, then the number is prime
and is returned

e.g. Checking 99; dividing 99 by all numbers from 2-99. 99/3 is 33, therefore it does not reach 99 and 99 is not a prime
	 Checking 47; dividing 47 by all numbers from 2-47. There are no factors of 47 so the final number reached is 47
				  therefore 47 is a prime and is returned
*/
int WarehouseAddress(int maximum)
{
	int i;
	int j = 2;
	int prime = 0;

	for (i = maximum - 1; i > 0; i--) {
		j = 2;
		while ((j < i) && (i % j != 0)) {
			//Increments j if the number being checked is not divisible by j and less than the number
			j++;
		}

		if (i == j) {
			//The number must be prime if j is equal to the number in question
			prime = i;
			break;
		}
	}
	return prime;
}

/*
Advertise is used to shift all the characters in a string one position to the left
with the first letter wrapping back to the end

This is done using a loop which sets the character in the current index (i.e. i) to the character in the
next index up (i.e. i + 1). The first character will be stored separately and later set to the last character
in the string
*/
void Advertise(char* words)
{
	int i;
	char firstChar = words[0];
	int numChars = strlen(words);

	for (i = 0; i < numChars; i++) {
		words[i] = words[i + 1];
	}

	words[numChars - 1] = firstChar; //Places first character at the end of the string
}

/*
WinningBid is used to find the lowest unique bid in a set of customer bids to determine the winner of the auction

This is done by searching through the array and comparing each number and counting the number of repeated numbers
If a repeated number is found (and it is not 0), all occurences are set 0 zero. This will isolate all the unique numbers
in the array. Then the lowest of these unique numbers is found and returned. If there are no unique numbers then -1 is returned
*/
int WinningBid(int* values, int length)
{
	int i, j, found, winningBid;
	int count = 0;
	int uniqueBids[MAX_ARRAY_SIZE];//Stores 

	for (i = 0; i < length; i++) {
		found = 0; //Number of repeated occurences found
		for (j = i + 1; j < length; j++) {
			if ((values[i] == values[j]) && values[i] != 0) {
				values[j] = 0;//Sets repeated numbers to 0
				found++;
			}
		}
		if (found != 0) {//Sets initial value being checked to 0 if multiple occurences are found
			values[i] = 0;
		}
		if (values[i] != 0) {
			uniqueBids[count] = values[i];//Copies and stores all unique numbers in new array
			count++;
		}
	}

	if (count > 0) {
		winningBid = uniqueBids[0];
		for (i = 1; i < count; i++) {//Finds the lowest value in the array
			if (uniqueBids[i] < winningBid) {
				winningBid = uniqueBids[i];
			}
		}
		return winningBid;
	}

	return -1;
}

/*
BoxDesign is used to generate a side view of a box of dimensions width x height and places a set of X's
in the center representing the area where it is easiest to move when pushed

This is done by first generating a 2d array which maps out the sides and empty spaces of the box first.
Then the X's are placed in the center of the box by replacing the space characters at the center of the 2d array,
the midpoint is dependent on the dimensions of the box. After the X's have been placed, the 2d array is then translated
back into a 1d array.
*/
void BoxDesign(char* design, int width, int height)
{
	int row, col;
	int midHeight = (height-1) / 2;
	int midWidth = (width-1) / 2;
	int count = 0;
	char mapArray[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];

	/* Creates 2d array mapping out the box */
	for (row = 0; row < height; row++) {
		for (col = 1; col <= width; col++) {
			mapArray[row][0] = '*';
			if ((row == 0 || row == height - 1) && col != width - 1) {
				mapArray[row][col] = '*';
			}
			else {
				mapArray[row][col] = ' ';
			}
			mapArray[row][width - 1] = '*';
			mapArray[row][width] = '\n';
		}
	}

	/* Places the X's inside the boxed area*/
	if ((width > 2) && (height > 2)) {
		if ((width % 2 != 0) && (height % 2 == 0)) {//odd width, even height
			mapArray[midHeight][midWidth] = 'X';
			mapArray[midHeight + 1][midWidth] = 'X';
		}
		else if ((width % 2 == 0) && (height % 2 != 0)) {//even width, odd height
			mapArray[midHeight][midWidth] = 'X';
			mapArray[midHeight][midWidth + 1] = 'X';
		}
		else if ((width % 2 == 0) && (height % 2 == 0)) {//even width, even height
			mapArray[midHeight][midWidth] = 'X';
			mapArray[midHeight][midWidth + 1] = 'X';
			mapArray[midHeight + 1][midWidth] = 'X';
			mapArray[midHeight + 1][midWidth + 1] = 'X';
		}
		else {//odd width, odd height
			mapArray[midHeight][midWidth] = 'X';
		}
	}
	
	/* Translates 2d array into 1d array */
	for (row = 0; row < height; row++) {
		for (col = 0; col <= width; col++) {
			design[count] = mapArray[row][col];
			count++;
		}
	}
}

/*
Worker Route is used to find a direct route between the worker and the box.

This is done by first locating the position of both the worker and the box within the 2d array.
Then calculates the number of moves required in both the vertical and horizontal directions and then 
changes the corresponding 0's in the path with 3's.
*/
void WorkerRoute(int warehouse[10][10])
{
	int i, rowWorker, colWorker, rowBox, colBox;
	/* Locate the position of worker and box */
	FindIndex(warehouse, 1, &rowWorker, &colWorker);
	FindIndex(warehouse, 2, &rowBox, &colBox);

	/* Number of steps to move in horizontal and vertical direction*/
	int horizontalMove = colWorker - colBox;
	int verticalMove = rowWorker - rowBox;

	/* Converts number to positive if it is negative */
	if (horizontalMove < 0) {
		horizontalMove *= -1;
	}
	if (verticalMove < 0) {
		verticalMove *= -1;
	}

	/* Changes all 0's in the horizontal path */
	if (verticalMove != 0) {
		for (i = 1; i <= horizontalMove; i++) {
			if (colWorker > colBox) {
				warehouse[rowWorker][colWorker - i] = 3;
			} else  {
				warehouse[rowWorker][colWorker + i] = 3;
			}
		}
	} else if ((verticalMove == 0 && horizontalMove > 0)) {
		for (i = 1; i < horizontalMove; i++) {
			if (colWorker > colBox) {
				warehouse[rowWorker][colWorker - i] = 3;
			}
			else {
				warehouse[rowWorker][colWorker + i] = 3;
			}
		}
	}

	/* Changes all 0's in the vertical path */
	if (verticalMove > 1) {
		for (i = 1; i < verticalMove; i++) {
			if (rowBox > rowWorker) {
				warehouse[rowBox - i][colBox] = 3;
			} else {
				warehouse[rowBox + i][colBox] = 3;
			}
		}
	}
}

/*
MakeMove moves the worker in the direction specified by the user if a valid move is possible

This is done by first locating the worker's row/column using the FindIndex function. Then various moves are carried out
depending on what tiles are adjacent to the worker tile. 
	- If the worker is to move in a direction with an open space, then the worker is moved 1 position in that direction. 
	- If the worker is to move in a direction with a box in front, the the worker moves if there is no other obstacle blocking
	  the box in that direction
	- If the worker is next to a wall or cannot move the box, nothing happens
*/
int MakeMove(int warehouse[10][10], char move)
{
	int rowWorker, colWorker;
	/* Locates the position of the worker*/
	if (FindIndex(warehouse, WORKER, &rowWorker, &colWorker) == 0) {
		FindIndex(warehouse, WORKER_ON_TARGET, &rowWorker, &colWorker);
	}

	if (AdjacentTile(warehouse, rowWorker, colWorker, move) == SPACE) {
		/* Actions to take if worker next to a space */

		/* Changes worker's current tile after move depending on what type of tile they are currently on */
		if (warehouse[rowWorker][colWorker] == WORKER_ON_TARGET) {
			warehouse[rowWorker][colWorker] = TARGET;
		} else { 
			warehouse[rowWorker][colWorker] = SPACE;
		}
		/* Moves the worker */
		MoveItem(warehouse, rowWorker, colWorker, WORKER, move);

	} else if (AdjacentTile(warehouse, rowWorker, colWorker, move) == TARGET) {
		/* Actions to take if the worker is next to a target */
		if (warehouse[rowWorker][colWorker] == WORKER_ON_TARGET) {
			warehouse[rowWorker][colWorker] = TARGET;
		} else { 
			warehouse[rowWorker][colWorker] = SPACE;
		}

		MoveItem(warehouse, rowWorker, colWorker, WORKER_ON_TARGET, move);


	} else if (AdjacentTile(warehouse, rowWorker, colWorker, move) == BOX || AdjacentTile(warehouse, rowWorker, colWorker, move) == BOX_ON_TARGET) {
		/* Actions to take if the worker is next to a box or a box on top of a target */
		int rowBox = rowWorker;
		int colBox = colWorker;

		/* Adjusts the box's row/column depending on position of worker*/
		if (move == 'w') {
			rowBox --;
		} else if (move == 'a') {
			colBox--;
		} else if (move == 's') {
			rowBox++;
		} else {
			colBox++;
		}

		if (AdjacentTile(warehouse, rowBox, colBox, move) == SPACE) {
			/* Moves to make if the box is next to a space */

			/* Changes box's current tile after move depending on what type of tile they are currently on */
			if (warehouse[rowBox][colBox] == BOX) { //If the box is not on a target
				/* Replaces worker's current tile after move depending on what the worker is sitting on */
				if (warehouse[rowWorker][colWorker] == WORKER_ON_TARGET) {
					warehouse[rowWorker][colWorker] = TARGET;
				} else {
					warehouse[rowWorker][colWorker] = SPACE;
				}
				MoveItem(warehouse, rowWorker, colWorker, WORKER, move);
				MoveItem(warehouse, rowBox, colBox, BOX, move);
			} else if (warehouse[rowBox][colBox] == BOX_ON_TARGET) { //If the box is on a target
				if (warehouse[rowWorker][colWorker] == WORKER_ON_TARGET) {
					warehouse[rowWorker][colWorker] = TARGET;
				} else {
					warehouse[rowWorker][colWorker] = SPACE;
				}
				MoveItem(warehouse, rowWorker, colWorker, WORKER_ON_TARGET, move);
				MoveItem(warehouse, rowBox, colBox, BOX, move);
			}
		} else if (AdjacentTile(warehouse, rowBox, colBox, move) == TARGET) {
			/* Moves to make if the box is next to a space */

			/* Changes box's current tile after move depending on what type of tile they are currently on */
			if (warehouse[rowBox][colBox] == BOX) {
				if (warehouse[rowWorker][colWorker] == WORKER_ON_TARGET) {
					warehouse[rowWorker][colWorker] = TARGET;
				} else {
					warehouse[rowWorker][colWorker] = SPACE;
				}
				MoveItem(warehouse, rowWorker, colWorker, WORKER, move);
				MoveItem(warehouse, rowBox, colBox, BOX_ON_TARGET, move);
			}
			else if (warehouse[rowBox][colBox] == BOX_ON_TARGET) {
				if (warehouse[rowWorker][colWorker] == WORKER_ON_TARGET) {
					warehouse[rowWorker][colWorker] = TARGET;
				} else {
					warehouse[rowWorker][colWorker] = SPACE;
				}
				MoveItem(warehouse, rowWorker, colWorker, WORKER_ON_TARGET, move);
				MoveItem(warehouse, rowBox, colBox, BOX_ON_TARGET, move);
			}
		}
	}
	int row, col;
	/* Searches the board for a target space. Returns 1 if there are none found*/
	return (!FindIndex(warehouse, TARGET, &row, &col) && FindIndex(warehouse, WORKER_ON_TARGET, &row, &col)); 
}

/* 
FindIndex searches for the row/column of a particular function

This is done by going through each index of the 2D warehouse array until one of the correct tileType is found
*/
int FindIndex(int warehouse[10][10], int tileType, int* row, int* col)
{
	int i, j;

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (warehouse[i][j] == tileType) {
				*row = i;
				*col = j;
				return 1;
			}
		}
	}
	return 0;
}

/*
AdjacentTile is used to check what type of tiles are adjacent to a particular tile

This is done by returning the tile type which is found in the tile adjacent to the one specified in
a given direction (e.g. w = up, a = left, s = down.. etc.)
*/
int AdjacentTile(int warehouse[10][10], int row, int col, char direction)
{
	if (direction == 'w') {
		return warehouse[row - 1][col];
	} else if (direction == 'a') {
		return warehouse[row][col - 1];
	} else if (direction == 's') {
		return warehouse[row + 1][col];
	} else {
		return warehouse[row][col + 1];
	}
}

/*
MoveItem is used to move a tile to an adjacent space on the board

This is done by changing the value in the adjacent space in the direction specified using a row & col given
The space is updated to be the tileType specified.
*/
void MoveItem(int warehouse[10][10], int row, int col, int tileType, char direction)
{
	if (direction == 'w') {
		warehouse[row - 1][col] = tileType;
	} else if (direction == 'a') {
		warehouse[row][col - 1] = tileType;
	} else if (direction == 's') {
		warehouse[row + 1][col] = tileType;
	} else {
		warehouse[row][col + 1] = tileType;
	}
}