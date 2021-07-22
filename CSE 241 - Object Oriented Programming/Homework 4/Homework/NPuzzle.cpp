#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Board.cpp"

using namespace std;

class NPuzzle{
	private:
		Board board;
		vector<Board> boards;
		
	public:
		bool isSolved();
		void solvePuzzleRecursive();
		string recursiveSolutionSearch(Board, int, char);
		Board getBoard();
		
		void print();
		void printReport();
		void readFromFile();
		void writeToFile();
		void shuffle(int);
		void reset(bool);
		void setSize();
		void moveRandom();
		void move(char moveChar);
		void solvePuzzle();
		friend ostream& operator << (ostream& out, NPuzzle& nPuzzle);
    friend void operator >> (istream& in,  NPuzzle& nPuzzle);
		int getNumberOfBoards();
};

bool NPuzzle::isSolved(){
	return board.isSolved();
}

//My recursive algorithm to solve puzzle from hw3 which is not used in this hw. (disabled)
void NPuzzle::solvePuzzleRecursive(){
	string solution = "";
	int intelligenceMoveLimit = 18;
	for(int intelligence = 0; solution == "" && intelligence < intelligenceMoveLimit; intelligence++){
		cout << "\033[H\033[J";
		print();
		cout << endl << "Calculating - " << (int)(((double)(intelligence + 1) / (double)intelligenceMoveLimit) * 100) << "%" << endl;
		
		string left = "";
		string right = "";
		string up = "";
		string down = "";
		
		if(board.moveLeftIsValid())  left  = recursiveSolutionSearch(board, intelligence, 'l');
		if(board.moveRightIsValid()) right = recursiveSolutionSearch(board, intelligence, 'r');
		if(board.moveUpIsValid())    up    = recursiveSolutionSearch(board, intelligence, 'u');
		if(board.moveDownIsValid())  down  = recursiveSolutionSearch(board, intelligence, 'd');
		
		string shortestPath = "";
		if((left  != "" && shortestPath == "") || (left  != "" && shortestPath != "" && left.size()  < shortestPath.size())) shortestPath = left;
		if((right != "" && shortestPath == "") || (right != "" && shortestPath != "" && right.size() < shortestPath.size())) shortestPath = right;
		if((up    != "" && shortestPath == "") || (up    != "" && shortestPath != "" && up.size()    < shortestPath.size())) shortestPath = up;
		if((down  != "" && shortestPath == "") || (down  != "" && shortestPath != "" && down.size()  < shortestPath.size())) shortestPath = down;
		
		solution = shortestPath;
	}
	
	if(solution != ""){
		for(int i = 0; i < solution.size(); i++){
			move(solution.at(i));
			cout << endl;
		}
	}
	else {
		cout << "Couldn't solve the puzzle" << endl;
	}
}

//Recursive function which tries every possible move (disabled)
string NPuzzle::recursiveSolutionSearch(Board boardCopy, int steps, char moveChar){
	Board boardTemp = boardCopy;
	
	boardTemp.move(moveChar);
				
	if(boardTemp.isSolved()){
		return string(1, boardTemp.getLastMove());
	}
	else{
		if(steps - 1 >= 0 ){
			if(boardTemp.getLastMove() != 'r' && boardTemp.moveLeftIsValid()){
				string leftSolution = recursiveSolutionSearch(boardTemp, steps - 1, 'l');
				if(leftSolution != "")return string(1, boardTemp.getLastMove()) + leftSolution;
			}
			if(boardTemp.getLastMove() != 'l' && boardTemp.moveRightIsValid()){
				string rightSolution = recursiveSolutionSearch(boardTemp, steps - 1, 'r');
				if(rightSolution != "")return string(1, boardTemp.getLastMove()) + rightSolution;
			}
			if(boardTemp.getLastMove() != 'd' && boardTemp.moveUpIsValid()){
				string upSolution = recursiveSolutionSearch(boardTemp, steps - 1, 'u');
				if(upSolution != "")return string(1, boardTemp.getLastMove()) + upSolution;
			}
			if(boardTemp.getLastMove() != 'u' && boardTemp.moveDownIsValid()){
				string downSolution = recursiveSolutionSearch(boardTemp, steps - 1, 'd');
				if(downSolution != "")return string(1, boardTemp.getLastMove()) + downSolution;
			}
		}
		return "";
	}
}

Board NPuzzle::getBoard(){
	return board;
}

void NPuzzle::print(){
	board.print();
}

void NPuzzle::printReport(){
	cout << "Solution will be found if you press \"v\"." << endl;
	cout << "Moves Done: " << to_string(board.getNumberOfMoves()) << endl;
}

void NPuzzle::readFromFile(){
	board.readFromFile();
}

void NPuzzle::writeToFile(){
	board.writeToFile();
}

void NPuzzle::shuffle(int n){
	board.reset(false);
	for(int i = 0; i < n; i++) moveRandom();
}

