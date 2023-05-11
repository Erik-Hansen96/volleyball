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
		cout << "PLAYER " << playerTurn << endl << endl;
		printMap(playerMap);
		cout << endl;
		printShips(shipBank);
		cout << endl;
		cout << "Place your ships!" << endl;
		cout << "Select a ship to add! (Enter C, B, S, or P)\n" << endl;
		char shipChoice;
		cin >> shipChoice;
		shipChoice = toupper(shipChoice);

		if(ships.find(shipChoice) != string::npos){
			ships.erase(ships.find(shipChoice), 1);
		} else {
			cout << "You have no more " << shipChoice << " ships!" << endl;
			cout << "Please pick another" << endl;
			sleep(1);
			system("clear");
			continue;
		}
		cout << ships << endl;
		for(size_t i = 0; i < shipBank.at(0).size(); i++){
			if(shipBank.at(i).at(0) == shipChoice){
				for(int j = 0; j < 5; j++){ 
					//printShips(shipBank);
					shipBank.at(j).erase(shipBank.at(j).begin());
				}
			break;
			}
		}

		cout << "Where would do you want to place your ship?" << endl;
		cout << "Enter a letter and number (like A5)" << endl;
		char letter;
		int num;
		cin >> letter;
		cin >> num;
		letter = toupper(letter);
		int letterCord = letter - 65;
		vector<vector<char>> or1 = playerMap;
		vector<vector<char>> or2 = playerMap;
		vector<vector<char>> or3 = playerMap;
		vector<vector<char>> or4 = playerMap;
		cout << num << letterCord << endl;
		for(int i = 0; i < 5; i++){
			playerMap.at(num).at(letterCord) = shipChoice;
		}
	//	system("clear");
	
		if(ships.empty()) break;
	}
}

int main(){
	int winner = 1;
	vector<vector<char>> grid(10, vector<char>(10, '#'));
	system("clear");
	/*
	cout << "  A B C D E F G H I J" << endl;
	int numCol = 0;
	for(const auto &row : grid){
		cout << numCol++ << " ";
		for(const auto &col : row){
			cout << col << " ";
		}
		cout << endl;
	}
	*/
//	printMap(grid);
//	cout << endl;
		vector<vector<char>> player1Map(10, vector<char>(10, '#'));
		vector<vector<char>> player2Map(10, vector<char>(10, '#'));
//		cout << "Your battleships: " << endl << endl;
//		printMap(player1Map);
		
//		cout << "Player " << winner << " place your ships\n" << endl;
		vector<vector<char>> shipBank1 = {
        	{'C', 'B', 'B', 'S', 'S', 'S', 'P', 'P', 'P', 'P'},
        	{'C', 'B', 'B', 'S', 'S', 'S', 'P', 'P', 'P', 'P'},
        	{'C', 'B', 'B', 'S', 'S', 'S', ' ', ' ', ' ', ' '},
        	{'C', 'B', 'B', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        	{'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    	};
		vector<vector<char>> shipBank2 = {
        	{'C', 'B', 'B', 'S', 'S', 'S', 'P', 'P', 'P', 'P'},
        	{'C', 'B', 'B', 'S', 'S', 'S', 'P', 'P', 'P', 'P'},
        	{'C', 'B', 'B', 'S', 'S', 'S', ' ', ' ', ' ', ' '},
        	{'C', 'B', 'B', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        	{'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    	};
		addShip(player1Map, shipBank1, 1);
		addShip(player2Map, shipBank2, 2);
		/*
		cout << endl;
		cout << "Place your ship!" << endl;	
		cout << "Enter a letter and number (like A5)" << endl;
		char letter;
		int num;
		cin >> letter;
		cin >> num;
		letter = toupper(letter);
		int letterCord = letter - letter;
*/

	cout << "swag" << endl;
}
