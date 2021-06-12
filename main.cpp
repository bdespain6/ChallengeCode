#include <iostream>
#include<sstream>
#include<fstream>
#include <vector>

using namespace std;
//This function allows the player to decide if they want to go first or second
bool FirstSecondChoice() {
	cout << "Do you want to go first or second? (Press f to go first or s to go second)\n";
	char order = ' ';
	cin >> order;
	if (order == 'f') {
		return true;
	}
	else if (order == 's') {
		return false;
	}
	//If the value received is not valid this function will continue to call itself until they enter either an f or an s
	else {
		cout << "Please enter a valid Character\n";
		return FirstSecondChoice();
	}
}
//Allows the player to decide if he wants to go first or second
bool PlayAgain() {
	char input = ' ';
	cout << "Do you want to play again? (Press y to play again and n to stop)\n";
	cin >> input;
	if(input == 'y'){
		return true;
	}
	else if(input == 'n'){
		return false;
	}
	//This makes sure that the player has enter a valid character to indicate if they will go first or second
	else{
		cout << "Please enter a valid Character\n";
		return PlayAgain();
	}

}
//This will list the open spots to make it easier for a player to choose where to put an X
void OpenSpotList(char board[3][3]) {
	cout << "The open Spots are:\n";
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			if (board[i][j] == '_')
				cout << " Row: " << i << " Column: " << j << "\n";
		}
	}
	cout << endl;
}
//This shows if a spot is valid 
bool isValidSpot(char board[3][3], int spotOne, int spotTwo) {
	if (board[spotOne][spotTwo] == 'X' || board[spotOne][spotTwo] == 'O') {
		cout << "This spot is already full\n";
		return false;
	}
	else return true;
}
//This will print out what the board currently looks like 
void PrintBoard(char board[3][3]) {
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			if (j != 2)
				cout << board[i][j] << "  ";
			else cout << board[i][j];


		}
		cout << endl;
	}
}
void PlayerSelectSpot(char board[3][3], int &spotOne, int &spotTwo) {
	
	cout << "Where would you like to place your X? (Enter in 2 numbers to place your X in an open square)\n";
	OpenSpotList(board);
	cout << "Type in the row number you want\n";
	cin >> spotOne;
	cout << "Type in the column number you want\n";
	cin >> spotTwo;
	while (spotOne > 2 || spotTwo > 2) {
		cout << "Please enter a value less than 3\n";
		if (spotOne > 2) {
			cout << "Reenter your row number";
			cin >> spotOne;
		}
		if (spotTwo > 2) {
			cout << "Reenter your column number\n";
			cin >> spotTwo;
		}
	}
	if (!isValidSpot(board, spotOne, spotTwo)) {
		return PlayerSelectSpot(board, spotOne, spotTwo);
	}
}
void PlayerTurn(char board[3][3]) {
	int spotOne = 0;
	int spotTwo = 0;
	PlayerSelectSpot(board, spotOne, spotTwo);
	board[spotOne][spotTwo] = 'X';
}
bool ComputerCheckSpot(char board[3][3], const int spotOne, const int spotTwo) {
	if (board[spotOne][spotTwo] == 'X' || board[spotOne][spotTwo] == 'O') {
		
		return false;
	}
	else return true;
}
//This creates a vector that will store all of the values of avaible spots
vector<pair<int,int>> ListOfSpots(char board[3][3]) {
	vector<pair<int, int>> listOfOpenSpots;
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			if (board[i][j] == '_')
				listOfOpenSpots.push_back(pair<int, int>(i, j));
		}
	}
	return listOfOpenSpots;
}
//The computer decides its move by using the rand function to select where it will play based on the size of the list of open spots
void ComputerMove(char board[3][3]) {
	
	int spotOne = 0;
	vector<pair<int, int>> freeSpots = ListOfSpots(board);
	if (freeSpots.size() != 1)
		spotOne = rand() % (freeSpots.size() - 1);
	else {
		spotOne = 0;
	}
	if (!ComputerCheckSpot(board, freeSpots.at(spotOne).first, freeSpots.at(spotOne).second)) {
		 ComputerMove(board);
	}
	else {
		board[freeSpots.at(spotOne).first][freeSpots.at(spotOne).second] = 'O';
		PrintBoard(board);
	}
}
//This function sees if a player or the computer has managed to get 3 in a row
bool CheckWinner(char board[3][3]) {
		//This is check of connected diagonals	
		if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] != '_') {
			return true;
		}
		//This is also a check of the other diagonals starting in the bottom left corner
		else if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] != '_') {			
			return true;
		}
		else if (board[0][0] == board[1][0] && board[2][0] == board[1][0] && board[1][0] != '_') {
			return true;
		}
		//If the winner has 3 in a row in the first column
		else if (board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][2] != '_') {
			return true;
		}
		//If the winner has 3 in a row straight down the middle column
		else if (board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[1][1] != '_') {			
			return true;
		}
		//If they have 3 straight down the far right column
		else if (board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[2][2] != '_') {
			return true;
		}
		//This is the result of if the winner has three in a row in the middle row
		else if (board[1][0] == board[1][1] && board[1][2] == board[1][1] && board[1][1] != '_') {
			return true;
		}
		//This is if the winner has three in a row in the bottom row
		else if (board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][2] != '_') {
			return true;
		}
		else {
			return false;
		}
	return false;
}
//This is where the game will be played 
void PlayGame(char board[3][3], bool& isFirst){
	//This runs the game if you choose to go first
	if (isFirst) {
		bool winner = false;
		int turn = 0;
		while (!winner) {
			PlayerTurn(board);
			PrintBoard(board);
			turn++;
			if (turn >= 5) {
				if (CheckWinner(board)) {
					cout << "Congratulations you won!\n";
					winner = true;
				}
			}
			if (turn == 9 && !winner) {
				winner = true;
				cout << "This was a tie!\n";
			}
			else if(!winner && turn < 9) {
				cout << "After the computer's move the board now looks like\n";
				ComputerMove(board);
				turn++;
				if (turn > 5) {
					if (CheckWinner(board)) {
						cout << "The Computer won this game!\n";
						winner = true;
					}
				}
			}
		}

	}
	//This is how it runs if you choose to go second
	else {
		int turn = 0;
		bool winner = false;
		while (!winner) {
			cout << "After the computer's move the board now looks like\n";
			ComputerMove(board);
			turn++;
			if (turn >= 5) {
				if (CheckWinner(board)) {
					cout << "The Computer won this game!\n";
					winner = true;
				}
			}
			if (turn == 9 && !winner) {
				winner = true;
				cout << "This was a tie!\n";
			}
			else if (turn < 9 && !winner) {
				PlayerTurn(board);
				PrintBoard(board);
				turn++;
				if (turn >= 5) {
					if (CheckWinner(board)) {
						cout << "Congratulations you won!\n";
						winner = true;
					}
				}
			}
		}
	}
}
//We set every position in the array to _ to represent an empty square and to make the board visible
void ResetBoard(char board[3][3]) {
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			board[i][j] = '_';
		}
	}
}

int main(int argc, char** argv) {
	//This will be where we store X's and O's
	char board[3][3];
	cout << "Welcome to TicTacToe against the CPU!\n";
	bool playAgain = true;
	while (playAgain) {
		bool isFirst = FirstSecondChoice();
		ResetBoard(board);
		PrintBoard(board);
		PlayGame(board, isFirst);
		playAgain = PlayAgain();
	}
	cout << "Thank you for playing we hope to see you again soon!\n";
	return 0;

}