void NPuzzle::reset(bool isJustCreated){
	board.reset(isJustCreated);
	while(boards.size() > 0)boards.pop_back();
}

void NPuzzle::setSize(){
	int sizeX;
	int sizeY;
	
	do {
		cout << "Enter a board width: ";
		cin >> sizeX;
		if(sizeX < 3){
			cout << "Please enter a valid size" << endl;
		}
	}
	while(!cin || sizeX < 3);
	do {
		cout << "Enter a board height: ";
		cin >> sizeY;
		if(sizeY < 3){
			cout << "Please enter a valid size" << endl;
		}
	}
	while(!cin || sizeY < 3);
	
	board.setSize(sizeX, sizeY);
}

void NPuzzle::moveRandom(){
	char moveChar;
	
	switch(rand() % 4){
		case 0: moveChar = 'l'; break;
		case 1: moveChar = 'r'; break;
		case 2: moveChar = 'u'; break;
		case 3: moveChar = 'd'; break;
	}
	
	if     (!board.moveLeftIsValid()  && moveChar == 'l')moveChar = 'r';
	else if(!board.moveRightIsValid() && moveChar == 'r')moveChar = 'l';
	else if(!board.moveUpIsValid()    && moveChar == 'u')moveChar = 'd';
	else if(!board.moveDownIsValid()  && moveChar == 'd')moveChar = 'u';
	
	move(moveChar);
}

void NPuzzle::move(char moveChar){
	board.move(moveChar);
}

void NPuzzle::solvePuzzle(){
	while(boards.size() > 0)boards.pop_back();
	
	if(board.moveLeftIsValid()){
		Board boardLeft = board;
		boardLeft.move('l');
		boards.push_back(boardLeft);
	}
	if(board.moveRightIsValid()){
		Board boardRight = board;
		boardRight.move('r');
		boards.push_back(boardRight);
	}
	if(board.moveUpIsValid()){
		Board boardUp = board;
		boardUp.move('u');
		boards.push_back(boardUp);
	}
	if(board.moveDownIsValid()){
		Board boardDown = board;
		boardDown.move('d');
		boards.push_back(boardDown);
	}
	
	int index = 0;
	while(!boards[index].isSolved()){
		cout << "\033[H\033[J";
		print();
		cout << endl << "Calculating - " << index << " moves checked..." << endl << endl;
		
		if(boards[index].getLastMove() != 'r' && boards[index].moveLeftIsValid()){
			Board boardLeft = boards[index];
			boardLeft.move('l');
			boards.push_back(boardLeft);
		}
		if(boards[index].getLastMove() != 'l' && boards[index].moveRightIsValid()){
			Board boardRight = boards[index];
			boardRight.move('r');
			boards.push_back(boardRight);
		}
		if(boards[index].getLastMove() != 'd' && boards[index].moveUpIsValid()){
			Board boardUp = boards[index];
			boardUp.move('u');
			boards.push_back(boardUp);
		}
		if(boards[index].getLastMove() != 'u' && boards[index].moveDownIsValid()){
			Board boardDown = boards[index];
			boardDown.move('d');
			boards.push_back(boardDown);
		}
		index++;
	}
	
	vector<char> solution;
	Board tempBoard = boards[index];
	
	for(int i = index; !(tempBoard == board); i--){
		if(boards[i] == tempBoard){
			solution.push_back(boards[i].getLastMove());
			if     (boards[i].getLastMove() == 'l')tempBoard.move('r');
			else if(boards[i].getLastMove() == 'r')tempBoard.move('l');
			else if(boards[i].getLastMove() == 'u')tempBoard.move('d');
			else if(boards[i].getLastMove() == 'd')tempBoard.move('u');
		}
	}
	
	for(int i = solution.size() - 1; i > -1; i--){
		move(solution[i]);
		print();
		cout << endl;
	}
}

//Operator that prints the nPuzzle board
ostream& operator << (ostream& out, NPuzzle &nPuzzle)
{
	const vector<vector<int>> tempBoard = nPuzzle.getBoard().getBoard();
	for(int y = 0; y < tempBoard.size(); y++){
		for(int x = 0; x < tempBoard[0].size(); x++){
			if(tempBoard[y][x] == 0) out << "##";
			else if(tempBoard[y][x] == -1) out << nPuzzle.getBoard().formatStringByDigitCount(" ", " ", to_string(tempBoard[0].size() * tempBoard.size() - 1).length());
			else out << nPuzzle.getBoard().formatStringByDigitCount(to_string(tempBoard[y][x]), "0", to_string(tempBoard[0].size() * tempBoard.size() - 1).length());
			out << " ";
		}
		out << endl;
	}
  return out;
}

//Operator that reads the nPuzzle board from a file
void operator >> (istream &in, NPuzzle& nPuzzle)
{
	nPuzzle.readFromFile();
}

int NPuzzle::getNumberOfBoards(){
	return boards.size();
}
