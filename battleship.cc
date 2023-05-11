#include <iostream>
#include <vector>
#include <cctype>
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
void addShip(vector<vector<char>> &playerMap, vector<vector<char>> &shipBank){
	cout << "Place your ship!" << endl;
	cout << "Select a ship to add! (Enter C, B, D, S, or P)" << endl;
	char shipChoice;
	cin >> shipChoice;
	shipChoice = toupper(shipChoice);
	for(size_t i = 0; i < shipBank.at(0).size(); i++){
		if(shipBank.at(i).at(0) == shipChoice){
			for(int j = 0; j < 5; j++){ 
				shipBank.at(i).erase(shipBank.at(i).begin() + j);
			}
		continue;
		}
	}
	printShips(shipBank);
	return;
	cout << endl << endl << endl;
	cout << shipBank.at(0).at(0) << " [0][0]" << endl;
	cout << shipBank.at(0).at(1) << " [0][1]" << endl;
	cout << shipBank.at(1).at(0) << " [1][0]" << endl;

	cout << "Enter a letter and number (like A5)" << endl;
	char letter;
	int num;
	cin >> letter;
	cin >> num;
	letter = toupper(letter);
	int letterCord = letter - letter;
	printShips(shipBank);
	

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
	printMap(grid);
	cout << endl;
		vector<vector<char>> player1Map(10, vector<char>(10, '#'));
		cout << "Your battleships: " << endl << endl;
		printMap(player1Map);
		
		cout << "Player " << winner << " place your ships\n" << endl;
		vector<vector<char>> shipBank = {
        	{'C', 'B', 'B', 'S', 'S', 'S', 'P', 'P', 'P', 'P'},
        	{'C', 'B', 'B', 'S', 'S', 'S', 'P', 'P', 'P', 'P'},
        	{'C', 'B', 'B', 'S', 'S', 'S', ' ', ' ', ' ', ' '},
        	{'C', 'B', 'B', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        	{'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    	};
		for(const auto &row : shipBank){
			for(const auto &col : row){
				cout << col << "   ";
			}
			cout << endl;
		}
		addShip(player1Map, shipBank);
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


}
