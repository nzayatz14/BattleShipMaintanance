/*
 * Triad Development Group
 * Battleship Consle Game
 *
 * Reference.cpp - Support/Reference Module (Supports Modules 1 and 2)
*/

#include <iostream>
#include <sstream>	// for ostringstream
#include <string>
#include <cctype>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>


using namespace std;
void BubbleSort(int list1[], string list2[], int size);



/*
This function displays the top 10 high scores (if there are 10 high scores) for the user to view. The high scores can be viewed from the main menu. From the main menu the user enters '3'. This is a void function that takes no parameters and returns no values. The high scores list will be displayed until the user enters any character to return to either the main menu, which is a discard character that exits the function and returns to the previous function. 
*/
void PrintHighScores ()
{
        cout << "\033[2J\033[1;1H";
 	cout<<"*******************************************************************"<<endl;
        cout<<"                            BATTLESHIP                             "<<endl;
        cout<<"*******************************************************************"<<endl;
        cout<< endl <<endl;
	cout << "HIGH SCORES LIST" << endl<< endl;

	ifstream inputFile;
	inputFile.open("highscores.txt");

	int arrayScores[100];
	string arrayNames[100];
	int x, y, size;

//read in the high scores
	bool endFile = false;
	x = 0;
inputFile >> arrayScores[x] >> arrayNames[x];

	do {
		if (inputFile.eof())
		{
			endFile = true;
		}
		else
		{
			x++;
			inputFile >> arrayScores[x] >> arrayNames[x];
		}

	} while (endFile == false);

	size = x + 1;

//sort the top 10 highest scores
	BubbleSort(arrayScores, arrayNames, size);

//print the high scores
	int z=0;
	for (y=0; y < 10; y++) {

		if (y>0 && arrayScores[y] == arrayScores[y-1])
		{
			cout << setw(2) << z << ") " << arrayScores[y] << " - " << arrayNames[y] << endl;
			z++;
		}
		else
		{
			z++;
			cout << setw(2) << z << ") " << arrayScores[y] << " - " << arrayNames[y] << endl;
		}
	}

	inputFile.close();

     //press any key to return to game play
     string discardstr;
     cout << endl << "Press any key to return to the main menu: " ;
     cin>>discardstr;
     //cin.get(discardstr);
     cin.ignore();
     //cin >> discardstr;
}

/*
This function takes 3 parameters: an array of integers, an array of strings, and one integer. The array of integers corresponds to all of the high scores that have been saved to the file highscores.txt, the array of strings corresponds to all of the user's names that have been saved to the file highscores.txt, and the integer refers to the size of each array. Both arrays will always be the same size since there will always be a name saved with a score to the file highscores.txt and the score in the array corresponds to the name in the array of strings in the same array position. The bubble sort function sorts the items in the array of integers from highest to lowest using a simple bubble sort algoritm and for loops. When a switch/swap is made with items in the array of integers, the same switch/swap is made in the array of strings so the user name still corresponds to their high score. These 3 parameters are passed by reference. The bubble sort function is only called by the PrintHighScores function.
*/
void BubbleSort(int list1[], string list2[], int size)
{
	for(int x=0; x<size; x++)
	{
		for(int y=0; y<size-1; y++)
		{
			if(list1[y]<list1[y+1])
			{
				int temp = list1[y+1];
					string temp2 = list2[y+1];
				list1[y+1] = list1[y];
					list2[y+1] = list2[y];
				list1[y] = temp;
					list2[y] = temp2;
			}
		}
	}


}

