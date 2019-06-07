//submit this file ONLY
//you must make sure your code can be compiled with the given main.cpp and gomoku.h in our official compilation environment

//there is no need to include anything else
#include "gomoku.h"

//you are NOT allowed to use any global variable
//but you may define your own helper function that aids your implementation

//you are NOT allowed to create/define any (static or dynamic) array structure in any function other than
//the createBoard function in which you definitely need to create a dynamic array of linked lists

Cell** createBoard(int height, int width)
{
    //the following is just a dummy implementation, change it
    Cell** cellRowHeads = new Cell* [height];
    for(int i = 0; i < height; i++){
      cellRowHeads[i] = new Cell;
      Cell* cellBefore = cellRowHeads[i];
      for(int j = 1; j < width; j++){
        // Cell* nextCellInRow = new Cell;
        cellBefore->next = new Cell;
        cellBefore = cellBefore->next;
      }
    }
    return cellRowHeads;
}

bool isBoardFull(Cell **cellRowHeads, int height, int width)
{
    //the following is just a dummy implementation, change it
    for(int i = 0; i < height; i++){
      Cell* cellBefore = cellRowHeads[i];
      for(int j = 0; j < width; j++){
        if(cellBefore->content == '.') return false;
        cellBefore = cellBefore->next;
      }
    }
    return true ;
}

bool move(char playerSymbol, int row, int col, Cell** cellRowHeads, int height, int width)
{
    //the following is just a dummy implementation, change it
    if(row < 1 || col < 1 || row > height || col > width) return false;
    Cell* cellBefore = cellRowHeads[row-1];
    for(int i = 1; i < col; i++){
      cellBefore = cellBefore->next;
    }
    if(cellBefore->content == '.'){
      cellBefore->content = playerSymbol;
      return true;
    }
    return false;
}
char checkHorizontal(Cell** cellRowHeads, int height, int width)
{
    //the following is just a dummy implementation, change it
    for(int i = 0; i < height; i++){
      Cell* cellBefore = cellRowHeads[i];
      char characterInBoard = cellRowHeads[i]->content;
      int counter = characterInBoard == 'X' || characterInBoard == 'O' ? 1 : 0;
      for(int j = 1; j < width; j++){
        cellBefore = cellBefore->next;
        if(cellBefore->content == characterInBoard){
          counter++;
        }
        else{
          counter = 0;
          characterInBoard = cellBefore->content;
        }

        if(counter == 5 && characterInBoard != '.'){
          return characterInBoard;
        }
      }
    }
    return '\0';
}

char checkVertical(Cell **cellRowHeads, int height, int width)
{
    //the following is just a dummy implementation, change it
    for(int i = 0; i < width; i++){
      char characterInBoard = 'X';
      int counter = 0;
      for(int j = 0; j < height; j++){
        Cell* cellRow = cellRowHeads[j];
        for(int k = 0; k < i; k++, cellRow = cellRow->next);
        if(cellRow->content == characterInBoard){
          counter++;
        }
        else{
          counter = 1;
          characterInBoard = cellRow->content;
        }

        if(counter == 5 && characterInBoard != '.') return characterInBoard;
      }
    }
    return '\0';
}

char checkDiagonal(Cell **cellRowHeads, int height, int width)
{
    //the following is just a dummy implementation, change it
    //Diagonal
    int counterWidth = 5;
    for(int i = height - 5; i >= 0; i--){
      char characterInBoard = 'X';
      int counter = 0;
      for(int j = 0; j < counterWidth; j++){
        int counterDiagonal = 0;
        Cell* cellBefore;
        for(cellBefore = cellRowHeads[i + j]; counterDiagonal < j; counterDiagonal++, cellBefore = cellBefore->next);
        if(cellBefore->content == characterInBoard) counter++;
        else{
          counter = 1;
          characterInBoard = cellBefore->content;
        }
        if(counter == 5 && characterInBoard != '.') return characterInBoard;
      }
      if(counterWidth < width) counterWidth++;
    }

    int counterHeight = 5;
    for(int i = width - 5; i >= 0; i--){
      char characterInBoard = 'X';
      int counter = 0;
      Cell* cellBefore;
      for(int j = 0; j < counterHeight; j++){
        cellBefore = cellRowHeads[j];
        for(int k = 0; k < i + j; k++, cellBefore = cellBefore->next);
        if(characterInBoard == cellBefore->content) counter++;
        else{
          counter = 1;
          characterInBoard = cellBefore->content;
        }
        if(counter == 5 && characterInBoard != '.') return characterInBoard;
      }
      if(counterHeight < height) counterHeight++;
    }

    //Anti diagonal
    counterHeight = 5;
    for(int i = width - 5; i >= 0; i--){
      char characterInBoard = 'X';
      int counter = 0;
      Cell* cellBefore;
      for(int j = 0; j < counterHeight; j++){
        cellBefore = cellRowHeads[height-1-j];
        for(int k = 0; k < i + j; k++, cellBefore = cellBefore->next);
        if(characterInBoard == cellBefore->content) counter++;
        else{
          counter = 1;
          characterInBoard = cellBefore->content;
        }
        if(counter == 5 && characterInBoard != '.') return characterInBoard;
      }
      if(counterHeight < height) counterHeight++;
    }

    counterWidth = 5;
    for(int i = 4; i < height; i++){
      char characterInBoard = cellRowHeads[i]->content;
      int counter = characterInBoard == 'X' || characterInBoard == 'O' ? 1 : 0;
      for(int j = 1; j < counterWidth; j++){
        int counterDiagonal = 0;
        Cell* cellBefore;
        for(cellBefore = cellRowHeads[i - j]; counterDiagonal < j; counterDiagonal++, cellBefore = cellBefore->next);
        if(cellBefore->content == characterInBoard) counter++;
        else{
          counter = 1;
          characterInBoard = cellBefore->content;
        }
        if(counter == 5 && characterInBoard != '.') return characterInBoard;
      }
      if(counterWidth < width) counterWidth++;
    }

    return '\0';
}

void deleteBoard(Cell **cellRowHeads, int height)
{
    //the following is just a dummy implementation, change it
    for(int i = 0; i < height; i++){
      Cell* cellBefore = cellRowHeads[i];
      while(cellRowHeads[i]->next != nullptr){
        while((cellBefore->next)->next != nullptr){
          cellBefore = cellBefore->next;
        }
        delete cellBefore->next;
        cellBefore->next = nullptr;
        cellBefore = cellRowHeads[i];
      }
    }
    for(int i = height-1 ; i >= 0; i--){
      delete cellRowHeads[i];
      cellRowHeads[i] = nullptr;
    }
    delete [] cellRowHeads;
    cellRowHeads = nullptr;
    return;
}
