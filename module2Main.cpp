/*
Triad Development Group
Battleship console game
Module 2 - Gameplay Module
*/


/*
PrintHighScores functionality:

Throughout the game, we keep a running total of the shots taken by each player and the number of hits for each player.
In this way, we can calculate the hit percentage at the end of the game.
For the purposes of calculating the player's score, we will use the following procedure:
-each time the player gets a hit, they get 10 points
-each time the player sinks a ship, they get points equal to the ship bonus (10x the length of the ship)
-at the end of the game, the player's score is multiplied by 100% plus their hit percentage (eg. *175% for a hit percentage of 75%)
*/


//Included Libraries
#include<iostream>
#include<ctime>
#include<climits>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include <sstream>	
#include <cctype>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;


//Declarations of non-class functions native to THIS MODULE ONLY

/*saveGame
Description: saveGame takes a snapshot of the current gamestate and writes it to a file that can be
	read and interpreted at a later time if loadGame is called
Pre-: expects to be given a string containing the player's name, as well as the usergrid and cpugrid
	which probably contain letters for ships, hits, and misses
Post-: the file is written in the game directory and contains all of the information the function
	was passed. After the function is called, the program terminates.
*/
void saveGame(string, char[10][10], char[10][10]);

//Class Declarations

/*class ship
Description: The ship class is the class that defines all of the ship objects.
	It contains their member variables, which describe properties the ships should have.
	It also defines the member functions to access these properties and manage basic operation
		of the ship objects.
*/
class ship{
private:
   int health;//number of units not hit yet
   int length;
   bool isSunk;//whether or not all units have been hit

public:
   void setHealth(int);
   int checkHealth();
   void setSunk(bool);
   bool checkSunk();
   void hit();
};

/*class player
Description: The player class is the class that defines both player objects.
	It contains the member variables that describe properties of the player, which include
		their stats such as score and hit percentage.
	It also defines the member functions to access these properties and manage basic operation
		of the player objects.
*/
class player{
private:
	int type;//what kind of user? 0 for cpu. 1 for human.
	int health;//total of all ship health
	int score;//score according to procedure listed at TOP
	int shots;//number of total shots player has taken
	int hits;//number of hits the player has achieved
	double hitPercent;//hits/shots
	string name;//name of player (only used for human)

public:
	void setType(int);
	int checkType();
	void setHealth(int);
	int checkHealth();
	void decrementHealth();
	char takeTurn(string, char [10][10], char [10][10], char [10][10], char [10][10]);
	bool verifyShot(string, char [10][10], char [10][10], char [10][10], char, int);
	void addScore(int);
	int checkScore();
	void setScore(int);
	void incrementShots();
	void setShots(int);
	int checkShots();
	void incrementHits();
	void setHits(int);
	int checkHits();
	void calcPercent();
	double checkPercent();
	void genScore();
	void setName(string);
};


//BEGIN LOAD-GAME FUNCTIONALITY

