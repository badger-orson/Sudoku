/***********************************************************************
* Program:
*    Project 13, Sudoku
*    Brother Comeau, CS124
* Author:
*    Orson C Badger
* Summary:
*    This program lets you play sudoku
*
*    Estimated:  4.0 hrs
*    Actual:     12.0 hrs
*      The hardest part, was figuring out how to ask for coordinates.
************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

// Functions Prototyping
string getFile(char fileName[]);
void readFile(char fileName[], char board[9][9]);
void displayMenu();
void displayBoard(char board[9][9]);
string getCoordinates(int &row, int &col);
void editSquare(char board[9][9]);
void possibleValues(char board[9][9], char possibles[9], int row, int col);
bool computeValues(char board[9][9], int row, int col, int value);
string fixCoordinates(string coordinates);
void saveAndQuit(char board[9][9]);
void interact(char board[9][9]);
int main();


/**********************************************************************
* getFile()
* This is where I will read in a filename.
*********************************************************************/
string getFile(char fileName[])
{
   // Get the file info
   cout << "Where is your board located? ";
   cin >> fileName;
   
   return fileName;
   
}

/**********************************************************************
* readFile()
* This is where I will read the contents of the file located in the
* program.
*********************************************************************/
void readFile(char fileName[], char board[9][9])
{
   
   //Open the file
   ifstream fin(fileName);
   
   //check to see if it failed to read file
   if (fin.fail())
   {
      cerr << "Failed to read file with board.";
      return;
   }
   
   // Read the file.
   
   // read rows
   for (int row = 0; row <= 8; row++)
   {
      // read columns
      for (int column = 0; column < 9; column++)
      {
         fin >> board[row][column];
      }
   }
   
   // close the file
   fin.close();
}

/**********************************************************************
* displayMenu()
* This just displays the instructions which is this menu
*********************************************************************/
void displayMenu()
{
   cout << "Options:\n"
        << "   ?  Show these instructions\n"
        << "   D  Display the board\n"
        << "   E  Edit one square\n"
        << "   S  Show the possible values for a square\n"
        << "   Q  Save and Quit\n"
        << endl;
   
}

/**********************************************************************
* displayBoard()
* This is where the Filename and the Board are going to be displayed
*********************************************************************/
void displayBoard(char board[9][9])
{
   for (int row = 0; row < 9; row++)
   {
      for (int column = 0; column < 9 ; column++)
      {
         if (board[row][column] == '0')
         {
            board[row][column] = ' ';
         }
      }
   }
   
   cout << "   A B C D E F G H I\n"
        << "1  " << board[0][0] << " "
        << board[0][1] << " "
        << board[0][2] << "|"
        << board[0][3] << " "
        << board[0][4] << " "
        << board[0][5] << "|"
        << board[0][6] << " "
        << board[0][7] << " "
        << board[0][8] << endl
   
        << "2  " << board[1][0] << " "
        << board[1][1] << " "
        << board[1][2] << "|"
        << board[1][3] << " "
        << board[1][4] << " "
        << board[1][5] << "|"
        << board[1][6] << " "
        << board[1][7] << " "
        << board[1][8] << endl
   
        << "3  " << board[2][0] << " "
        << board[2][1] << " "
        << board[2][2] << "|"
        << board[2][3] << " "
        << board[2][4] << " "
        << board[2][5] << "|"
        << board[2][6] << " "
        << board[2][7] << " "
        << board[2][8] << endl
   
        << "   -----+-----+-----\n"
   
        << "4  " << board[3][0] << " "
        << board[3][1] << " "
        << board[3][2] << "|"
        << board[3][3] << " "
        << board[3][4] << " "
        << board[3][5] << "|"
        << board[3][6] << " "
        << board[3][7] << " "
        << board[3][8] << endl
   
        << "5  " << board[4][0] << " "
        << board[4][1] << " "
        << board[4][2] << "|"
        << board[4][3] << " "
        << board[4][4] << " "
        << board[4][5] << "|"
        << board[4][6] << " "
        << board[4][7] << " "
        << board[4][8] << endl
   
   
        << "6  " << board[5][0] << " "
        << board[5][1] << " "
        << board[5][2] << "|"
        << board[5][3] << " "
        << board[5][4] << " "
        << board[5][5] << "|"
        << board[5][6] << " "
        << board[5][7] << " "
        << board[5][8] << endl
   
        << "   -----+-----+-----\n"
   
        << "7  " << board[6][0] << " "
        << board[6][1] << " "
        << board[6][2] << "|"
        << board[6][3] << " "
        << board[6][4] << " "
        << board[6][5] << "|"
        << board[6][6] << " "
        << board[6][7] << " "
        << board[6][8] << endl
   
        << "8  " << board[7][0] << " "
        << board[7][1] << " "
        << board[7][2] << "|"
        << board[7][3] << " "
        << board[7][4] << " "
        << board[7][5] << "|"
        << board[7][6] << " "
        << board[7][7] << " "
        << board[7][8] << endl
   
        << "9  " << board[8][0] << " "
        << board[8][1] << " "
        << board[8][2] << "|"
        << board[8][3] << " "
        << board[8][4] << " "
        << board[8][5] << "|"
        << board[8][6] << " "
        << board[8][7] << " "
        << board[8][8] << endl;
   
}


