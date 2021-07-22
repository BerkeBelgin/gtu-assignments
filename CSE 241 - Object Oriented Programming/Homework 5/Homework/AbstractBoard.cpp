#include "AbstractBoard.h"

using namespace ab;

int AbstractBoard::boardCount = 0;

AbstractBoard::AbstractBoard(){
	AbstractBoard::boardCount++;
}

AbstractBoard::~AbstractBoard(){
	AbstractBoard::boardCount--;
}

int AbstractBoard::getBoardSizex(){
	return boardSizex;
}

int AbstractBoard::getBoardSizey(){
	return boardSizey;
}

int AbstractBoard::getEmptyCellx(){
	return emptyCellx;
}

int AbstractBoard::getEmptyCelly(){
	return emptyCelly;
}

//A utility function which helps to print the board
string AbstractBoard::formatStringByDigitCount(string element, string placeHolder, int digits){
	string placeHolders = "";
	for(int i = 0; i < digits - element.length(); i++) placeHolders += placeHolder;
	return placeHolders + element;
}

//A utility function which converts written numbers in a string into int
int AbstractBoard::convertToInt(string number){
	int result = 0;
	int multiplier;
	for(int i = number.length() - 1; i >= 0; i--){
		multiplier = 1;
		for(int n = i + 1; number.length() - n > 0; n++)multiplier *= 10;
		result += (number[i] - '0') * multiplier;
	}
	return result;
}

//Prints the current state of the board.
void AbstractBoard::print(){
	for(int y = 0; y < boardSizey; y++){
		for(int x = 0; x < boardSizex; x++){
			if((*this)(y, x) == 0) cout << "##";
			else if((*this)(y, x) == -1) cout << formatStringByDigitCount(" ", " ", to_string(boardSizex * boardSizey - 1).length());
			else cout << formatStringByDigitCount(to_string((*this)(y, x)), "0", to_string(boardSizex * boardSizey - 1).length());
			cout << " ";
		}
		cout << endl;
	}
}

//Function that loads the board from a text file.
void AbstractBoard::readFromFile(string filename){
	ifstream file;
	
	int tempBoardSizex = 0;
	int tempBoardSizey = 0;
		
	file.open(filename, ios::in);
	if(!file.is_open()){
		cout << "The file you are looking does not exist" << endl << endl;
		return;
	}

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
		if(tempBoardSizex == 0){
			tempBoardSizex = boardSizexCount;
		} 
		else if(tempBoardSizex != boardSizexCount){
			cout << "A mismatch between column and row sizes is detected. Please fix it and try again" << endl << endl;
			return;
		}
		tempBoardSizey++;
	}
	file.close();
	
	setSize(tempBoardSizex, tempBoardSizey);
	
	string cell;
	
	file.open(filename, ios::in);
	for(int y = 0; y < boardSizey; y++){
		for(int x = 0; x < boardSizex; x++){
			file >> cell;
			if(cell == formatStringByDigitCount("b", "b", to_string(boardSizex * boardSizey - 1).length())){
				emptyCellx = x;
				emptyCelly = y;
				setCellValue(y, x, -1);
			}
			else{
				setCellValue(y, x, convertToInt(cell));
			}
		}
	}
	file.close();
	
	cout << "File is read successfuly" << endl;
}

//The function where we save current game state to a text file.
void AbstractBoard::writeToFile(string filename){
	ofstream file;
	
	file.open(filename.c_str(), ios::out);
	if(!file.is_open()){
		cout << endl << "The name you entered is not valid" << endl << endl;
		return;
	}
	
	string stream;
	for(int y = 0; y < boardSizey; y++){
		stream = "";
		for(int x = 0; x < boardSizex; x++){
			if((*this)(y, x) == -1)stream += formatStringByDigitCount("b", "b", to_string(boardSizex * boardSizey - 1).length());
			else stream += formatStringByDigitCount(to_string((*this)(y, x)), "0", to_string(boardSizex * boardSizey - 1).length());
			
			if(x == boardSizex - 1 && y == boardSizey - 1)stream += "\0";
			else if(x == boardSizex - 1 && y != boardSizey - 1)stream += "\n";
			else stream += " ";
		}
		file << stream;
	}
	file.close();
	
	cout << "File is saved successfuly" << endl <<  endl;
}

