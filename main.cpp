//do NOT submit this file
//do NOT modify this file

//there is no need to include anything else
#include "gomoku.h"

//get the choice within a specific bound
int getChoice(const char* message, int lowerBound, int upperBound)
{
    cout << message << " [" << lowerBound << "-" << upperBound << "]" << endl;
    int choice;
    cin >> choice;
    while(choice<lowerBound || choice>upperBound)
    {
        cout << "Invalid input. Try again." << endl;
        cin >> choice;
    };
    return choice;
}

//draw the board
void drawBoard(Cell** rows, int height, int width)
{
    cout << "  ";
    for (int j = 0; j < width; j++)
        cout << (j + 1) << " ";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        cout << (i + 1) << " ";
        Cell* cur = rows[i];
        while (cur)
        {
            cout << cur->content << " ";
            cur = cur->next;
        }
        cout << endl;
    }
}

//main entry point of the program
int main()
{
    //let's play!
    cout << "Let's play Gomoku! :)" << endl;
    cout << endl;

    //get the board size
    int height, width;
    cout << "Please enter the size of the board." << endl;
    height = getChoice("Height?", 5, 9);
    width = getChoice("Width?", 5, 9);

    //create the board
    Cell** cellRowHeads = createBoard(height, width);

    //current player, either 1 or 2
    int player = 1;

    //game goes until the board is full
    //unless a player wins, then the game will terminate early
    while (!isBoardFull(cellRowHeads, height, width))
    {
        //draw the board and have the current player move
        cout << endl;
        drawBoard(cellRowHeads, height, width);
        cout << endl;
        cout << "Player " << (player==1?'X':'O') << ", your turn! What's your move?" << endl;
        int row, col;
        do
        {
            cout << "Enter row and column. [1-" << height << "] [1-" << width << "]" << endl;
            cin >> row;
            cin >> col;
        }
        while( !move(player==1?'X':'O', row, col, cellRowHeads, height, width) );

        //check if the current player wins
        char hWin = checkHorizontal(cellRowHeads, height, width);
        char vWin = checkVertical(cellRowHeads, height, width);
        char dWin = checkDiagonal(cellRowHeads, height, width);
        if (hWin != 0 || vWin != 0 || dWin != 0)
        {
            cout << endl;
            drawBoard(cellRowHeads, height, width);
            cout << endl;

            cout << "Player " << player << " has won ";
            if(hWin!= 0)
                cout << "horizontally ";
            if (vWin != 0)
                cout << "vertically ";
            if (dWin != 0)
                cout << "diagonally ";
            cout << "!!!" << endl;

            deleteBoard(cellRowHeads, height);
            return 0;
        }

        //switch player
        player=player==1?2:1;
    }

    //draw game if the program reaches here
    cout << endl;
    drawBoard(cellRowHeads, height, width);
    cout << endl;
    cout << "DRAW!! @_@" << endl;
    deleteBoard(cellRowHeads, height);

    return 0;
}
