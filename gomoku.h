//do NOT submit this file
//do NOT modify this file

#include <iostream>
using namespace std;

//a Cell on the board
struct Cell
{
    char content = '.'; //it is the Cell's content as shown on the board, should be either '.', 'X', or 'O'
    Cell* next = nullptr; //the next pointer that points to the next Cell in the same row, points to nullptr if it is the last cell in the row
};

//NOTE:
//For all the functions below, beside of their descriptions,
//you should also read the main.cpp to see how they are used
//that will help you understand what is expected from each of the function

//return the dynamic array of linked lists given the board height and width
//see the webpage for description of the linked lists
//in total, exactly height*width Cell objects will be created
Cell **createBoard(int height, int width);

//return whether the board is full or not
bool isBoardFull(Cell **cellRowHeads, int height, int width);

//put playerSymbol to the Cell's content at (row, col)
//if the given row or col is out-of-bound of the board, simply return false
//if the (row, col) is not empty (i.e. already occupied by some player), also return false
//return true at the end if the move can be made
bool move(char playerSymbol, int row, int col, Cell** cellRowHeads, int height, int width);

//return the player symbol of the player that has 5 consecutive pieces in a row
//if no such player is found (i.e. no one wins horizontally yet), simply return a null character, i.e., '\0'
char checkHorizontal(Cell **cellRowHeads, int height, int width);

//return the player symbol of the player that has 5 consecutive pieces in a column
//if no such player is found (i.e. no one wins vertically yet), simply return a null character, i.e., '\0'
char checkVertical(Cell **cellRowHeads, int height, int width);

//return the player symbol of the player that has 5 consecutive pieces in a diagonal or antidiagonal
//if no such player is found (i.e. no one wins diagonally yet), simply return a null character, i.e., '\0'
char checkDiagonal(Cell **cellRowHeads, int height, int width);

//deallocate all the dynamic memory allocated for the linked lists
//this function will be called just before the end of the program
//you should make sure there is no memory leak with this function
void deleteBoard(Cell **cellRowHeads, int height);
