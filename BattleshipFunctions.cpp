
/* Triad Development Group
 * Battleship console game
 *
 * BattleshipFunctions.cpp  - Module 1 (Intilization) 
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

//Function Declarations
/* Welcome:
 *
 * This function is called in the main routine in Battleship.cpp, this function will act as the
 * starting point for the entire game of Battleship. Calling all other needed functions. This function 
 * will display the main menu. The function asks the user to input a number which will direct them to
 * another function.
 *
 * Pre-condition: The functions called have already been defined. This function requires no parameters.
 *
 * Post-condition: Every other function either falls back to the welcome function, thus displaying the 
 * main menu or the has exited the program elsewhere.
 */
void Welcome();
/*NewGame:
 *
 * This function is called when the user wishes to begin a new game. The function calls createGrid
 * which creates a ten by ten grid (2-D array) on which the ships will be placed and shots will be fired
 * both for the user and the cpu. The function prompts the user for their name and input in the form of
 * character,integer,character,integer on where they would like to place all 5 of their ships. 
 * The function then calls RandomPlacement, so that the cpu's ships can be placed, then it calls 
 * playGame and passes playGame the user inputed name, and the two grids with the ships already placed.
 *
 * Pre-condition: The functions have been correctly defined. This function requires no parameters.
 *
 * Post-condition: ...
 *
 */
void NewGame();
/*LoadGame:
 *
 * This function handles loading a function from a saved file within the current directory entitiled
 * "saved.txt" it creates locally variables to hold the player's name and then two grids (2-D arrays)
 * to hold each of the grids from the saved file. This function will then call the playGame 
 * function with the information loaded from the saved file.
 *
 * Pre-condition: This function assumes that there is something in the file, in the correct format to
 * read in the name and the two grids. 
 *
 * Post-condition: The function correctly hands off the name of the player and the two grids to the 
 * playGame function.
 *
 */
void LoadGame();
/*PrintHelpGuide:
 *
 * This function prints the help guide, for further information about this function please see comment
 * in reference.cpp.
 *
 * Pre-Condition: The function has no parameters. 
 *
 * Post-Condition: The helpguide was printed correctly. The function does not return anything.
 *
 */
void PrintHelpGuide();
/*PrintHighScores:
 *
 * This function prints the high scores, for further information about this function please see comment
 * in reference.cpp.
 *
 * Pre-Condition: This function has no parameters.
 *
 * Post-Condition: The high scores were printed correctly. The function does not return anything.
 *
 */
void PrintHighScores();
/*RandomPlacement:
 *
 * This function will create local variables to handle the processing of placing the 5 needed ships 
 * randomly onto the cpugrid. It does this more quickly by using a start location equation.By this 
 * equation, the odds that that the ship placement will be valid are increased, because the equation 
 * reduces the possibily that the ship will be placed in a location it does not fit.
 *
 * Pre-Condition: This function is correctly passed a grid (2-D array) loaded with '.' in every spot.
 *
 * Post-Condition: This function will have correctly placed the ships onto the board it was given.
 * ...
 *
 */
void RandomPlacement(char [10][10]);
/*verifyPlacement: 
 *
 * The function will verify that the coordinates passed to it are infact valid. It does this by checking
 * that the character entered is from A to J and the integer is from 1 to 10, then checking wether
 * the ship is being placed either horizontally or vertically, then checking to make sure the 
 * coordinates were correct for the length of the ship, and then finally checking to make sure that the
 * spaces are not already occupied (meaning they contain the value '.') The function returns either 
 * true or false depending if the ships placement is valid.  
 *
 * Pre-condition: The fucntion is correctly handed, the length of the ship, the charachter and integer 
 * for the starting point of the ship and the character and integer for the ending point of the ship, 
 * along with the grid that it is verifying. 
 *
 * Post-Condition: The function returns a boolean value.
 *
 *
 */

