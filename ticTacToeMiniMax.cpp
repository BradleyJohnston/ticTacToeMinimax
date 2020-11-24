// ticTacToeMiniMax.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

using namespace std;

#include <iostream> // cout
#include <iomanip>  // setw
#include <string>   // string
#include <stdlib.h> // atoi/tolower

void clearBoard(char board[][3]);
void displayBoard(char board[][3]);
bool getPlayerInput(char board[][3]);
bool isDraw(char board[][3]); 
int getBoardScore(char board[][3]);
void doOpponentTurn(char board[][3]);
int minimax(char board[][3], bool isPlayerO);
void displayWinner(char board[][3]);

int main()
{
    // This is the container for the board
    char board[3][3];

    // Set things up
    clearBoard(board);
    displayBoard(board);

    // Game loop
    while (getBoardScore(board) == 0 && !isDraw(board))
    {
        // Player turn
        // Get a valid input
        while(!getPlayerInput(board));
        displayBoard(board);

        // Opponent turn
        doOpponentTurn(board);
        displayBoard(board);
    }

    // Closing up
    displayWinner(board);
}

/*
Set every value to a uniform value, ensuring
that that value is not 'X' or 'O'
*/
void clearBoard(char board[][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

/*
Loop through the game board and display
the contents to the user in an appealing way
*/
void displayBoard(char board[][3])
{
    cout << endl << endl;
    // Display header
    cout << "   A   B   C" << endl;
    
    // Row
    for (int i = 0; i < 3; i++)
    {
        // Display col numbering
        cout << i + 1 << setw(3);

        // Col
        for (int j = 0; j < 2; j++)
        {
            cout << board[i][j] << setw(2) << "|" << setw(2);
        }
        cout << board[i][2] << endl;
        
        // Display in between line
        if (i != 2)
        {
            cout << "  ---+---+---" << endl;
        }
    }

    cout << endl << endl;
}

/*
Get user input and set the desired position
with their piece
*/
bool getPlayerInput(char board[][3])
{
    // Set up variables
    string input;
    int row = 0;
    int col = 0;

    // Get user input
    cout << "What square: ";
    cin >> input;

    // Parse row
    switch (tolower(input[0]))
    {
    case 'a':
        row = 0;
        break;
    case 'b':
        row = 1;
        break;
    case 'c':
        row = 2;
        break;
    default:
        cout << "Incorrect input" << endl;
        return false;
        break;
    }

    // Convert char to ascii int, then subtract 49 to get col value
    col = ((int)input[1]) - 49;
    if (col > 2 || col < 0)
    {
        return false;
    }

    // Set player value
    if (board[col][row] == ' ')
    {
        board[col][row] = 'X';
    }
    else
    {
        cout << "That square is taken" << endl;
        return false;
    }

    return true;
}

/*
This function determines if the game is a draw
*/
bool isDraw(char board[][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }

    return true;
}

/*
Determine if a player has won the game
1 signifies 'X' has won
0 signifies inconclusive or draw
-1 signifies 'O' has won
*/
int getBoardScore(char board[][3])
{
    // Get horizontal win
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][0] == board[i][2] &&
            board[i][0] != ' ')
        {
            return (board[i][0] == 'X' ? 1 : -1);
        }
    }

    // Get vertical win
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] &&
            board[0][i] == board[2][i] &&
            board[0][i] != ' ')
        {
            return (board[0][i] == 'X' ? 1 : -1);
        }
    }

    // Get diagnol win
    if (board[0][0] == board[1][1] &&
        board[0][0] == board[2][2] &&
        board[0][0] != ' ')
    {
        return (board[0][0] == 'X' ? 1 : -1);
    }
    if (board[2][0] == board[1][1] &&
        board[2][0] == board[0][2] &&
        board[2][0] != ' ')
    {
        return (board[2][0] == 'X' ? 1 : -1);
    }

    return 0;
}

/*
This function sets up for the minimax
algorithm, calls it and does the opponent's
optimal move
*/
void doOpponentTurn(char board[][3])
{
    if (isDraw(board) || getBoardScore(board) != 0)
    {
        return;
    }

    // Set up some variables we will need
    int highScore = 2;
    int bestX = 0;
    int bestY = 0;
    int score = 0;

    // Row
    for (int i = 0; i < 3; i++)
    {
        // Col
        for (int j = 0; j < 3; j++)
        {
            // If the square is playable
            if (board[i][j] == ' ')
            {
                // Test this option
                board[i][j] = 'O';
                score = minimax(board, false);

                // If the move is good, then save it
                if (score < highScore)
                {
                    cerr << "Score: " << score << endl;
                    highScore = score;
                    bestX = i;
                    bestY = j;
                }

                // Clean up the mess
                board[i][j] = ' ';
            }
        }
    }

    // Set the opponent's best move
    board[bestX][bestY] = 'O';
    cerr << "Best move: " << highScore << endl;
}

/*
This is a recursive algorithm where we test every possible
move and get the best move. Then we test
the opponents moves, on and on till we run out of moves
or win/lose
*/
int minimax(char board[][3], bool isPlayerO)
{
    // Set up some variables that are needed
    int highScore = 0;
    int score = 0;

    if (getBoardScore(board) != 0)
    {
        return getBoardScore(board);
    }

    if (isDraw(board))
    {
        return getBoardScore(board);
    }

    // Determine opponent best move
    if (isPlayerO)
    {
        // Set the highscore to worse than the worst case scenario
        highScore = 2;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // If the square is empty
                if (board[i][j] == ' ')
                {
                    // Test this move
                    board[i][j] = 'O';
                    score = minimax(board, false);

                    // If the move is good, then save it
                    if (score < highScore)
                    {
                        highScore = score;
                    }

                    // Clean up the mess
                    board[i][j] = ' ';
                }
            }
        }
    }
    // Determine player best move
    else if (!isPlayerO)
    {
        // Set the highscore to worse than the worst case scenario
        highScore = -2;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    // Test the move
                    board[i][j] = 'X';
                    score = minimax(board, true);
                    
                    // If the move is good, then save it
                    if (score > highScore)
                    {
                        highScore = score;
                    }

                    // Clean up the mess
                    board[i][j] = ' ';
                }
            }
        }
    }

    return highScore;
}

/*
This function simply determines who won,
and displays that to the user
*/
void displayWinner(char board[][3])
{
    int winner = getBoardScore(board);
    switch (winner)
    {
    case -1:
        cout << "O has won" << endl;
        break;
    case 1:
        cout << "X has won" << endl;
        break;
    default:
        cout << "It was a draw" << endl;
        break;
    }
}