int playGame(string name, char usergrid[10][10], char cpugrid[10][10]){

	//declare base objects
	player user, cpu;
	user.setScore(0);
	cpu.setScore(0);
	user.setType(1);
	cpu.setType(0);
	user.setName(name);
	ship userCar, cpuCar, userBat, cpuBat, userDes, cpuDes, userSub, cpuSub, userPat, cpuPat;	
	char selected;
	char selected2;
	string discardstr;
	char userview[10][10];
	createGrid(userview);

	//declare and initialize counters for loading ships, hits, and misses
	int unumC=0, unumB=0, unumD=0, unumS=0, unumP=0; //counters for numbers of each letter on grid  (i.e. health of corresponding ship)
	int cnumC=0, cnumB=0, cnumD=0, cnumS=0, cnumP=0;
	int unumX=0, unumM=0, cnumX=0, cnumM=0; //counters for numbers of hits and misses for each player

	//loop to count instances in both grids
	for(int i=0;i<10;i++){
	   for(int j=0;j<10;j++){
	      if(cpugrid[i][j]=='M'){//if the player missed at this spot
				userview[i][j]='M';
				unumM++;
	      }
	      else if(cpugrid[i][j]=='X'){//if the player hit at this spot
	         userview[i][j]='X';
				unumX++;
	      }
			else if(cpugrid[i][j]=='C'){//if the cpu has an aircraft carrier here
				cnumC++;
			}
			else if(cpugrid[i][j]=='B'){//" battleship
				cnumB++;
			}
			else if(cpugrid[i][j]=='D'){//" destroyer
				cnumD++;
			}
			else if(cpugrid[i][j]=='S'){//" submarine
				cnumS++;
			}
			else if(cpugrid[i][j]=='P'){//" patrol boat
				cnumP++;
			}
			if(usergrid[i][j]=='M'){//if the computer missed at this spot
				cnumM++;
			}
			else if(usergrid[i][j]=='X'){//if the computer hit at this spot
				cnumX++;
			}
			else if(usergrid[i][j]=='C'){//if the user has an aircraft carrier here
				unumC++;
			}
			else if(usergrid[i][j]=='B'){//" battleship
				unumB++;
			}
			else if(usergrid[i][j]=='D'){//" destroyer
				unumD++;
			}
			else if(usergrid[i][j]=='S'){//" submarine
				unumS++;
			}
			else if(usergrid[i][j]=='P'){//" patrol boat
				unumP++;
			}
	   }
	}

	//set ships health
	cpuCar.setHealth(cnumC);
	cpuBat.setHealth(cnumB);
	cpuDes.setHealth(cnumD);
	cpuSub.setHealth(cnumS);
	cpuPat.setHealth(cnumP);
	userCar.setHealth(cnumC);
	userBat.setHealth(cnumB);
	userDes.setHealth(cnumD);
	userSub.setHealth(cnumS);
	userPat.setHealth(cnumP);

	//draw grids on screen first time
	cout << "\033[2J\033[1;1H";
	cout<<"*******************************************************************"<<endl;
	cout<<"                            BATTLESHIP                             "<<endl;
	cout<<"*******************************************************************"<<endl;
  	cout<< endl <<endl;
	printGrid(userview);
	cout << "-------------------------------------------------------------------" << endl;
	printGrid(usergrid);

	//if no hits or misses, make sure ships health is correct
	if(unumM == 0 && unumX == 0){
		userCar.setHealth(5);
		userBat.setHealth(4);
		userDes.setHealth(3);
		userSub.setHealth(3);
		userPat.setHealth(2);
	}
	if(cnumM == 0 && cnumX == 0){
		cpuCar.setHealth(5);
		cpuBat.setHealth(4);
		cpuDes.setHealth(3);
		cpuSub.setHealth(3);
		cpuPat.setHealth(2);
	}

	//set initial number of shots and hits for each player
	user.setHits(unumX);
	user.setShots(unumX+unumM);
	cpu.setHits(cnumX);
	cpu.setShots(cnumX+cnumM);

	//set initial player health
	user.setHealth(userCar.checkHealth()+userBat.checkHealth()+userDes.checkHealth()+userSub.checkHealth()+userPat.checkHealth());
	cpu.setHealth(cpuCar.checkHealth()+cpuBat.checkHealth()+cpuDes.checkHealth()+cpuSub.checkHealth()+cpuPat.checkHealth());

	//set initial player scores
	user.addScore(10*((5-cnumC)+(4-cnumB)+(3-cnumD)+(3-cnumS)+(2-cnumP)));
	cnumC==0?user.addScore(50):user.addScore(0);
	cnumB==0?user.addScore(40):user.addScore(0);
	cnumD==0?user.addScore(30):user.addScore(0);
	cnumS==0?user.addScore(30):user.addScore(0);
	cnumP==0?user.addScore(20):user.addScore(0);
	cpu.addScore(10*((5-unumC)+(4-unumB)+(3-unumD)+(3-unumS)+(2-unumP)));
	unumC==0?cpu.addScore(50):cpu.addScore(0);
	unumB==0?cpu.addScore(40):cpu.addScore(0);
	unumD==0?cpu.addScore(30):cpu.addScore(0);
	unumS==0?cpu.addScore(30):cpu.addScore(0);
	unumP==0?cpu.addScore(20):cpu.addScore(0);

	//END LOAD-GAME FUNCTIONALITY

	while(user.checkHealth() > 0 && cpu.checkHealth() > 0){//while both players are still alive


	selected = user.takeTurn(name, usergrid, cpugrid, cpugrid, userview);//take the human player's turn and save the letter at the position they select

	//decide if the selection is a hit or a miss, and update the appropriate ship and player health and score
	switch(selected){
		case '.':
			cout << "MISS!" << endl;
			break;
		case 'C':
			cout << "HIT!" << endl;
			user.incrementHits();
			cpuCar.hit();
			cpu.decrementHealth();
			user.addScore(10);
			if(cpuCar.checkHealth()==0){
				cout << "You have sunk the opponent's Aircraft Carrier!" << endl;
				cpuCar.setSunk(true);
				user.addScore(50);
			}
			break;
		case 'B':
			cout << "HIT!" << endl;
			user.incrementHits();
			cpuBat.hit();
			cpu.decrementHealth();
			user.addScore(10);
			if(cpuBat.checkHealth()==0){
				cout << "You have sunk the opponent's Battleship!" << endl;
				cpuBat.setSunk(true);
				user.addScore(40);
			}
			break;
		case 'D':
			cout << "HIT!" << endl;
			user.incrementHits();
			cpuDes.hit();
			cpu.decrementHealth();
			user.addScore(10);
			if(cpuDes.checkHealth()==0){
				cout << "You have sunk the opponent's Destroyer!" << endl;
				cpuDes.setSunk(true);
				user.addScore(30);
			}
			break;
		case 'S':
			cout << "HIT!" << endl;
			user.incrementHits();
			cpuSub.hit();
			cpu.decrementHealth();
			user.addScore(10);
			if(cpuSub.checkHealth()==0){
				cout << "You have sunk the opponent's Submarine!" << endl;
				cpuSub.setSunk(true);
				user.addScore(30);
			}
			break;
		case 'P':
			cout << "HIT!" << endl;
			user.incrementHits();
			cpuPat.hit();
			cpu.decrementHealth();
			user.addScore(10);
			if(cpuPat.checkHealth()==0){
				cout << "You have sunk the opponent's Patrol Boat!" << endl;
				cpuPat.setSunk(true);
				user.addScore(20);
				}
			break;
		default:
			cout << "OH NO SOMETHING WENT TERRIBLY WRONG!" << endl;//<----- This actually helped us locate several errors :)
			break;
	}
	printGrid(userview);//print to the screen the human player's view at the end of their turn

	//check if the player won on their last turn
	if(cpu.checkHealth()==0){
	cout << "Congratulations! You have won the game!" << endl;
	cout << "\tYour stats were: " << endl;
	cout << "\t\t" << user.checkShots() << " total shots" << endl;
	cout << "\t\t" << user.checkHits() << " hits" << endl;
	cout << "\t\t" << user.checkShots()-user.checkHits() << " misses" << endl;
	user.genScore();
	cout << "\tResulting in a hit percentage of " << setprecision(2) << user.checkPercent() << "%" << endl;
	cout << "\tYou achieved a score of " << user.checkScore() << "!" << endl;
	//if the player won on their last turn, initiate end-game procedure, including generating their final score
	ofstream highscores;
	highscores.open("highscores.txt", ios::app);
	highscores << user.checkScore() << " " << name;
	highscores.close();

	cout << "Press any key to continue!" << endl;
	cin >> discardstr;
	return 1;
	}

	selected2 = cpu.takeTurn(name, usergrid, cpugrid, usergrid, userview);//take the computer player's turn and save the randomly selection position

	//decide if the selection is a hit or a miss, and update the appropriate ship and player health and score
	switch(selected2){
		case '.':
			cout << "MISS!" << endl;
			break;
		case 'C':
			cout << "HIT!" << endl;
			cpu.incrementHits();
			userCar.hit();
			user.decrementHealth();
			cpu.addScore(10);
			if(userCar.checkHealth()==0){
				cout << "Your opponent has sunk your Aircraft Carrier!" << endl;
				userCar.setSunk(true);
				cpu.addScore(50);
			}
			break;
		case 'B':
			cout << "HIT!" << endl;
			cpu.incrementHits();
			userBat.hit();
			user.decrementHealth();
			cpu.addScore(10);
			if(userBat.checkHealth()==0){
				cout << "Your opponent has sunk your Battleship!" << endl;
				userBat.setSunk(true);
				cpu.addScore(40);
			}
			break;
		case 'D':
			cout << "HIT!" << endl;
			cpu.incrementHits();
			userDes.hit();
			user.decrementHealth();
			cpu.addScore(10);
			if(userDes.checkHealth()==0){
				cout << "Your opponent has sunk your Destroyer!" << endl;
				userDes.setSunk(true);
				cpu.addScore(30);
			}
			break;
		case 'S':
			cout << "HIT!" << endl;
			cpu.incrementHits();
			userSub.hit();
			user.decrementHealth();
			cpu.addScore(10);
			if(userSub.checkHealth()==0){
				cout << "Your opponent has sunk your Submarine!" << endl;
				userSub.setSunk(true);
				cpu.addScore(30);
			}
			break;
		case 'P':
			cout << "HIT!" << endl;
			cpu.incrementHits();
			userPat.hit();
			user.decrementHealth();
			cpu.addScore(10);
			if(userPat.checkHealth()==0){
				cout << "Your opponent has sunk your Patrol Boat!" << endl;
				userPat.setSunk(true);
				cpu.addScore(20);
			}
			break;
		default:
			cout << "OH NO SOMETHING WENT TERRIBLY WRONG!" << endl;//<----- This actually helped us locate several errors :)
			break;
	}
	printGrid(usergrid);//print to the screen the human player's view of the computer opponent's grid (i.e. only their own hits/misses)

	//check if the human player lost on the computer's last turn, and if so, initiate end-game procedure
	if(user.checkHealth()==0){
		cout << "Oh no! You have lost the game!" << endl;
		cout << "Press any key to continue!" << endl;
		cin >> discardstr;
		return 0;
	}

	}
	return 0;
}