bool verifyPlacement(int, char, int, char, int, char [10][10]); //length and coordinates and grid
/*BubbleSort:
 *
 *  The bubble sort function sorts the items in the array of integers from highest to lowest using a 
 *  simple bubble sort algoritm and for loops. When a switch/swap is made with items in the array of 
 *  integers, the same switch/swap is made in the array of strings so the user name still corresponds 
 *  to their high score
 *
 * Pre-Condition: an array of integers, an array of strings, and one integer. The array of integers 
 * corresponds to all of the high scores that have been saved to the file highscores.txt, the array of 
 * strings corresponds to all of the user's names that have been saved to the file highscores.txt, 
 * and the integer refers to the size of each array. Both arrays will always be the same size since 
 * there will always be a name saved with a score to the file highscores.txt and the score in the 
 * array corresponds to the name in the array of strings in the same array position.
 *
 * Post-Condition: These 3 parameters are passed by reference. The bubble sort function is only 
 * called by the PrintHighScores function.
 *
 */
void BubbleSort(int list1[], string list2[], int size);
/*playGame:
 *
 * The function is located in Module2Main.cpp, for further information about the nature of this function
 * please see that file, a brief synopsis follows. This function is the primary module 2 handler, which
 * is used to play the game battleship. It handles the taking of turns between the user and the cpu.
 *
 * Pre-Condition: The fucntion expects to be correctly handed the name of the player as well as 
 * the usergrid and the cpugrid, each of which contain the ships correctly placed on the grid.
 *
 * Post-Condition: The function returns an int, a 0 for cpu win and a 1 for a player win.
 *
 */
int playGame(string name, char [10][10], char [10][10]);

/*Placement Struct:
 *
 * The Placement struct handles the necessary arrays and their definitions for the for loops. 
 *
 */
//Struct Declaration:
struct Placement{
  int lengtharray [5];
  char shiparray [5];
  string shipnamearray [5]; 
  int directionnumberarray [5];
};

//Welcome function when you first enter the game.
void Welcome()
{  char ch;
   int choice; //=0;
do{
   cout << "\033[2J\033[1;1H";

   cout<<"*******************************************************************"<<endl;
   cout<<"                            BATTLESHIP                             "<<endl;
   cout<<"*******************************************************************"<<endl;
   cout<< endl <<endl;
   cout<<"Please select one of the following choices:(Enter the corresponding number)"<<endl;
   cout<<"1 - Start New Game"<<endl;
   cout<<"2 - Load a Saved Game"<<endl;
   cout<<"3 - View the Highscores List"<<endl;
   cout<<"4 - Access the Help Guide"<<endl;
   cout<<"5 - Quit"<<endl;
   cout<<endl;
   cout<<"Enter the number: ";
   
      
      cin>>ch;
      while(ch<'1'||ch>'5'){
         cout<<"You have entered an invalid key, please try again."<<endl;
         cout<<"Enter the number:";
         cin>>ch;
      }
      choice=ch-48;

      if(choice==1){
         NewGame();
      }else if(choice==2){
         LoadGame();
      }else if(choice==3){
         PrintHighScores();
      }else if(choice==4){
         PrintHelpGuide();
      }else if(choice==5){
         quitGame();
      }else{
         cout<<"You have invalid entry, Please try again."<<endl;
      }
   }while(choice != 5);

}


