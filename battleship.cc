#include <iostream>
#include <vector>
using namespace std;

int main(){
	int winner = 1;
	vector<vector<char>> grid(10, vector<char>(10, '#'));
	system("clear");
	cout << "  A B C D E F G H I J" << endl;
	int num = 0;
	for(const auto &row : grid){
		cout << num++ << ' ';
		for(const auto &col : row){
			cout << col << ' ';
		}
		cout << endl;
	}
	cout << "Player " << winner << " place your ships\n" << endl;
	vector<vector<char>> shipBank;
	int shipSize = 5;
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < shipSize; j++){
			shipBank.at(i).at(j) = 'O';
			for(int k = 5; k > shipSize; k--){
				shipSize--;
				shipBank.at(i).at(j) = '#';
			}
		}
	}
	for(auto &row : shipBank){
		for(auto &col : row){
			cout << col << ' ';
		}
		cout << endl;
	}


}
