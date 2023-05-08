#include "/public/colors.h"
#include "/public/read.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <unistd.h>
using namespace std;
struct Questions{
	string question;
	string correctAnswer;
	vector<string> answers;
};

int main(){
	srand(time(NULL));
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
			//Replacing \n with endl;
			string find = "\\n";  
			string replace = "\n";
			size_t pos = 0;
			while ((pos = line.find(find, pos)) != string::npos) {
				line.replace(pos, find.length(), replace);
				pos += replace.length();
			}
			q.question = line;
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
			random_shuffle(q.answers.begin(), q.answers.end()); //Shuffling answer vector
			questions.push_back(q);
			q.answers.clear();
		}

	}
	infile.close();
	//	random_shuffle(questions.begin(), questions.end());
	bool playerTurn = true;
	int playerOne = 0;
	int playerTwo = 0;
	system("clear"); 
	//Input testing not fully complete but mostly works. 
	for(const auto& q : questions){
		system("clear");
		if(playerOne == 10 or playerTwo == 10){
			break;
		}
		cout << endl;
		cout << endl;
		cout << BOLDYELLOW << "SCORE \n" 
			<< "Player 1: " << playerOne
			<<" Player 2: " << playerTwo << RESET << endl;
		cout << endl;
		cout << endl;	
		cout <<BOLDBLUE << "==========QUESTION===========" <<RESET<< endl;
		cout << q.question << endl;
		cout <<BOLDBLUE << "=============================" <<RESET<< endl;
		for(size_t i =0; i < q.answers.size(); i++){
			cout <<BOLDCYAN << i+1 << ".) "<<RESET << q.answers[i] << endl;
		}
		int choice = 0;
		cout << endl;
		cout <<BOLDMAGENTA<< "Player " <<(playerTurn ? 1 : 2) << " turn." << RESET<< endl;
		cout <<BOLDYELLOW << "Enter a choice from 1-4: " << RESET << endl;
		cin >> choice;
		if(choice >=1 and choice <= 4){
			string userAnswer = q.answers[choice-1];//Getting answer from user choice
			if(userAnswer == q.correctAnswer){
				cout <<BOLDGREEN << "Correct!\n" << RESET<< endl;
				if(playerTurn){//If true its player one turn else player two turn;
					playerOne++;
				}
				else { 
					playerTwo++; 
				}
			}
			else{
				cout << BOLDRED << "Incorrect!\n" << RESET << endl;
				cout << BOLDGREEN <<"Correct answer: " <<RESET << " ' "<< q.correctAnswer << " ' " <<endl;
			}
		}
		//If choice is not a int for 1-4
		else if(cin.fail() or choice != 1 or choice !=2 or choice !=3 or choice != 4)
		{
			cout <<BOLDRED << "INVALID ANSWER CHOICE" << RESET<< endl;
		}
		for(int i = 4; i > 0; i--){
			sleep(1);
			cout <<BOLDWHITE<< i <<RESET << " ";
		}
		playerTurn = !playerTurn; //Alteranting player turns;
		cout << endl;
		cin.clear(); //clear the cin.
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discards remaining input
		system("clear");
	}
	//END OF GAME
	system("clear");
	if(playerOne == 10) cout << "Player 1 is the WINNER!" << endl;
	else { cout << "Player 2 is the WINNER!" << endl;}
}

















