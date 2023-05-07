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
struct Questions{
	string question;
	string correctAnswer;
	vector<string> answers;
};
void readJeopardy(const string fileName, vector<Questions>& questions){
	ifstream infile(fileName);
	if(!infile.is_open()){
		cerr << "Error: could not open file " << fileName << endl;
	}
	Questions q;
	string line;
	int lineCount = 0;
	//Getting the questions
	while(getline(infile, line)){
		if(line.empty()){continue;}
		lineCount++;
		//reading First line of file
		if(lineCount % 5 == 1){
		//	cout << line << endl;
			replace(line.begin(), line.end(), '\n', ' ');
			q.question = line;
		//	cout << q.question << endl;
		}
		//reading second line of file the correct answer
		else if(lineCount % 5 == 2){
			q.correctAnswer = line;
			q.answers.push_back(line);
		}
		//rest of answers
		else{
			q.answers.push_back(line);
		}
		//Checking if questions and answer blocks have been read
		if(lineCount % 5 == 0){
            random_device rd;
            mt19937 g(rd());
            shuffle(q.answers.begin(), q.answers.end(), g); //Shuffling answer vector
			questions.push_back(q);
			q.answers.clear();
		}
		
	}
	infile.close();

}
int main(){
	srand(time(NULL));
	vector<Questions> questions;
	string fileName ="questions.txt";
	readJeopardy(fileName,questions);
	random_shuffle(questions.begin(), questions.end());
	//declares timer
	chrono::steady_clock::time_point timer_start;
	//starts timer
	timer_start = chrono::steady_clock::now();
	//This will cout all of the question at once. Jeopardy.cc has a for loop that prints out one at a time and waits for a input. Input testing not fully complete but mostly works. You can delete this if you want.
/*	for(const auto& q: questions){
		cout << "==========QUESTION===========" << endl;
		cout << q.question << endl;
		cout << "=============================" << endl;
		for(size_t i =0; i < q.answers.size(); i++){
			cout << i+1 << ".) " << q.answers[i] << endl;
			}
			//
	}*/

	string question = "What is 2+2?";
	string answers = "1) 1\n2) 2\n3) 3\n4) 4";
	int correctAnswer = 4;
	//declares time passed variable
	chrono::duration<float> time_passed;

	int playerSwitcher = -1;
	int playerTurn = 1;
	int winner = 0;

	while(true){
		//playerSwitcher starts as -1, 
		//but each loop changes its sign
		playerSwitcher *= -1;
		//if its -1, then its player twos turn
		if(playerSwitcher < 0) playerTurn = 2;
		//otherwise its player one's turn. 
		//we start w/ player 1
		else playerTurn = 1;
		
		cout << "\nPLAYER " << playerTurn << endl; 
		cout << question << endl;
		cout << answers << endl;

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
		if(time_passed > chrono::seconds(5)){
			cout << "\nYou ran out of time!" << endl;
			break;
		}
	}
	//it only breaks on the loser's turn
	//so this declares the other person the winner.
	if(playerSwitcher < 0) winner = 1;
	else winner = 2;
	cout << "Player " << winner << " wins!" << endl;
}
