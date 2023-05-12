#include <iostream>
#include <vector>
#include <cctype>
#include <unistd.h>
#include "/public/colors.h"
#include "/public/read.h"
#include <cstdlib>
using namespace std;

void printMap(vector<vector<char>> grid){
	cout <<BOLDMAGENTA<< "  A B C D E F G H I J" <<RESET<< endl;
	int numCol = 0;
	for(const auto &row : grid){
		cout << BOLDCYAN << numCol++ <<RESET<< " ";
		for(const auto &col : row){
			if(col == 'X'){
				cout << BOLDGREEN << col << " " << RESET;
			} else if(col == 'O'){
				cout << BOLDRED << col << " " << RESET;
			} else if(col == '#') {
			cout << BOLDBLUE << col << " " << RESET;
			} else {
			cout << BOLDWHITE << col << " " << RESET;
			}
		}
		cout << endl;
	}
}
void printOrient(vector<vector<char>> grid, vector<vector<char>> grid2, bool display1, bool display2){
	int numCol = 0;
	if(display1){
		for(const auto &row : grid){
			numCol++;
			for(const auto &col : row){
				if(col == '#'){
					cout << BOLDBLUE << col << " " << RESET;
				} else {
					cout << BOLDWHITE << col << " " << RESET;
				}
			}
			cout << "\t\t\t";
			if(display2){
				for(const auto &col : grid2.at(numCol-1)){
					if(col == '#'){
						cout << BOLDBLUE << col << " " << RESET;
					} else {
						cout << BOLDWHITE << col << " " << RESET;
					}
				}
			}
			cout << endl;
		}
	} else if(display2) {
		for(const auto &row : grid){
			numCol++;
			for(const auto &col : row){
				cout << " " << " ";
			}
			cout << "\t\t\t";
			if(display2){
				for(const auto &col : grid2.at(numCol-1)){
					if(col == '#'){
						cout << BOLDBLUE << col << " " << RESET;
					} else {
						cout << BOLDWHITE << col << " " << RESET;
					}
				}
			}
			cout << endl;
		}
	}
}
void printShips(vector<vector<char>> shipBank){
	for(const auto &row : shipBank){
		for(const auto &col : row){
        	cout << col << "   ";
        }
        cout << endl;
	}
}
void addShip(vector<vector<char>> &playerMap, vector<vector<char>> &shipBank, int playerTurn){
	string ships = "CBBSSSPPPP";
	while(true){
		system("clear");
		cout <<BOLDYELLOW << "PLAYER " << playerTurn <<RESET<< endl << endl;
		printMap(playerMap);
		cout << endl;
		printShips(shipBank);
		cout << endl;
		cout <<BOLDGREEN<< "Place your ships!" << RESET<< endl;
		cout <<BOLDGREEN<< "Select a ship to add! (Enter C, B, S, or P)\n" <<RESET<< endl;
		char shipChoice;
		int shipSize;
		cin >> shipChoice;
		shipChoice = toupper(shipChoice);
		if(shipChoice == 'C') shipSize = 5;
		if(shipChoice == 'B') shipSize = 4;
		if(shipChoice == 'S') shipSize = 3;
		if(shipChoice == 'P') shipSize = 2;

		if(ships.find(shipChoice) != string::npos){
		} else {
			cout <<BOLDRED<< "You have no more " << shipChoice << " ships!" <<RESET<< endl;
			cout <<BOLDWHITE<< "Please pick another" <<RESET<< endl;
			sleep(3);
			system("clear");
			continue;
		}

		cout <<BOLDGREEN<< "Where would do you want to place your ship?" <<RESET<< endl;
		cout <<BOLDYELLOW<<"Enter a letter and number (like A5)" <<RESET<< endl;
		char letter;
		size_t num;
		cin >> letter;
		cin >> num;
		letter = toupper(letter);
		size_t letterCord = letter - 65;
		system("clear");
		bool display1 = true;
		bool display2 = true;
		bool display3 = true;
		bool display4 = true;

		vector<vector<char>> or1 = playerMap;
		for(int i = 0; i < shipSize; i++){
			if(num < or1.size() and letterCord+i < or1.at(num).size() and or1.at(num).at(letterCord+i) == '#' ){
				or1.at(num).at(letterCord+i) = shipChoice;
			} else {
				display1 = false;
				break;
			}
		}

		vector<vector<char>> or2 = playerMap;
		for(int i = 0; i < shipSize; i++){
			if(num < or2.size() and letterCord-i < or2.at(num).size() and or2.at(num).at(letterCord-i) == '#'){
				or2.at(num).at(letterCord-i) = shipChoice;
			} else {
				display2 = false;
				break;
			}
		}		
		vector<vector<char>> or3 = playerMap;
		for(int i = 0; i < shipSize; i++){
			if(num+i < or3.size() and letterCord < or3.at(num).size() and or3.at(num+i).at(letterCord) == '#'){
				or3.at(num+i).at(letterCord) = shipChoice;
			} else {
				display3 = false;
				break;
			}
		}
		vector<vector<char>> or4 = playerMap;
		for(int i = 0; i < shipSize; i++){
			if(num-i < or4.size() and letterCord < or4.at(num).size() and or4.at(num-i).at(letterCord) == '#'){
				or4.at(num-i).at(letterCord) = shipChoice;
			} else { 
				display4 = false;
				break;
			}
		}
		if(!display1 and !display2 and !display3 and !display4){
			cout <<BOLDRED<< "That ship doesn't fit there!" <<RESET<< endl;
			sleep(3);
			continue;
		}

		int orientation;
		cout <<BOLDCYAN<< "1)\t\t\t\t       2)\n" << RESET << endl;
		printOrient(or1, or2, display1, display2);
		
		cout << "\n\n\n\n";
		cout << "3)\t\t\t\t       4)\n" <<RESET<< endl;
		printOrient(or3, or4, display3, display4);
		cout <<BOLDGREEN<< "\nChoose an orientation (1,2,3,4)" <<RESET<< endl;
		cin >> orientation;
		if(orientation != 1 and orientation != 2 and orientation != 3 and orientation != 4){
			cout <<BOLDRED<< "Invalid choice!" <<RESET<< endl;
			continue;
		}
		if(orientation == 1){
			if(!display1){
				cout <<BOLDRED<< "Invalid choice!" <<RESET<< endl;
				sleep(2);
				continue;
			} else {
				playerMap = or1;
			}
		}
		if(orientation == 2){
			if(!display2){
				cout <<BOLDRED<< "Invalid choice!" <<RESET<< endl;
				sleep(2);
				continue;
			} else {
				playerMap = or2;
			}
		}
		if(orientation == 3){
			if(!display3){
				cout <<BOLDRED<< "Invalid choice!" <<RESET<< endl;
				sleep(2);
				continue;
			} else {
				playerMap = or3;
			}
		}
		if(orientation == 4){
			if(!display4){
				cout <<BOLDRED<< "Invalid choice!" <<RESET<< endl;
				sleep(2);
				continue;
			} else {
				playerMap = or4;
			}
		}
		for(size_t i = 0; i < shipBank.at(0).size(); i++){
			if(shipBank.at(0).at(i) == shipChoice){
				for(int j = 0; j < 5; j++){ 
					shipBank.at(j).at(i) = ' ';
				}
				break;
			}
		}
		ships.erase(ships.find(shipChoice), 1);


		if(ships.empty()){
			system("clear");
			break;
		}
	}
}

