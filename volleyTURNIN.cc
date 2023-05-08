#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

//The current a.out is just for this file. 
//I'm just compiling by using g++ volley.cc
int main(){
	string question = "What is 2+2?";
	string answers = "1) 1\n2) 2\n3) 3\n4) 4";
	int correctAnswer = 4;
	//declares time passed variable
	chrono::duration<float> time_passed;
	chrono::duration<float> prevTime = chrono::seconds(1000000);

	int playerSwitcher = -1;
	int playerTurn = 1;
	int winner = 0;

	while(true){
		system("clear");
		chrono::steady_clock::time_point timer_start;
		timer_start = chrono::steady_clock::now();

		//playerSwitcher starts as -1, 
		//but each loop changes its sign
		if(prevTime != chrono::seconds(1000000)){
			cout << "You have " << prevTime.count() << " seconds to answer." << endl;
		}
		playerSwitcher *= -1;
		//if its -1, then its player twos turn
		if(playerSwitcher < 0) playerTurn = 2;
		//otherwise its player one's turn. 
		//we start w/ player 1
		else playerTurn = 1;
		
		cout << "\nPLAYER " << playerTurn << endl; 
		cout << question << endl;
		cout << answers << endl << "\n>";

		int choice;
		cin >> choice;
		//if they choose wrong then it breaks and prints
		if(choice != correctAnswer){
			cout << "\nWrong answer!" << endl;
			break;
		}
		//this defines the time_passed variable and figures out how much time has passed.
		time_passed = chrono::steady_clock::now() - timer_start;
		//if we're over the timelimit, break;
		if(time_passed > prevTime){
			cout << "\nYou ran out of time!" << endl;
			break;
		}
		prevTime = time_passed;
	}
	//it only breaks on the loser's turn
	//so this declares the other person the winner.
	if(playerSwitcher < 0) winner = 1;
	else winner = 2;
	cout << "Player " << winner << " wins!\n" << endl;
}
