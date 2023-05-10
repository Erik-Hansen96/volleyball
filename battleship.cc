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
	vector<vector<char>> player1Personal(10, vector<char>(10, '#'));

	/*
	cout << "Player " << winner << " place your ships\n" << endl;
	vector<vector<char>> shipBank = {
        {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', ' '},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', ' '},
        {'O', 'O', 'O', 'O', 'O', 'O', ' ', ' ', ' ', ' '},
        {'O', 'O', 'O', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };
	for(const auto &row : shipBank){
		for(const auto &col : row){
			cout  << col << "   ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Enter a letter and number (like A5)" << endl;
	char letter;
	int num;
	cin >> letter;
	cin >> num;
	letter = toupper(letter);
	int letterCord = letter - letter;
	*/


}