//New Game function
void NewGame ()
{  
   string name;
   char usergrid[10][10];
   char cpugrid[10][10];
   bool istrue;
   char x1, x2;
   int y1,y2;
   createGrid(usergrid);
   createGrid(cpugrid);
   cout<<"Please enter your first name (no spaces): ";
   //cin>>name;
   //gets (name);
   cin.get();
   getline (cin, name); 

   printGrid(usergrid);
   cout<<name<<", now please select the coordinates for your ships: "<<endl;
 
   Placement item={{5,4,3,3,2},
                   {'C', 'B', 'D', 'S', 'P'},
                   {"Aircraft Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat"},
                   {6,7,8,8,9}};
   for(int z=0;z<5;z++){
   do{
      cout<<"Enter the start and ending coordinates for your ";
      cout<< item.shipnamearray[z];
      cout<<" ("<<item.lengtharray[z]<< " units long)."<<endl;
      cout<<"Please enter in the format A1 A5 or A1 E1: ";
      cin>>x1>>y1>>x2>>y2;
      x1=toupper(x1);
      x2=toupper(x2);
      istrue=verifyPlacement(item.lengtharray[z], x1, y1, x2, y2, usergrid);
      if(istrue==false)
         cout<<"INVALID SHIP PLACEMENT, Please try again."<<endl;
     }while(istrue==false);
     if(x1==x2){
       for(int i=y1;i<=y2; i++)
          usergrid[i-1][x1-65]=item.shiparray[z];
     }else{
         for(int i=x1;i<=x2; i++)
            usergrid[y1-1][i-65]=item.shiparray[z];
      }
      printGrid(usergrid);  
      }
cout<<"test1"<< endl;
      RandomPlacement(cpugrid);
cout<<"tets2"<<endl;
      playGame(name, usergrid, cpugrid);
cout<<"test3"<<endl;
}

bool verifyPlacement (int length, char x1, int y1, char x2, int y2, char usergrid[10][10])
{  if(!(x1>=65&&x1<=74) && !(x2>=65&&x2<=74)){
       return false;
   }else if(!(y1>=1&&y1<=10) && !(y2>=1&&y2<=10)){
      return false;
   }else if(x1!=x2 && y1!=y2){
      return false;
   }else if(x1==x2 && (y2-y1+1)!=length){
      return false;
   }else if(y1==y2 && (x2-x1+1)!=length){
      return false;
   }else if(x1==x2){
      for(int i=y1; i<=y2; i++){
         if(usergrid[i-1][x1-65]!='.'){
            return false;
         }
      }
    return true;
   }else if(y1==y2){
       for(int i=x1;i<=x2;i++){
          if(usergrid[y1-1][i-65]!='.'){
             return false;
          }
       }
    return true;
   }
   else
      return true;
}
 

void RandomPlacement(char cpugrid[10][10])
{  
   bool istrue;
   char x1, x2;
   int y1,y2;
   int direction;
   Placement item={{5,4,3,3,2},
                   {'C', 'B', 'D', 'S', 'P'},
                   {"Aircraft Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat"},
                   {6,7,8,8,9}};
   //direction = rand() % 2 + 5;//choose a direction either vertical or horizontal
  for(int z=0;z<5;z++){
  do{
      //srand (time(0));
      x1=rand() %item.directionnumberarray[z] + 65;
      y1=rand() %item.directionnumberarray[z];
      direction = rand() % 2 + 5;
      if(direction==5){
         y2=y1+(item.lengtharray[z]-1);
         x2=x1;
      }else if(direction==6){
         x2=x1+(item.lengtharray[z]-1);
         y2=y1;
      }
      istrue=verifyPlacement(item.lengtharray[z], x1, y1, x2, y2, cpugrid);
     }while(istrue==false); 
     if(x1==x2){
       for(int i=y1;i<=y2; i++)
          cpugrid[i-1][x1-65]=item.shiparray[z];
     }else{
         for(int i=x1;i<=x2; i++)
            cpugrid[y1-1][i-65]=item.shiparray[z];
      }
   }
}

void LoadGame()
{
   string name;
   char usergrid[10][10];
   char cpugrid[10][10];
  
   ifstream file;
   file.open("saved.txt");
   file>>name;
   if(file.eof()){
     cout<<"There is no saved game. Please start a new game."<<endl;
     //press any key to return to game play
     string discardstr;
     cout << endl << "Press any key to return to the main menu: " ;
     cin>>discardstr;
     //cin.get(discardstr);
     cin.ignore();
     //cin >> discardstr;
   }else{       
   for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
          file>>usergrid[i][j];
      }
   }
   for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
          file>>cpugrid[i][j];
      }
   }

   playGame(name,usergrid,cpugrid);
   }
}