/**********************************************************************
* possibleValues()
* Find the possible Values;
*********************************************************************/
void possibleValues(char board[9][9], char possibles[9], int row, 
                    int col, string coordinates)
{
   char temp[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
   possibles = temp;
   
   // check the col
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         if (board[i][col] == possibles[j])
         {
            possibles[j] = ' ';
            
         }
      }
   }
   
   // check the row
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         if (board[row][i] == possibles[j])
         {
            possibles[j] = ' ';
            
         }
      }
   }
   
   

   /*
            Board Coordinates

    00 01 02    03 04 05    06 07 08
    10 11 12    13 14 15    16 17 18
    20 21 22    23 24 25    26 27 28
    
    30 31 32    33 34 35    36 37 38
    40 41 42    43 44 45    46 47 48
    50 51 52    53 54 55    56 57 58
    
    60 61 62    63 64 65    66 67 68
    70 71 72    73 74 75    76 77 78
    80 81 82    83 84 85    86 87 88
    */

   // check the quadrant
   int quadrant;
   char snagValues[3][3];
   
   if ((row >= 0 && row <= 2) && (col >= 0 && col <= 2))
   {
      quadrant = 1;
      for (int i = 0; i <= 2; i++)
      {
         
         for (int j = 0; j <= 2; j++)
         {
            snagValues[i][j] = board[i][j];
         }
      }
   }
   else if ((row >= 0 && row <= 2) && (col >= 3 && col <= 5))
   {
      quadrant = 2;
      for (int i = 0; i <= 2; i++)
      {
         
         for (int j = 3; j <= 5; j++)
         {
            snagValues[i][j - 3] = board[i][j];
         }
      }
   }
   else if ((row >= 0 && row <= 2) && (col >= 6 && col <= 8))
   {
      quadrant = 3;
      for (int i = 0; i <= 2; i++)
      {
         
         for (int j = 6; j <= 8; j++)
         {
            snagValues[i][j - 6] = board[i][j];
         }
      }
   }
   if ((row >= 3 && row <= 5) && (col >= 0 && col <= 2))
   {
      quadrant = 4;
      for (int i = 3; i <= 5; i++)
      {
         
         for (int j = 0; j <= 2; j++)
         {
            snagValues[i - 3][j] = board[i][j];
         }
      }
   }
   else if ((row >= 3 && row <= 5) && (col >= 3 && col <= 5))
   {
      quadrant = 5;
      for (int i = 3; i <= 5; i++)
      {
         
         for (int j = 3; j <= 5; j++)
         {
            snagValues[i - 3][j - 3] = board[i][j];
         }
      }
   }
   else if ((row >= 3 && row <= 5) && (col >= 6 && col <= 8))
   {
      quadrant = 6;
      for (int i = 3; i <= 5; i++)
      {
         
         for (int j = 6; j <= 8; j++)
         {
            snagValues[i - 3][j - 6] = board[i][j];
         }
      }
   }
   if ((row >= 6 && row <= 8) && (col >= 0 && col <= 2))
   {
      quadrant = 7;
      for (int i = 6; i <= 8; i++)
      {
         
         for (int j = 0; j <= 2; j++)
         {
            snagValues[i - 6][j] = board[i][j];
         }
      }
   }
   else if ((row >= 6 && row <= 8) && (col >= 3 && col <= 5))
   {
      quadrant = 8;
      for (int i = 6; i <= 8; i++)
      {
         
         for (int j = 3; j <= 5; j++)
         {
            snagValues[i - 6][j - 3] = board[i][j];
         }
      }
   }
   else if ((row >= 6 && row <= 8) && (col >= 6 && col <= 8))
   {
      quadrant = 9;
      for (int i = 6; i <= 8; i++)
      {
         
         for (int j = 6; j <= 8; j++)
         {
            snagValues[i - 6][j - 6] = board[i][j];
         }
      }
   }
    
    /* 
     This loops through the 3 by 3 row and col
     to see if the number is a valid input.
    */
    
   for (int i = 0; i <= 2; i++)
   {
      for (int j = 0; j <= 2; j++)
      {
         for (int k = 0; k < 9; k++)
         {
            if (snagValues[i][j] == possibles[k])
            {
               possibles[k] = ' ';
    
            }
         }
      }
   }
    
   
   cout << "The possible values for "
        <<  "\'"
        << (char)coordinates[0]
        << coordinates[1]
        << "\'"
        << " are: ";
   
   string endRule = "";
   //print the values out.
   for (int i = 0; i < 9; i++)
   {
      
      if (possibles[i] != ' ')
      {
         endRule += possibles[i];
         endRule += ", ";
      }
      
   }
   
   string somethingSomething = "";
   
   for (int i = 0; i < endRule.length() - 2; i++)
   {
      somethingSomething += endRule[i];
   }
   
   cout << somethingSomething << endl;
}

