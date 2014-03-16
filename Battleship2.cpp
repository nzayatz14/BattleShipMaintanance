/*Name:Michele Burns
 * Class: CSC-3710
 * Date: 7 February 2014
 * Description:
 *
 */
#include<iostream>
#include<ctime>
#include<climits>
#include<string>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
//Function Declarations
void Welcome();
void NewGame();
void LoadGame();
void InitializeGame();
void PrintHelpGuide();
void PrintHighScores();
void createGrid(char [10][10]);
void printGrid(char [10][10]);
void RandomPlacement(char [10][10]);

bool verifyPlacement(int, char, int, char, int, char [10][10]); //length and coordinates and grid
//Class Declarations
class ship{

public:
void SetHealth(int);
void SetSunk(bool);

private:
int health;
int length;
bool isSunk;

};

int main(void)
{
   Welcome();
   NewGame();

}

//Welcome function when you first enter the game.
void Welcome()
{
   cout << "\033[2J\033[1;1H";
   int choice=0;
   cout<<"*******************************************************************"<<endl;
   cout<<"                            BATTLESHIP                             "<<endl;
   cout<<"*******************************************************************"<<endl;
   cout<< endl <<endl;
   cout<<"Please select one of the following choices:(Press the corresponding number)"<<endl;
   cout<<"1 - Start New Game"<<endl;
   cout<<"2 - Load a Saved Game"<<endl;
   cout<<"3 - View the Highscores List"<<endl;
   cout<<"4 - Access the Help Guide"<<endl;
   cout<<"5 - Quit"<<endl;
   
   /*do {
      cin>>choice;
   
      if(choice==1){
         NewGame();
      }else if(choice==2){
         LoadGame();
      }else if(choice==3){
         HighScores();
      }else if(choice==4){
         PrintHelpGuide();
      }else if(choice==5){
         cout<<"Goodbye!"<<endl;
      }else{
         cout<<"You have invalid entry, Please try again."<<endl;
      
   }while(choice>0&&choice<=5);
 */  
}


//Create Gridchar [] [] 
void createGrid (char usergrid[10][10])
{
   
   for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
          usergrid[i][j]='.';
      }
   }

}

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


