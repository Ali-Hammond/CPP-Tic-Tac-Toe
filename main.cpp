#include <iostream>
#include <string>

using namespace std;

/*
If you want to see this file with no comments, refer to mainNoComments.cpp
I decided to comment the hell out of this file so if anyone else is trying to learn some basic C++ things like me, you can (hopefully) understand what's-
going on here and why
Feel free to take this code (or the uncommented code in mainNoComments.cpp) and do whatever with it, I don't care
I also left the .vscode folders' c_cpp_properties.json/tasks.json in the push so you can see what I'm using to compile it (I'm on Linux)
If you are having trouble understanding the board/array layout, think of it like this:

|col|col|col|
| 0 | 1 | 2 | 
|___|___|___|___
|   |   |   |row
| X | O |   | 0
|___|___|___|___
|   |   |   |row
|   | X |   | 1
|___|___|___|___
|   |   |   |row
| X | O | O | 2
|___|___|___|___
*/

int main() {
    // Create a 3x3 board array with blank starting values in each spot
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    // Assign players to their characters
    // Since X goes first in tic-tac-toe, set the currentPlayer to playerX, and switch it back and forth later
    const char playerX = 'X';
    const char playerO = 'O';
    char currentPlayer = playerX;

    // Assign ints for the player to choose a row (r) and column (c) to place their marker inside
    // Default is negative 1, so we can know if the player actually chose a column or did nothing
    int r = -1;
    int c = -1;

    // Assign the winner, which by default is nobody (blank)
    char winner = ' ';

    /*
    Print the board and do the game logic
    Alongside printing lines like "_" and "|" to make the board look like a real board, we print the index of each point in the array to show the chars-
    Ex: board[0][0] would be the top left, board[0][1] would be the top middle, and board[0][2] would be the top right
    The first number when getting a point in the array is the line, and the 2nd number is the spot, so board[1][2] would be middle row middle
    I also have it end the line after each array row, so it wraps downwards like an actual board
    Finally, do a for loop. There are 9 tiles, which means 9 turns. We want to stop the game when 9 turns have been passed
    So we do i = 0 for no turns/init/start, then while i < 9, we increment it by 1 (turn), and print the new board
    */
    for (int i = 0; i < 9; i++) {
        cout << "   |   |   " << endl; // Top two lines for design, technically they aren't needed but it helps the characters look centered in a box
        cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl; // First row with line spacers between
        cout << "___|___|___" << endl; // Board lines for top/middle
        cout << "   |   |   " << endl; // Vertical lines to give the center columns more space for the X's and O's
        cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl; // Second row with line spacers between
        cout << "___|___|___" << endl; // Board lines for middle/bottom
        cout << "   |   |   " <<endl; // Vertical lines to give the bottom columns more space for the X's and O's
        cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl; // Third row with line spacers between
        cout << "   |   |   " << endl; // Bottom two lines for design, technically they aren't needed but it helps the characters look centered in a box

        // Check if there is a winner
        // If the winner is not equal to a blank, meaning it has a new value, then there is a winner and we will break out of this for loop to stop asking for input
        if (winner != ' ') {
            break;
        }

        // Get the players input
        cout << "Current Player is: " << currentPlayer << endl;
        while (true) {
            cout << "Enter r c from 0-2 for row and column: ";
            cin >> r >> c;

            // Check if the players input was valid (below 0, above 2 for r and c)
            if (r < 0 || r > 2 || c < 0 || c > 2) {
                cout << "Invalid Input. Try again." << endl;
            }

            // Check if the array they pointed to already contains a value by checking if the given array point is not empty
            else if (board[r][c] != ' ') {
                cout << "Tile is already occupied, try again." << endl;
            }
            else {
                break;
            }
            // Reset the r and c values
            r = -1;
            c = -1;
            cin.clear(); // Clear error flags, so if they put a character that is not an integer the console does not spam/errors from not being able to assign-
            // a non-int to an int get cleared
            cin.ignore(1000, '\n'); // Now we discard those values, and skip to the new next line (up to 10000 char) already in the input stream
        }

        /*
        Now set the r and c they selected and set it equal to the currentPlayer
        So we are going to the exact position in the array that they provided, and setting it equal to their character
        Ex: player enters 0 0 -> board[r][c] becomes board[0][0] = 'X'; which the X switches to O (or vice versa) depending on who-
        currentPlayer is, and it draws X's and O's because currentPlayer always equals playerX or playerO, which is assigned to the char X or O
        */
        board[r][c] = currentPlayer;

        /*
        Now switch the currentPlayer by checking to see if the currentPlayer is playerX, if it is, we switch to playerO. if it's playerO, we switch to playerX
        The question mark is a ternary operator, essentially an in-line if/else statement
        Ex: condition ? expressionIfTrue : expressionIfFalse;
        */
        currentPlayer = (currentPlayer == playerX) ? playerO : playerX;

        /*
        Check for a winner (horizontally)
        We create a new int r = 0 (this one is constrained to this for loop, and is not the same as the r int from above inside board[r][c])
        Since you need 3 in a row to win, we do a for loop, so while r < 3, we increment it by 1 and check again
        On the first iteration, r = 0 as said above, this will check the entirety of row 0, once it gets incremented, it will check row 1, and again for row 2
        First, we check if the rows' column 0 is not empty, if it is not then there is either an X or an O, meaning this row could contain a winning sequence
        We then check if the rows' column 0 equals the rows' column 1, and then if the rows' column 1 equals the rows' column 2, meaning they are all the same-
        and it is a valid horizontal win sequence 
        */
        for (int r = 0; r < 3; r++) {
            if (board[r][0] != ' ' && board[r][0] == board[r][1] && board[r][1] == board[r][2]) {
                // If we reach here, then the above conditions are true, so we assign the winner to whatever value is in that column index (X or O)
                winner = board[r][0];
                // We also break when a match has been found, instead of continuing on checking other rows. If there is a win in row 0, there's no point-
                // to checking row 1. Same if there was a win in row 1, there's no point in checking row 2
                break;
            }
        }

        /*
        Check for a winner (Vertically)
        This is essentially "identical" to the above horizontal case. The main difference is that instead of keeping the row index the same and changing-
        the column, we keep the column index the same and check each row in that column
        We create a new int c = 0, which is also constrained to this loop. Again, since you need 3 in a row to win, we do a for loop so while c < 3, we-
        increment it by 1 and check again
        On the first iteration, c = 0 as said above, this will check the entirety of of col 0. Once it gets incremented, it will check col 1, and again for col 2
        First, we check if the cols' row is not empty. If it is not then there is either an X or an O, meaning this could contain a winning sequence
        We then check if the cols' row 0 equals the cols' row 1, and then if the cols' row 1 equals the cols' row 2, meaning they are all the same and it is a-
        valid vertical win sequence
        */
        for (int c = 0; c < 3; c++) {
            if (board[0][c] != ' ' && board[0][c] == board[1][c] && board[1][c] == board[2][c]) {
                // If we reach here, then the above conditions are true, so we assign the winner to whatever value is in that column index (X or O)
                winner = board[0][c];
                // We still break when a match has been found, instead of checking other columns. This is because if there is a win in col 0, there's no point-
                // to checking col 1. Same if there was a win in col 1, there's no point in checking col 2
                break;
            }
        }

        /*
        Check for a winner (diagonal from top left to bottom right)
        This check is a bit easier, as we don't use a for loop. Since there can only be 2 winning diagonals in a game of tic-tac-toe, we can just check-
        specific arrays directly
        First, we check if the first array point, row 0 col 0, is not empty. If it is not then there is either an X or an O, meaning this could contain a-
        winning sequence
        We then check if row 0 col 0 is equal to the next diagonal point, row 1 col 1, and then if row 1 col 1 is equal to the next diagonal point, row 2 col 2
        If they are all equal, that means we have a valid top left diagonal win sequence
        */
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            // If we reach here, then the above conditions are true, so we assign the winner to whatever value is in that row/cols' index (X or O)
            winner = board[0][0];
            // We don't break here because this is not a for loop
        }
        /*
        Check for a winner (diagonal from top right to bottom left)
        This is essentially "identical" to the above top left to bottom right check. The main difference being that instead of starting from the top left-
        and working towards the bottom right, we are starting from the top right and working towards the bottom left
        First, we check if the first array point, row 0 col 2, is not empty. If it is not then there is either an X or an O, meaning this could contain a-
        winning sequence
        We then check if row 0 col 2 is equal to the next diagonal point, row 1 col 1, and then if row 1 col 1 is equal to the next diagonal point, row 2 col 0
        If they are all equal, that means we have a valid top right diagonal win sequence
        */
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            // If we reach here, then the above conditions are true, so we assign the winner to whatever value is in the row/cols' index (X or O)
            winner = board[0][2];
            // Again, we don't break here because this isn't a for loop
        }
    }

    /*
    After the game has ended (outside of the main for loop)
    First we check if the winner is not equal to a blank
    If it is not a blank, that means someone won, and we can print winner to show who has won
    If it is a blank, that means nobody won, and we can inform them it was a tie
    */
    if (winner != ' ') {
        cout << "Player" << winner << " is the winner!" << endl;
    }
    else {
        cout << "It was a tie! No one wins!" << endl;
    }
}
