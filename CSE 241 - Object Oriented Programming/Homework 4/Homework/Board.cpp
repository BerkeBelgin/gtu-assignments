#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Board{
	private:
		vector<vector<int>> board;
		int emptyCellx;
		int emptyCelly;
		int moveCount = 0;
		char lastMove = 's';
		
	public:
		string formatStringByDigitCount(string, string, int);
		inline int convertToInt(string);
		bool moveLeftIsValid();
		bool moveRightIsValid();
		bool moveUpIsValid();
		bool moveDownIsValid();
		vector<vector<int>> getBoard();
		
		void print();
		void readFromFile();
		void writeToFile();
		void reset(bool);
		void setSize(int, int);
		void move(char);
		bool isSolved();
    int& operator () (int y, int x);
    friend bool operator == (Board &board1, Board &board2);
		char getLastMove();
		int getNumberOfMoves();
};

//A utility function which helps to print the board
string Board::formatStringByDigitCount(string element, string placeHolder, int digits){
	string placeHolders = "";
	for(int i = 0; i < digits - element.length(); i++) placeHolders += placeHolder;
	return placeHolders + element;
}

//A utility function which converts written numbers in a string into int
inline int Board::convertToInt(string number){
	int result = 0;
	int multiplier;
	for(int i = number.length() - 1; i >= 0; i--){
		multiplier = 1;
		for(int n = i + 1; number.length() - n > 0; n++)multiplier *= 10;
		result += (number[i] - '0') * multiplier;
	}
	return result;
}

//Checks if move left is valid.
bool Board::moveLeftIsValid(){
	return (emptyCellx != 0 && board[emptyCelly][emptyCellx - 1] != 0);
}

//Checks if move right is valid.
bool Board::moveRightIsValid(){
	return (emptyCellx != board[0].size() - 1 && board[emptyCelly][emptyCellx + 1] != 0);
}

//Checks if move up is valid.
bool Board::moveUpIsValid(){
	return (emptyCelly != 0 && board[emptyCelly - 1][emptyCellx] != 0);
}

//Checks if move down is valid.
bool Board::moveDownIsValid(){
	return (emptyCelly != board.size() - 1 && board[emptyCelly + 1][emptyCellx] != 0);
}

//Function that returns board 2d vector.
vector<vector<int>> Board::getBoard(){
	return board;
}
		
//Prints the current state of the board.
void Board::print(){
	for(int y = 0; y < board.size(); y++){
		for(int x = 0; x < board[0].size(); x++){
			if(board[y][x] == 0) cout << "##";
			else if(board[y][x] == -1) cout << formatStringByDigitCount(" ", " ", to_string(board[0].size() * board.size() - 1).length());
			else cout << formatStringByDigitCount(to_string(board[y][x]), "0", to_string(board[0].size() * board.size() - 1).length());
			cout << " ";
		}
		cout << endl;
	}
}

//Function that loads the board from a text file.
void Board::readFromFile(){
	string filename;
	bool success;
	ifstream file;
	
	int boardSizex = 0;
	int boardSizey = 0;
	
	do{
		success = true;
		
		do{
			cout << "Please enter the name of the text file without \".txt\": ";
			cin >> filename;
			
			filename += ".txt";
			file.open(filename, ios::in);
			if(!file.is_open()){
				cout << "The file you are looking does not exist" << endl << endl;
			}
		} while(!file.is_open());
		
		string stream;
		while(getline(file,stream)){
			bool inSpace = true;
			int boardSizexCount = 0;
			for(int i = 0; i < stream.length(); i++){
				if(stream[i] == ' ' && !inSpace){
					inSpace = true;
				}
				else if(stream[i] != ' ' &&  inSpace){
					inSpace = false;
					boardSizexCount++;
				}
			}
			if(boardSizex == 0){
				boardSizex = boardSizexCount;
			} 
			else if(boardSizex != boardSizexCount){
				success = false;
				cout << "A mismatch between column and row sizes is detected. Please fix it and try again" << endl << endl;
				break;
			}
			boardSizey++;
		}
		file.close();
	}while(!success);
	
	board.resize(boardSizey);
	for(int i = 0; i < board.size(); i++)board[i].resize(boardSizex);
	
	string stream;
	string cell;
	
	file.open(filename, ios::in);
	for(int y = 0; y < board.size(); y++){
		for(int x = 0; x < board[0].size(); x++){
			file >> cell;
			if(cell == formatStringByDigitCount("b", "b", to_string(board[0].size() * board.size() - 1).length())){
				emptyCellx = x;
				emptyCelly = y;
				board[y][x] = -1;
			}
			else{
				board[y][x] = convertToInt(cell);
			}
		}
	}
	file.close();
}