int main(){
	system("clear");
	system("figlet -f big -c WELCOME TO BATTLESHIP!");
	sleep(5);
	system("clear");
	int winner = 1;
	vector<vector<char>> player1Ocean(10, vector<char>(10, '#'));
	vector<vector<char>> player2Ocean(10, vector<char>(10, '#'));
	vector<vector<char>> player1Map(10, vector<char>(10, '#'));
	vector<vector<char>> player2Map(10, vector<char>(10, '#'));	
	vector<vector<char>> shipBank1 = {
        {'C', 'B', 'B', 'S', 'S', 'S', 'P', 'P', 'P', 'P'},
        {'C', 'B', 'B', 'S', 'S', 'S', 'P', 'P', 'P', 'P'},
        {'C', 'B', 'B', 'S', 'S', 'S', ' ', ' ', ' ', ' '},
        {'C', 'B', 'B', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };
	vector<vector<char>> shipBank2 = shipBank1;
	addShip(player1Map, shipBank1, 1);
	cout <<BOLDGREEN<< "You've added all your ships!" << endl;
	cout << "\nNext player's turn to add ships" <<RESET<< endl;
	sleep(3);
	addShip(player2Map, shipBank2, 2);
	//cout << "LETS FIGHT!!" << endl;
	system("figlet -f big LETS FIGHT!!");
	sleep(3);
	bool playerTurn = true;
	while(true){	
		system("clear");
		if(playerTurn){
			cout <<BOLDYELLOW<< "PLAYER 1\n" <<RESET<< endl;	
			printMap(player1Ocean);
			cout << endl;
			printMap(player1Map);
			cout << endl;

		} else {
			cout <<BOLDYELLOW<< "PLAYER 2\n" <<RESET<< endl;
			printMap(player2Ocean);
			cout << endl;
			printMap(player2Map);
			cout << endl;
		}
		cout <<BOLDYELLOW<< "\nEnter a letter and number to strike!" <<RESET<< endl;
		char letter;
		size_t num;
		cin >> letter;
		cin >> num;
		letter = toupper(letter);
		size_t letterCord = letter - 65;
		if(playerTurn){
			if(num >= player2Map.size() or letterCord >= player2Map.at(num).size()){
				cout <<BOLDRED<< "Invalid input!" <<RESET<< endl;
				sleep(3);
				continue;
			}
			if(player2Map.at(num).at(letterCord) != '#'){
				cout <<BOLDGREEN<< "Hit!" <<RESET<< endl;
				player1Ocean.at(num).at(letterCord) = 'X';
				player2Map.at(num).at(letterCord) = 'X';
				sleep(3);
			} else {
				cout <<BOLDRED<< "Miss!" <<RESET<< endl;
				player1Ocean.at(num).at(letterCord) = 'O';
				player2Map.at(num).at(letterCord) = 'O';
				sleep(3);
			}
		} else {
			if(num >= player1Map.size() or letterCord >= player1Map.at(num).size()){
				cout <<BOLDRED<< "Invalid input!" <<RESET<< endl;
				sleep(3);
				continue;
			}
			if(player1Map.at(num).at(letterCord) != '#'){
				cout <<BOLDGREEN<< "Hit!" <<RESET<< endl;
				player2Ocean.at(num).at(letterCord) = 'X';
				player1Map.at(num).at(letterCord) = 'X';
				sleep(3);
			} else {
				cout <<BOLDRED<< "Miss!" <<RESET<< endl;
				player2Ocean.at(num).at(letterCord) = 'O';
				player1Map.at(num).at(letterCord) = 'O';
				sleep(3);
			}
		}
		playerTurn = !playerTurn;
	}
	cout << "swag" << endl;
}