/**********************************************************************
 * computeValues()
 * This is where I will find the possibleValues and locations
 *********************************************************************/
bool computeValues(char board[9][9], int row, int col, char value)
{
   // check the col
   for (int i = 0; i < 9; i++)
   {
      if (board[i][col] == value)
      {
         return false;
      }
   }
   
   // check the row
   for (int i = 0; i < 9; i++)
   {
      if (board[row][i] == value)
      {
         return false;
      }
   }
   
   /*
            Board Coordinates

    00 01 02    03 04 05    06 07 08
    10 11 12    13 14 15    16 17 18
    20 21 22    23 24 25    26 27 28
    
    30 31 32    33 34 35    36 37 38
    40 41 42    43 44 45    46 47 48
    50 51 52    53 54 55    56 57 58
    
    60 61 62    63 64 65    66 67 68
    70 71 72    73 74 75    76 77 78
    80 81 82    83 84 85    86 87 88
    */
   

   // check the quadrant
   int quadrant;
   char snagValues[3][3];
   
   if ((row >= 0 && row <= 2) && (col >= 0 && col <= 2))
   {
      quadrant = 1;
      for (int i = 0; i <= 2; i++)
      {
         
         for (int j = 0; j <= 2; j++)
         {
            snagValues[i][j] = board[i][j];
         }
      }
   }
   else if ((row >= 0 && row <= 2) && (col >= 3 && col <= 5))
   {
      quadrant = 2;
      for (int i = 0; i <= 2; i++)
      {
         
         for (int j = 3; j <= 5; j++)
         {
            snagValues[i][j - 3] = board[i][j];
         }
      }
   }
   else if ((row >= 0 && row <= 2) && (col >= 6 && col <= 8))
   {
      quadrant = 3;
      for (int i = 0; i <= 2; i++)
      {
         
         for (int j = 6; j <= 8; j++)
         {
            snagValues[i][j - 6] = board[i][j];
         }
      }
   }
   if ((row >= 3 && row <= 5) && (col >= 0 && col <= 2))
   {
      quadrant = 4;
      for (int i = 3; i <= 5; i++)
      {
         
         for (int j = 0; j <= 2; j++)
         {
            snagValues[i - 3][j] = board[i][j];
         }
      }
   }
   else if ((row >= 3 && row <= 5) && (col >= 3 && col <= 5))
   {
      quadrant = 5;
      for (int i = 3; i <= 5; i++)
      {
         
         for (int j = 3; j <= 5; j++)
         {
            snagValues[i - 3][j - 3] = board[i][j];
         }
      }
   }
   else if ((row >= 3 && row <= 5) && (col >= 6 && col <= 8))
   {
      quadrant = 6;
      for (int i = 3; i <= 5; i++)
      {
         
         for (int j = 6; j <= 8; j++)
         {
            snagValues[i - 3][j - 6] = board[i][j];
         }
      }
   }
   if ((row >= 6 && row <= 8) && (col >= 0 && col <= 2))
   {
      quadrant = 7;
      for (int i = 6; i <= 8; i++)
      {
         
         for (int j = 0; j <= 2; j++)
         {
            snagValues[i - 6][j] = board[i][j];
         }
      }
   }
   else if ((row >= 6 && row <= 8) && (col >= 3 && col <= 5))
   {
      quadrant = 8;
      for (int i = 6; i <= 8; i++)
      {
         
         for (int j = 3; j <= 5; j++)
         {
            snagValues[i - 6][j - 3] = board[i][j];
         }
      }
   }
   else if ((row >= 6 && row <= 8) && (col >= 6 && col <= 8))
   {
      quadrant = 9;
      for (int i = 6; i <= 8; i++)
      {
         
         for (int j = 6; j <= 8; j++)
         {
            snagValues[i - 6][j - 6] = board[i][j];
         }
      }
   }
   
    /* 

    This loops through the 3 by 3 row and col
    to see if the number is a valid input.

    */
   for (int i = 0; i <= 2; i++)
   {
      
      for (int j = 0; j <= 2; j++)
      {
         if (snagValues[i][j] == value)
         {
            return false;
         }
      }
   }

   return true;
}