//New Game function
void NewGame ()
{
   char usergrid[10][10];
   char cpugrid[10][10];
   bool istrue;
   char x1, x2;
   int y1,y2;
   createGrid(usergrid);
   createGrid(cpugrid);
   printGrid(usergrid);
   cout<<"Now please select the coordinates for your ships: "<<endl;
//This first loop is for Aircraft Carrier (5 units)
   do{
      cout<<"Enter the start and ending coordinates for your Aircraft Carrier(5 units long)."<<endl;
      cout<<"Please enter in the format A1 A5 or A1 E1: ";
      cin>>x1>>y1>>x2>>y2;
      istrue=verifyPlacement(5, x1, y1, x2, y2, usergrid);
      if(istrue==false)
         cout<<"INVALID SHIP PLACEMENT, Please try again."<<endl;
     }while(istrue==false);
     if(x1==x2){
       for(int i=y1;i<=y2; i++)
          usergrid[i-1][x1-65]='C';
     }else{
         for(int i=x1;i<=x2; i++)
            usergrid[y1-1][i-65]='C';
      }
      printGrid(usergrid);  
//This is for the Battleship (4 units)
   do{
      cout<<"Enter the start and ending coordinates for your Battleship(4 units long)."<<endl;
      cout<<"Please enter in the format A1 A5 or A1 E1: ";
      cin>>x1>>y1>>x2>>y2;
      istrue=verifyPlacement(4, x1, y1, x2, y2, usergrid);
      if(istrue==false)
         cout<<"INVALID SHIP PLACEMENT, Please try again."<<endl;
     }while(istrue==false); 
     if(x1==x2){
       for(int i=y1;i<=y2; i++)
          usergrid[i-1][x1-65]='B';
     }else{
         for(int i=x1;i<=x2; i++)
            usergrid[y1-1][i-65]='B';
      }
      printGrid(usergrid);  
//This is for the Destroyer (3 units)
   do{
      cout<<"Enter the start and ending coordinates for your Destroyer(3 units long)."<<endl;
      cout<<"Please enter in the format A1 A5 or A1 E1: ";
      cin>>x1>>y1>>x2>>y2;
      istrue=verifyPlacement(3, x1, y1, x2, y2, usergrid);
      if(istrue==false)
         cout<<"INVALID SHIP PLACEMENT, Please try again."<<endl;
     }while(istrue==false); 
     if(x1==x2){
       for(int i=y1;i<=y2; i++)
          usergrid[i-1][x1-65]='D';
     }else{
         for(int i=x1;i<=x2; i++)
            usergrid[y1-1][i-65]='D';
      }
      printGrid(usergrid);  
//This is for the Submarine (3 unitS)
   do{
      cout<<"Enter the start and ending coordinates for your Submarine(3 units long)."<<endl;
      cout<<"Please enter in the format A1 A5 or A1 E1: ";
      cin>>x1>>y1>>x2>>y2;
      istrue=verifyPlacement(3, x1, y1, x2, y2, usergrid);
      if(istrue==false)
         cout<<"INVALID SHIP PLACEMENT, Please try again."<<endl;
     }while(istrue==false); 
     if(x1==x2){
       for(int i=y1;i<=y2; i++)
          usergrid[i-1][x1-65]='S';
     }else{
         for(int i=x1;i<=x2; i++)
            usergrid[y1-1][i-65]='S';
      }
      printGrid(usergrid);  
//This is for the Patrol Boat (2 units)
   do{
      cout<<"Enter the start and ending coordinates for your Patrol Boat(2 units long)."<<endl;
      cout<<"Please enter in the format A1 A5 or A1 E1: ";
      cin>>x1>>y1>>x2>>y2;
      istrue=verifyPlacement(2, x1, y1, x2, y2, usergrid);
      if(istrue==false)
         cout<<"INVALID SHIP PLACEMENT, Please try again."<<endl;
     }while(istrue==false); 
     if(x1==x2){
       for(int i=y1;i<=y2; i++)
          usergrid[i-1][x1-65]='P';
     }else{
         for(int i=x1;i<=x2; i++)
            usergrid[y1-1][i-65]='P';
      }
      printGrid(usergrid);  
      RandomPlacement(cpugrid);
      printGrid(cpugrid);


}
bool verifyPlacement (int length, char x1, int y1, char x2, int y2, char usergrid[10][10])
{
   if(x1!=x2 && y1!=y2){
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
   srand (time(0));
   direction = rand() % 2 + 5;//choose a direction either vertical or horizontal
   do{
      srand (time(0));
      x1=rand() %6 + 65;
      y1=rand() %6;
      //direction = rand() % 2 + 5;
      if(direction==5){
         y2=y1+4;
         x2=x1;
      }else if(direction==6){
         x2=x1+4;
         y2=y1;
      }
      istrue=verifyPlacement(5, x1, y1, x2, y2, cpugrid);
     }while(istrue==false); 
     if(x1==x2){
       for(int i=y1;i<=y2; i++)
          cpugrid[i-1][x1-65]='C';
     }else{
         for(int i=x1;i<=x2; i++)
            cpugrid[y1-1][i-65]='C';
      }
   do{
      srand (time(0));
      x1=rand() %7 + 65;
      y1=rand() %7;
      //direction = rand() % 2 + 5;
      direction==5?direction++:direction--;
      if(direction==5){
         y2=y1+3;
         x2=x1;
      }else if(direction==6){
         x2=x1+3;
         y2=y1;
      }
      istrue=verifyPlacement(4, x1, y1, x2, y2, cpugrid);
     }while(istrue==false); 
     if(x1==x2){
       for(int i=y1;i<=y2; i++)
          cpugrid[i-1][x1-65]='B';
     }else{
         for(int i=x1;i<=x2; i++)
            cpugrid[y1-1][i-65]='B';
      }
   do{
      srand (time(0));
      x1=rand() %8 + 65;
      y1=rand() %8;
      //direction = rand() % 2 + 5;
      direction==5?direction++:direction--;
      if(direction==5){
         y2=y1+2;
         x2=x1;
      }else if(direction==6){
         x2=x1+2;
         y2=y1;
      }
      istrue=verifyPlacement(3, x1, y1, x2, y2, cpugrid);
     }while(istrue==false); 
     if(x1==x2){
       for(int i=y1;i<=y2; i++)
          cpugrid[i-1][x1-65]='D';
     }else{
         for(int i=x1;i<=x2; i++)
            cpugrid[y1-1][i-65]='D';
      }
   do{
      srand (time(0));
      x1=rand() %8 + 65;
      y1=rand() %8;
      //direction = rand() % 2 + 5;
      direction==5?direction++:direction--;
      if(direction==5){
         y2=y1+2;
         x2=x1;
      }else if(direction==6){
         x2=x1+2;
         y2=y1;
      }
      istrue=verifyPlacement(3, x1, y1, x2, y2, cpugrid);
     }while(istrue==false); 
     if(x1==x2){
       for(int i=y1;i<=y2; i++)
          cpugrid[i-1][x1-65]='S';
     }else{
         for(int i=x1;i<=x2; i++)
            cpugrid[y1-1][i-65]='S';
      }
   do{
      srand (time(0));
      x1=rand() %9 + 65;
      y1=rand() %9;
      //direction = rand() % 2 + 5;
      direction==5?direction++:direction--;
      if(direction==5){
         y2=y1+1;
         x2=x1;
      }else if(direction==6){
         x2=x1+1;
         y2=y1;
      }
      istrue=verifyPlacement(2, x1, y1, x2, y2, cpugrid);
     }while(istrue==false); 
     if(x1==x2){
       for(int i=y1;i<=y2; i++)
          cpugrid[i-1][x1-65]='P';
     }else{
         for(int i=x1;i<=x2; i++)
            cpugrid[y1-1][i-65]='P';
      }


}