//sets the ship object's health
void ship::setHealth(int input){
	health=input;
}

//returns the ship object's health
int ship::checkHealth(){
	return health;
}

//sets the ship object's sunk status
void ship::setSunk(bool input){
	isSunk=input;
}

//returns the ship object's sunk status
bool ship::checkSunk(){
	return isSunk;
}

//decrements the ship object's health as a result of being hit
void ship::hit(){
	health--;
}

//sets the player object's name
void player::setName(string input){
	name=input;
}

//sets the player object's type (0 for CPU, 1 for human)
void player::setType(int input){
	type=input;
}

//returns the player object's type
int player::checkType(){
	return type;
}

//sets the player object's health (combined total of their ships' health)
void player::setHealth(int input){
	health=input;
}

//returns the player object's health
int player::checkHealth(){
	return health;
}

//decrements the player object's health as a result of one of their ships being hit
void player::decrementHealth(){
	health--;
}

//adds desired amount to the player object's score
void player::addScore(int input){
	score+=input;
}

//returns the player object's current score
int player::checkScore(){
	return score;
}

//sets the player object's score to the desired amount
void player::setScore(int input){
	score=input;
}

//increments the number of shots the player object has taken as when they take 1 turn
void player::incrementShots(){
	shots++;
}

//sets the number of shots the player object has taken (used when loading an existing game)
void player::setShots(int input){
	shots=input;
}