/*
This function displays the help guide for the user to view. This help guide can be viewed from the main menu or in the middle of a game. From the main menu the user enters '4' or enters '?' in the middle of a game. This is a void function that takes no parameters and returns no values. The help guide will be displayed until the user enters any character to return to either the main menu or the current game, which is a discard character that exits the function and returns to the previous function. 
*/
void PrintHelpGuide ()
{
        cout << "\033[2J\033[1;1H";
 	cout<<"*******************************************************************"<<endl;
        cout<<"                            BATTLESHIP                             "<<endl;
        cout<<"*******************************************************************"<<endl;
        cout<< endl <<endl;
	cout << "HELP GUIDE" << endl;

	cout << "\tA) \"BATTLESHIP\" SHIPS" << endl << "\t\tSHIP NAMES\t\tLENGTHS\t\tCHARACTERS" <<endl;
	cout << "\t\t1) Aircraft Carrier\t5 units long\t'C'"<<endl;
	cout << "\t\t2) Battleship\t\t4 units long\t'B'"<<endl;
	cout << "\t\t3) Destroyer\t\t3 units long\t'D'"<<endl;
	cout << "\t\t4) Submarine\t\t3 units long\t'S'"<<endl;
	cout << "\t\t5) Patrol Boat\t\t2 untis long\t'P'"<<endl;
	cout << endl;

	cout << "\tB) \"BATTLESHIP\" GAME PLAY"<<endl;
	cout << "\t\t1) New Game"<<endl;
	cout << "\t\t\ta) From the main menu, press '1' to begin a new game."<<endl;
	cout << "\t\t\tb) Enter your first name. Enter the start and end coordinates of each ship beginning with the longest and ending with the shortest."<<endl;
	cout << "\t\t\t\ti) Valid coordinate entries: A1 E1, A1E1, a1 e1, a1e1, A 1 E 1, a 1 e 1"<<endl;
	cout << "\t\t\t\tii) The user's updated grid with ship locations will be displayed after each ship placement."<<endl;
	cout << "\t\t\t\tiii) Any invalid ship placements will prompt the user to re-enter ship coordinates."<<endl;
	cout << "\t\t\tc) Game play will begin. User will be prompted to enter one coordinate to fire on the opponent's grid."<<endl;
	cout << "\t\t\t\ti) The opponent's grid will be updated with 'X' for a hit and 'M' for a miss."<<endl;
	cout << "\t\t\t\tii) The opponent will select a grid location after the user has selected a location."<<endl;
	cout << "\t\t\t\tiii) At any time during the game the user may enter '?' to view the Help Guide, 'S' to save and exit the game, or 'Q' to quit the current game without saving."<<endl;
	cout << "\t\t\t\tiv) Game play will continue until either the user or opponent wins or until the user chooses to save and quit or quit without saving."<<endl;
	cout << "\t\t\t\tv) *The user may only save one game at a time. If a game has already been saved, the user may save their current game and the old saved game will be overwritten."<<endl;
	cout << "\t\t2) Load a Saved Game"<<endl;
	cout << "\t\t\ta) From the main menu, press '2' to load a saved game."<<endl;
	cout << "\t\t\tb) Only one game may be saved at a time. *If more than one game is saved, the older one will be overwritten by the newer game. The newest game will be loaded and game play will continue at the last saved point. Both the user's and opponent's grid will be displayed with all of the saved information and coordinates that have previously been played."<<endl;
	cout << endl;

	cout << "\tC) \"BATTLESHIP\" HIGH SCORES"<<endl;
	cout << "\t\t1) Scoring"<<endl;
	cout << "\t\t\ta) Plus 10 points per hit."<<endl;
	cout << "\t\t\tb) No penalty for misses."<<endl;
	cout << "\t\t\tc) When user sinks a ship, plus a ship bonus of 10 times the length of the ship."<<endl;
	cout << "\t\t\td) If the user wins, their final score is their current scores times 100\\% plus their hit percentage (ratio of hits to misses)."<<endl;
	cout << "\t\t\te) If the user loses, then their final score is 0."<<endl;
	cout << "\t\t2) View High Scores"<<endl;
	cout << "\t\t\ta) From the main menu, press '3' to view high scores."<<endl;
	cout << "\t\t\tb) The top 10 highest scores will be displayed and ranked along with the user's name."<<endl;
	cout << endl;

	cout << "\tD) \"BATTLESHIP\" CREDITS"<<endl;
	cout << "\t\t1) Triad Development Group"<<endl;
	cout << "\t\t\ta) The Triad Development Group (TDG) created the terminal based computer generated \"BATTLESHIP\" game for the HASBRO company."<<endl;
	cout << "\t\t\t\ti) Credit for the creation of \"BATTLESHIP\" goes to Michele Burns, Project Manager; Joshua Gilstrap, Client/Developer Liason; & Greyson Whitaker, Documents Manager."<<endl;
	cout << "\t\t2) \"BATTLESHIP\" is a game of the HASBRO company, all rights reserved. Electronic terminal-based version of \"BATTLESHIP\" was created by the Triad Development Group, Inc. for the HASBRO company, in cooperation with the Senior Manager, Dr. Scott Russell, of High Point University's Department of Mathematics and Computer Science, CSC 3710: Software Engineering & Design."<<endl;


     //press any key to return to game play
     string discardstr;
     cout << endl << "Press any key to return to the main menu: " ;
     cin>>discardstr;
     //cin.get(discardstr);
     cin.ignore();
     //cin >> discardstr;
     
}


