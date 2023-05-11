#include <iostream>
#include <vector>
#include <cctype>
#include <unistd.h>
using namespace std;

void printMap(vector<vector<char>> grid){
	cout << "  A B C D E F G H I J" << endl;
	int numCol = 0;
	for(const auto &row : grid){
		cout << numCol++ << " ";
		for(const auto &col : row){
			cout << col << " ";
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
				cout << col << " ";
			}
			cout << "\t\t\t";
			if(display2){
				for(const auto &col : grid2.at(numCol-1)){
					cout << col << " ";
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
					cout << col << " ";
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
		cout << "PLAYER " << playerTurn << endl << endl;
		printMap(playerMap);
		cout << endl;
		printShips(shipBank);
		cout << endl;
		cout << "Place your ships!" << endl;
		cout << "Select a ship to add! (Enter C, B, S, or P)\n" << endl;
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
			cout << "You have no more " << shipChoice << " ships!" << endl;
			cout << "Please pick another" << endl;
			sleep(3);
			system("clear");
			continue;
		}

		cout << "Where would do you want to place your ship?" << endl;
		cout << "Enter a letter and number (like A5)" << endl;
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
			cout << "That ship doesn't fit there!" << endl;
			sleep(3);
			continue;
		}

		int orientation;
		cout << "1)\t\t\t\t       2)\n" << endl;
		printOrient(or1, or2, display1, display2);
		
		cout << "\n\n\n\n";
		cout << "3)\t\t\t\t       4)\n" << endl;
		printOrient(or3, or4, display3, display4);
		cout << "\nChoose an orientation (1,2,3,4)" << endl;
		cin >> orientation;
		if(orientation != 1 and orientation != 2 and orientation != 3 and orientation != 4){
			cout << "Invalid choice!" << endl;
			continue;
		}
		if(orientation == 1){
			if(!display1){
				cout << "Invalid choice!" << endl;
				sleep(2);
				continue;
			} else {
				playerMap = or1;
			}
		}
		if(orientation == 2){
			if(!display2){
				cout << "Invalid choice!" << endl;
				sleep(2);
				continue;
			} else {
				playerMap = or2;
			}
		}
		if(orientation == 3){
			if(!display3){
				cout << "Invalid choice!" << endl;
				sleep(2);
				continue;
			} else {
				playerMap = or3;
			}
		}
		if(orientation == 4){
			if(!display4){
				cout << "Invalid choice!" << endl;
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
	int winner = 1;
	vector<vector<char>> p1ocean(10, vector<char>(10, '#'));
	vector<vector<char>> p2ocean(10, vector<char>(10, '#'));
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
	cout << "You've added all your ships!" << endl;
	cout << "\nNext player's turn to add ships" << endl;
	sleep(3);
	addShip(player2Map, shipBank2, 2);
	cout << "LETS FIGHT!!" << endl;
	sleep(3);
	while(true){	
		system("clear");
		printMap(p1ocean);
		printMap(player1Map);
	}
	cout << "swag" << endl;
}
