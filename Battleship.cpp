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
#include"support.cpp"
#include"reference.cpp"
#include"BattleshipFunctions.cpp"
#include"module2Main.cpp"

const int NUMBER_OF_SHIPS = 5;
const int MIN_COL_LABEL = 'A';
const int MAX_COL_LABEL = 'J';
const int MIN_ROW_LABEL = 1;
const int MAX_ROW_LABEL = 10;

//#include"module2Main.cpp"
using namespace std;


int main(void)
{
   srand (time(0));
   Welcome();
   

}