/**********************************************************************
 * getCoordinates()
 * This is where we are going to get the coordinates for our input.
 *********************************************************************/
string getCoordinates(int &row, int &col)
{
   string coordinates;
   
   // Prompt for the coordinates of the item.
   cout << "What are the coordinates of the square: ";
   cin >> coordinates;
   
   coordinates = fixCoordinates(coordinates);
   
   
   
   col = toupper(coordinates[0]) - 'A';
   
   // rows
   row = coordinates[1] - '1';
   
   
   return coordinates;
}

/**********************************************************************
 * fixCoordinates()
 * This flips the strings around if you enter backwards coordinates.
 *********************************************************************/
string fixCoordinates(string coordinates)
{
   char fixedCoordinates[2];
   
   
   if (isalpha(coordinates[1])) // entered coordinates backwards.
   {
      fixedCoordinates[0] = toupper(coordinates[1]);
      fixedCoordinates[1] = coordinates[0];
      coordinates = fixedCoordinates;
   }
   else
   {
      fixedCoordinates[0] = toupper(coordinates[0]);
      fixedCoordinates[1] = coordinates[1];
      coordinates = fixedCoordinates;
      
   }
   
   return coordinates;
}

/**********************************************************************
* editSquare()
* We get to actually edit a location and play the game here.
*********************************************************************/
void editSquare(char board[9][9])
{
   int row;
   int col;
   
   
   string coordinates = getCoordinates(row, col);
   
   
   if (board[row][col] == ' ')
   {
      
      char value;
      cout << "What is the value at " << "\'"
           << (char)coordinates[0]
           << coordinates[1]
           << "\': ";
      cin >> value;
      
      
      if (value <= '9' && value > '0')
      {
         
         if (computeValues(board, row, col, value))
         {      
                // A   #
            board[row][col] = value;
         }
         else
            cout  << "ERROR: Value " << "\'" << value << "\'"
                  << " in square "
                  << "\'"
                  << (char)coordinates[0]
                  << coordinates[1]
                  << "\'"
                  << " is invalid\n";
      }
      else
      {
         cout  << "ERROR: Value " << "\'" << value << "\'"
               << " in square "
               << "\'"
               << (char)coordinates[0]
               << coordinates[1]
               << "\'"
               << " is invalid\n";
      }
      
   }
   else
   {
      cout << "ERROR: Square "
           << "\'"
           << (char)coordinates[0]
           << coordinates[1]
           << "\'"
           << " is filled\n";
   }
   
   
}



