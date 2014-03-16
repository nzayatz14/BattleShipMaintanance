/*
 * Triad Development Group
 * Battleship console game
 *
 * Support.cpp - Support/Reference Module (Supports modules 1 and 2)
 *
 */

#include<iostream>
#include<ctime>
#include<climits>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include <sstream>	// for ostringstream
#include <cctype>
#include <iomanip>
#include <fstream>
#include <cstdlib>
using namespace std;
/* createGrid:
 *
 * This function creates a grid (2-D array) that contains a '.' in every location in the grid. 
 * This function is called at multiple places throughout module 1 and 2.
 *
 * Pre-Condition: The function is correctly handed an empty 2-D array
 *
 * Post-Condition: The grid is correctly filled in with each coordinate containing a '.' for every 
 * value.  
 *
 */
void createGrid (char grid[10][10])
{
   
   for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
          grid[i][j]='.';
      }
   }

}
/*printGrid:
 *
 * This function contains a loop that will print out the grid. First printing out the axis labels. Then
 * printing out what is contained in each coordinate.
 *
 * Pre-Condition:The function is correctly handed a loaded 2-D array to print out, meaning that 
 * grid[i][j] contains some value. 
 *
 * Post-Condition:The function correctly prints the grid to the screen.
 *
 */
void printGrid(char grid[10][10])
{
   cout<<"   A B C D E F G H I J"<<endl;
   int x=1;

    
   for(int i=0; i<10; i++){
      if(x<10){
         cout<<" ";
      }
      cout<<x;
      x++;
      for(int j=0; j<10; j++){
          cout<<" "<<grid[i][j];
      }
      cout<<endl;
   }
}
/*quitGame:
 *
 * This function clears the screen, prints out the Battleship header, then thanks the user for playing 
 * the game, than exits the program.
 *
 * Pre-Condiition: This function accepts no parameters.
 *
 * Post-Condition: The program has been exited.
 *
 */
void quitGame()
{
    cout << "\033[2J\033[1;1H";
         cout<<"*******************************************************************"<<endl;
         cout<<"                            BATTLESHIP                             "<<endl;
         cout<<"*******************************************************************"<<endl;
         cout<< endl <<endl;
         cout<<"Thanks for playing Battleship!"<<endl;
         exit(0);
}