//returns the player object's number of shots
int player::checkShots(){
	return shots;
}

//increments the number of hits the player object has achieved
void player::incrementHits(){
	hits++;
	calcPercent();
}

//sets the number of shots the player object has taken (used when loading an existing game)
void player::setHits(int input){
	hits=input;
}

//returns the player object's number of hits
int player::checkHits(){
	return hits;
}

//calculates the player object's hit percentage as a function of hits divided by total shots
void player::calcPercent(){
	hitPercent=(double)hits/shots;
}

//returns the player object's hit percentage
double player::checkPercent(){
	return hitPercent;
}

//generates the player object's final game score, taking into account the hit percentage
void player::genScore(){
	score=(double)score*(1+hitPercent);
}

/*player::takeTurn
Description: takeTurn is responsible for prompting the user for a position to fire at (or randomly
	generating it in the case of the computer) and verifying that position as valid. It also places
	a HIT (X) or MISS (M) on the appropriate grid.
Pre-: It expects the player object's name on which it is being called (because saveGame is called inside of here),
	as well as 4 grids; the usergrid, cpugrid, and grid corresponding to which object called the function (one of
	which is redundant), and the grid representing the user's view.
Post-: The player object's turn will have effectively been taken, they will have been prompted for a position to fire at
	(or one will have been randomly generated in the case of the computer), and a HIT (X) or MISS (X) will be placed on the
	appropriate grid.
*/
char player::takeTurn(string name, char usergrid[10][10], char cpugrid[10][10], char grid[10][10], char view[10][10]){
	char x;
	int y;
	char selected;

	if(type==1){
		cout << "Please choose a position to fire at (in the form A1): ";
		//cin >> x >> y;
		cin >> x;

		while(x=='?'||x=='S'||x=='Q'){
		//if statement here for help guide
		if(x=='?'){

		PrintHelpGuide();
		cout << "\033[2J\033[1;1H";
		cout<<"*******************************************************************"<<endl;
		cout<<"                            BATTLESHIP                             "<<endl;
		cout<<"*******************************************************************"<<endl;
	  	cout<< endl <<endl;
		printGrid(view);
		cout << "-------------------------------------------------------------------" << endl;
		printGrid(usergrid);
		cout << "Please choose a position to fire at (in the form A1): ";
		//cin >> x >> y;
		}
		else if(toupper(x)=='S'){
			saveGame(name, usergrid, cpugrid);
		}
		else if(toupper(x)=='Q'){
			char response;
			cout << "Would you like to save the game first (Y/N)? ";
			cin >> response;
			while(toupper(response) != 'Y' && toupper(response) != 'N'){
				cout << "Please enter Y or N!" << endl;
				cout << "Would you like to save the game first (Y/N)? ";
				cin >> response;
			}
			if(toupper(response)=='Y'){
				saveGame(name, usergrid, cpugrid);
			}
			else{
				quitGame();
			}
		}
			cin >> x;
		}
		
		cin >> y;

		x=toupper(x);
		while(verifyShot(name, usergrid, cpugrid, view, x, y)==false){
		cout << "INVALID POSITION!" << endl << "Please choose a position to fire at (in the form A1): ";
		cin >> x >> y;
		x=toupper(x);
		}

   cout << "\033[2J\033[1;1H";
	cout<<"*******************************************************************"<<endl;
	cout<<"                            BATTLESHIP                             "<<endl;
	cout<<"*******************************************************************"<<endl;
  	cout<< endl <<endl;
	cout << "You fired at " << x << y << "... ";
	incrementShots();

	}
	else{
		do{
			x=rand() %10 + 65;
			y=rand() %10;
		}while(verifyShot(name, usergrid, cpugrid, grid, x, y)==false);
		cout << "-------------------------------------------------------------------" << endl;
		cout << "The computer fired at " << x << y << "... ";
		incrementShots();
	}
	x=toupper(x);
	selected = grid[y-1][x-65]; //As opposed to above commented out logic, because now takeTurn is passed the corresponding grid

	if(type==0){
		selected=='.'?grid[y-1][x-65]=77:grid[y-1][x-65]=88;
	}
	else{
		selected=='.'?view[y-1][x-65]=77:view[y-1][x-65]=88;
		selected=='.'?cpugrid[y-1][x-65]=77:cpugrid[y-1][x-65]=88;
	}
	return selected;	
}