//The function where we save current game state
void Board::writeToFile(){
	ofstream file;
	string filename;
	
	do{
		cout << endl << "Please emptyCellx != 0 && board[emptyCelly][emptyCellx - 1] != 0 enter a filename without \".txt\": ";
		cin >> filename;
		
		filename += ".txt";
		file.open(filename.c_str(), ios::out);
		if(!file.is_open()){
			cout << endl << "Please enter a valid name" << endl << endl;
		}
	} while(!file.is_open());
	
	string stream;
	for(int y = 0; y < board.size(); y++){
		stream = "";
		for(int x = 0; x < board[0].size(); x++){
			if(board[y][x] == -1)stream += formatStringByDigitCount("b", "b", to_string(board[0].size() * board.size() - 1).length());
			else stream += formatStringByDigitCount(to_string(board[y][x]), "0", to_string(board[0].size() * board.size() - 1).length());
			
			if(x == board[0].size() - 1 && y == board.size() - 1)stream += "\0";
			else if(x == board[0].size() - 1 && y != board.size() - 1)stream += "\n";
			else stream += " ";
		}
		file << stream;
	}
	file.close();
	
	cout << endl << "File is saved successfuly" << endl;
}

//Function that resets the board with correct numbers.
void Board::reset(bool isJustCreated){
	if(isJustCreated){
		for(int y = 0; y < board.size(); y++){
			for(int x = 0; x < board[0].size(); x++){
				board[y][x] = (y * board.size() + (x + 1));
			}
		}
	}
	else{
		int cellValue = 1;
		for(int y = 0; y < board.size(); y++){
			for(int x = 0; x < board[0].size(); x++){
				if(board[y][x] != 0){
					board[y][x] = cellValue++;
				}
			}
		}
	}

	emptyCellx = board[0].size() - 1;
	emptyCelly = board.size() - 1;
	board[emptyCelly][emptyCellx] = -1;
}

//Function that creates the board.
void Board::setSize(int sizeX, int sizeY){
	board.resize(sizeY);
	for(int i = 0; i < sizeY; i++)board[i].resize(sizeX);
	reset(true);
}

//The function which handles shift operation from a cell into empty cell
void Board::move(char move){
	switch(move){
	case 'L':
	case 'l':
		if(moveLeftIsValid()){
			int temp = board[emptyCelly][emptyCellx];
			board[emptyCelly][emptyCellx] = board[emptyCelly][(emptyCellx) - 1];
			board[emptyCelly][emptyCellx - 1] = temp;
			emptyCellx--;
			lastMove = 'l';
			moveCount++;
		}
		break;
	case 'R':
	case 'r':
		if(moveRightIsValid()){
			int temp = board[emptyCelly][emptyCellx];
			board[emptyCelly][emptyCellx] = board[emptyCelly][emptyCellx + 1];
			board[emptyCelly][emptyCellx + 1] = temp;
			emptyCellx++;
			lastMove = 'r';
			moveCount++;
		}
		break;
	case 'U':
	case 'u':
		if(moveUpIsValid()){
			int temp = board[emptyCelly][emptyCellx];
			board[emptyCelly][emptyCellx] = board[emptyCelly - 1][emptyCellx];
			board[emptyCelly - 1][emptyCellx] = temp;
			emptyCelly--;
			lastMove = 'u';
			moveCount++;
		}
		break;
	case 'D':
	case 'd':
		if(moveDownIsValid()){
			int temp = board[emptyCelly][emptyCellx];
			board[emptyCelly][emptyCellx] = board[emptyCelly + 1][emptyCellx];
			board[emptyCelly + 1][emptyCellx] = temp;
			emptyCelly++;
			lastMove = 'd';
			moveCount++;
		}
		break;
	}
}

//Checks if there is any wrong placed cells, if not ends the game.
bool Board::isSolved(){
	int currentCellValue = 0;
	for(int y = 0; y < board.size(); y++){
		for(int x = 0; x < board[0].size(); x++){
			if(board[y][x] != 0){
				currentCellValue++;
				if(board[y][x] != -1 && board[y][x] != currentCellValue)return false;
			}
		}
	}
	return true;
}

//Operator which returns the element in y'th row and x'th column
int & Board::operator () (int y, int x){
    if(y < board.size() && x < board[0].size()){
    	return board[y][x];
    } else{
    	exit(0);
    }
}

//Operator that checks if two board configurations are the same in two different Board objects.
bool operator == (Board &board1, Board &board2){
	 if(board1.board.size() == board2.board.size() && board1.board[0].size() == board2.board[0].size()){
		 for(int y = 0; y < board1.board.size(); y++){
		 	for(int x = 0; x < board1.board[0].size(); x++){
		 		if(board1.board[y][x] != board2.board[y][x])return false;
		 	}
		 }
	 }
	 return true;
}

//Function that returns last move.
char Board::getLastMove(){
	return lastMove;
}

//Function that returns move count.
int Board::getNumberOfMoves(){
	return moveCount;
}
