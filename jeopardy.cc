#include "colors.h"
#include "read.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <unistd.h>
#include "common.h"
using namespace std;
struct Questions{
	string question;
	string correctAnswer;
	vector<string> answers;
};
int main(){
	vector<vector<char>> player1Ocean(10, vector<char>(10, '~'));
	vector<vector<char>> player2Ocean(10, vector<char>(10, '~'));
	vector<vector<char>> player1Map(10, vector<char>(10, '~'));
	vector<vector<char>> player2Map(10, vector<char>(10, '~'));	
	bool firstTime = true;
	bool playerTurn = true;
	battleship(player1Ocean, player2Ocean, player1Map, player2Map, firstTime, playerTurn);
	firstTime = false;
	srand(time(NULL));
	vector<Questions> questions;
	string fileName = "questions.txt";
	ifstream infile(fileName);
	if(!infile.is_open()){
		cerr <<BOLDRED<< "File failed to open!" <<RESET<< endl;
		return 1;
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
			//Replacing \n with endl;
			string find = "\\n";
			string replace = "\n";
			size_t pos = 0;
			while((pos = line.find(find,pos)) != string::npos){
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
	random_shuffle(questions.begin(), questions.end());
	bool player1Win = false;
	bool player2Win = false;
	int playerOne = 0;
	int playerTwo = 0;
	system("clear"); 

	chrono::duration<float> time_passed;
	chrono::duration<float> prevTime = chrono::seconds(100000);;
		
	for(const auto& q : questions){
		bool resetTime = false;
		chrono::steady_clock::time_point timer_start;
		system("clear");
		cout << BOLDYELLOW << "SCORE \n" 
			<< "Player 1: " << playerOne
			<<" Player 2: " << playerTwo << RESET << endl;
		cout << endl;
		//"prevTime" is set to 100000 before the loop (just a random number) 
		//if its equal to that, then dont display a time cuz that means its first persons turn
		//otherwise display how long the last person took to answer

		if(prevTime != chrono::seconds(100000)){
			cout << BOLDYELLOW << "YOU HAVE " << setprecision(2) << prevTime.count() << " SECONDS TO ANSWER." << RESET << endl;
		}
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

		//Start timer
		timer_start = chrono::steady_clock::now();
		cout << endl;
		//take answer
		cin >> choice;
		//End timer
		time_passed = chrono::steady_clock::now() - timer_start;
		//if we're over the prevTime, break;
		if(time_passed > prevTime){
			cout << BOLDRED << "You ran out of time!\n" << RESET << endl;
			sleep(1);
			battleship(player1Ocean, player2Ocean, player1Map, player2Map, firstTime, !playerTurn);
			cin.clear(); //clear the cin.
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discards remaining input
			resetTime = true;
		}
		if(!resetTime){	
			if(choice >=1 and choice <= 4){
				string userAnswer = q.answers[choice-1];//Getting answer from user choice
				if(userAnswer == q.correctAnswer){
					cout <<BOLDGREEN << "Correct!\n" << RESET<< endl;
					sleep(2);
					if(playerTurn){
					//If true its player one turn else player two turn;
						playerOne++;
					}
					else { 
						playerTwo++; 
					}
				}
				else{
					cout << BOLDRED << "Incorrect!\n" << RESET << endl;
					cout << BOLDGREEN <<"Correct answer: " <<RESET << " ' "<< q.correctAnswer << " ' " <<endl;
					sleep(2);
					battleship(player1Ocean, player2Ocean, player1Map, player2Map, firstTime, !playerTurn);
					cin.clear(); //clear the cin.
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discards remaining input
					resetTime = true;
				}
			}
		}
		//If choice is not a int for 1-4
		if(choice != 1 and choice !=2 and choice !=3 and choice != 4)
		{
			cout <<BOLDRED << "INVALID ANSWER CHOICE" << RESET<< endl;
		}
		cout << endl;
		cin.clear(); //clear the cin.
		system("clear");
		if(!playerTurn){
			for(size_t i = 0; i < player1Map.size(); i++){
				auto it = find(player1Map.at(i).begin(), player1Map.at(i).end(), 'C');
				if(player1Map.at(i).end() != it){ 
					player2Win = false;
					break;
				}
				it = find(player1Map.at(i).begin(), player1Map.at(i).end(), 'B');
				if(player1Map.at(i).end() != it){ 
					player2Win = false;
					break;
				}
				it = find(player1Map.at(i).begin(), player1Map.at(i).end(), 'S');
				if(player1Map.at(i).end() != it){ 
					player2Win = false;
					break;
				}
				it = find(player1Map.at(i).begin(), player1Map.at(i).end(), 'P');
				if(player1Map.at(i).end() != it){ 
					player2Win = false;
					break;
				}
				player2Win = true;
			}
		}
		if(playerTurn){
			for(size_t i = 0; i < player2Map.size(); i++){
				auto it = find(player2Map.at(i).begin(), player2Map.at(i).end(), 'C');
				if(player2Map.at(i).end() != it){ 
					player1Win = false;
					break;
				}
				it = find(player2Map.at(i).begin(), player2Map.at(i).end(), 'B');
				if(player2Map.at(i).end() != it){ 
					player1Win = false;
					break;
				}
				it = find(player2Map.at(i).begin(), player2Map.at(i).end(), 'S');
				if(player2Map.at(i).end() != it){ 
					player1Win = false;
					break;
				}
				it = find(player2Map.at(i).begin(), player2Map.at(i).end(), 'P');
				if(player2Map.at(i).end() != it){ 
					player1Win = false;
					break;
				}
				player1Win = true;
			}
		}
		if(resetTime) prevTime = chrono::seconds(100000);
		else prevTime = time_passed;
		playerTurn = !playerTurn; //Alteranting player turns;
		if(player1Win or player2Win) break;
	}
	//END OF GAME
	system("clear");
	if(player2Win) cout << BOLDGREEN << "Player 2 is the WINNER!" << RESET << endl;
	else cout << BOLDGREEN << "Player 1 is the WINNER!" << RESET << endl;
}

