/*player::verifyShot
Description: verifyShot is responsible for determining if a position selected to fire at is valid (i.e. it is on
	the grid, and has not been fired at before.
Pre-: It expects the player object's name (since saveGame is called from here), as well as 3 grids; the usergrid,
	cpugrid, and grid corresponding to which object called it (one of which is redundant), and finally the coordinates
	of the position that has been selected to fire at.
Post-: It returns true if the position is valid to fire at (i.e. is on the grid and has not been fired at before).
	It returns false if the position is not valid to fire at (i.e. is off the grid or has been fired at before).
*/
bool player::verifyShot(string name, char usergrid[10][10], char cpugrid[10][10], char grid[10][10], char x, int y){

	if(!(x>=65 && x<=74)){
		return false;
	}
	else if(!(y>=1 && y<=10)){
		return false;
	}
	else if(grid[y-1][x-65]=='X'){
		return false;
	}
	else if(grid[y-1][x-65]=='M'){
		return false;
	}
	else
		return true;
	}

/*saveGame
Description: saveGame is responsible for writing the current game-state information to a file in the game directory.
Pre-: It expects the player object's name and both the usergrid and cpugrid, all of which are written to a file in
	the game directory called "saved.txt". The format is name/usergrid/cpugrid where / is a line break.
Post-: It returns nothing, but the file will be written in the game directory, ready to be loaded at a later date if
	the user so chooses. When this function is called, and after it has saved the game, the program terminates.
*/
void saveGame(string name, char usergrid[10][10], char cpugrid[10][10]){
	ofstream saved;
	saved.open("saved.txt", ios::trunc);
	saved << name << endl;
    
   for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
          saved << usergrid[i][j] << " ";
      }
      saved<<endl;
   }
	cout << endl;
	for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
          saved << cpugrid[i][j] << " ";
      }
      saved<<endl;
   }
	saved.close();
	quitGame();
}
