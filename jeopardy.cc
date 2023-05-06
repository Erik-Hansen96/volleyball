#include "/public/colors.h"
#include "/public/read.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>
#include <cstdlib>
using namespace std;
struct Questions{
	string question;
	string correctAnswer;
	vector<string> answers;
};

int main(){
	vector<Questions> questions;
	string fileName = "questions.txt";
	ifstream infile(fileName);
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
//	random_device rd;
//   mt19937 g(rd());
//  shuffle(questions.begin(), questions.end(), g);
	bool playerTurn = true;
	int playerOne = 0;
	int playerTwo = 0;
	//Input testing not fully complete but mostly works. 
	for(const auto& q : questions){
		cout << "==========QUESTION===========" << endl;
		cout << q.question << endl;
		cout << "=============================" << endl;
		for(size_t i =0; i < q.answers.size(); i++){
			cout << i+1 << ".) " << q.answers[i] << endl;
			}
		int choice = 0;
		cout << endl;
		cout << "Player " <<(playerTurn ? 1 : 2) << " turn." << endl;
		cout << "Enter a choice from 1-4: ";
		cin >> choice;
		if(choice >= 1 && choice <= 4){
			string userAnswer = q.answers[choice-1];//Getting answer from user choice
			if(userAnswer == q.correctAnswer){
				cout << "Correct!\n" << endl;
				if(playerTurn){//If true its player one turn else player two turn;
					playerOne++;
				}
				else { 
					playerTwo++; 
				}
			}
			else{
				cout << "Incorrect!\n" << endl;
				cout << "Correct answer was " << q.correctAnswer << endl;
			}
		}
		system("clear");
		if(playerOne == 10 or playerTwo == 10){
			break;
		}
		else{cout << "SCORE: " 
				  << "Player 1: " << playerOne
				  <<" Player 2: " << playerTwo << endl;}
		playerTurn = !playerTurn; //Alteranting player turns;
		cout << endl;
	}
	system("clear");
	if(playerOne == 10) cout << "Player 1 is the WINNER!" << endl;
	else { cout << "Player 2 is the WINNER!" << endl;}
}

