//Function that resets the board with correct numbers.
void AbstractBoard::reset(){
	for(int y = 0; y < boardSizey; y++){
		for(int x = 0; x < boardSizex; x++){
			setCellValue(y, x, y * boardSizey + (x + 1));
		}
	}

	emptyCellx = boardSizex - 1;
	emptyCelly = boardSizey - 1;
	setCellValue(emptyCelly, emptyCellx, -1);
}

//The function which handles shift operation from a cell into empty cell
void AbstractBoard::move(char move){
	switch(move){
	case 'L':
	case 'l':
		if(emptyCellx != 0 && (*this)(emptyCelly, emptyCellx - 1) != 0){
			int temp = (*this)(emptyCelly, emptyCellx);
			setCellValue(emptyCelly, emptyCellx, (*this)(emptyCelly, emptyCellx - 1));
			setCellValue(emptyCelly, emptyCellx - 1, temp);
			emptyCellx--;
			lastMove = 'l';
			moveCount++;
		}
		break;
	case 'R':
	case 'r':
		if(emptyCellx != boardSizex - 1 && (*this)(emptyCelly, emptyCellx + 1) != 0){
			int temp = (*this)(emptyCelly, emptyCellx);
			setCellValue(emptyCelly, emptyCellx, (*this)(emptyCelly, emptyCellx + 1));
			setCellValue(emptyCelly, emptyCellx + 1, temp);
			emptyCellx++;
			lastMove = 'r';
			moveCount++;
		}
		break;
	case 'U':
	case 'u':
		if(emptyCelly != 0 && (*this)(emptyCelly - 1, emptyCellx) != 0){
			int temp = (*this)(emptyCelly, emptyCellx);
			setCellValue(emptyCelly, emptyCellx, (*this)(emptyCelly - 1, emptyCellx));
			setCellValue(emptyCelly - 1, emptyCellx, temp);
			emptyCelly--;
			lastMove = 'u';
			moveCount++;
		}
		break;
	case 'D':
	case 'd':
		if(emptyCelly != boardSizey - 1 && (*this)(emptyCelly + 1, emptyCellx) != 0){
			int temp = (*this)(emptyCelly, emptyCellx);
			setCellValue(emptyCelly, emptyCellx, (*this)(emptyCelly + 1, emptyCellx));
			setCellValue(emptyCelly + 1, emptyCellx, temp);
			emptyCelly++;
			lastMove = 'd';
			moveCount++;
		}
		break;
	}
}

//Checks if there is any wrong placed cells, if not ends the game.
bool AbstractBoard::isSolved(){
	int currentCellValue = 0;
	for(int y = 0; y < boardSizey; y++){
		for(int x = 0; x < boardSizex; x++){
			if((*this)(y, x) != 0){
				currentCellValue++;
				if((*this)(y, x) != -1 && (*this)(y, x) != currentCellValue)return false;
			}
		}
	}
	return true;
}

//Operator that checks if two board configurations are the same in two different Board objects.
bool AbstractBoard::operator == (AbstractBoard &abstractBoard){
	if(boardSizey == abstractBoard.getBoardSizey() && boardSizex == abstractBoard.getBoardSizex()){
		 for(int y = 0; y < boardSizey; y++){
		 	for(int x = 0; x < boardSizex; x++){
		 		if((*this)(y, x) != abstractBoard(y, x))return false;
		 	}
		 }
	 }
	 return true;
}

//Function that gets global board count.
int AbstractBoard::getNumberOfBoards(){
	return boardCount;
}

//Function that gets last move.
char AbstractBoard::getLastMove(){
	return lastMove;
}

//Function that gets move count.
int AbstractBoard::getNumberOfMoves(){
	return moveCount;
}