/**********************************************************************
 * saveAndQuit()
 * This is where I save the board to a file then I quit the game.
 *********************************************************************/
void saveAndQuit(char board[9][9])
{
   cout << "What file would you like to write your board to: ";
   char file[256];
   
   cin >> file;
   ofstream fout(file);
   
   if (fout.fail())
   {
      cerr << "Failed to write file";
      return;
   }
   // This checks to see if a place is ' ' and then replaces it
   // with a 0 so it can be read in correctly.
   for (int row = 0; row < 9; row++)
   {
      for (int column = 0; column < 9 ; column++)
      {
         if (board[row][column] == ' ')
         {
            board[row][column] = '0';
         }
      }
   }
   
   fout << board[0][0]
        << board[0][1]
        << board[0][2]
        << board[0][3]
        << board[0][4]
        << board[0][5]
        << board[0][6]
        << board[0][7]
        << board[0][8] << endl
   
        << board[1][0]
        << board[1][1]
        << board[1][2]
        << board[1][3]
        << board[1][4]
        << board[1][5]
        << board[1][6]
        << board[1][7]
        << board[1][8] << endl
   
        << board[2][0]
        << board[2][1]
        << board[2][2]
        << board[2][3]
        << board[2][4]
        << board[2][5]
        << board[2][6]
        << board[2][7]
        << board[2][8] << endl
   
        << board[3][0]
        << board[3][1]
        << board[3][2]
        << board[3][3]
        << board[3][4]
        << board[3][5]
        << board[3][6]
        << board[3][7]
        << board[3][8] << endl
   
        << board[4][0]
        << board[4][1]
        << board[4][2]
        << board[4][3]
        << board[4][4]
        << board[4][5]
        << board[4][6]
        << board[4][7]
        << board[4][8] << endl
   
   
        << board[5][0]
        << board[5][1]
        << board[5][2]
        << board[5][3]
        << board[5][4]
        << board[5][5]
        << board[5][6]
        << board[5][7]
        << board[5][8] << endl
   
        << board[6][0]
        << board[6][1]
        << board[6][2]
        << board[6][3]
        << board[6][4]
        << board[6][5]
        << board[6][6]
        << board[6][7]
        << board[6][8] << endl
   
        << board[7][0]
        << board[7][1]
        << board[7][2]
        << board[7][3]
        << board[7][4]
        << board[7][5]
        << board[7][6]
        << board[7][7]
        << board[7][8] << endl
   
        << board[8][0]
        << board[8][1]
        << board[8][2]
        << board[8][3]
        << board[8][4]
        << board[8][5]
        << board[8][6]
        << board[8][7]
        << board[8][8] << endl;
   
   cout << "Board written successfully\n";
   fout.close();
   return;
   
}

/**********************************************************************
 * interact()
* Here we will get to interact with the game, I.e Play, save and quit
* etc...
*********************************************************************/
void interact(char board[9][9])
{
   displayMenu();
   displayBoard(board);
   char playerInput;
   string coordinates;
   
   do
   {
      
      cout << "\n> ";
      cin >> playerInput;
      
      switch (toupper(playerInput))
      {
         case 'Q':
            saveAndQuit(board);
            break;
         case '?':
            displayMenu();
            break;
         case 'D':
            displayBoard(board);
            break;
         case 'E':
            editSquare(board);
            break;
         case 'S':
            int row;
            int col;
            char possibles[9];
            coordinates = getCoordinates(row, col);
            possibleValues(board, possibles, row, col, coordinates);
            break;
         default:
            cout << "Error: Invalid Command\n";
            break;
            
      }
   }
   while (playerInput != 'Q');
}

/**********************************************************************
* main()
* This is where the Filename and the Board are held
*********************************************************************/
int main()
{
   
   // This is the size of the Sodoku Board.
   char board[9][9];
   
   // This is the name of the file.
   char fileName[256];
   
   getFile(fileName);
   
   // Check to see if the file was read in correctly.
   // I now need to read the file.
   readFile(fileName, board);
   
   // This is how I interact with the player and board.
   interact(board);
   
   
   return 0;
}
