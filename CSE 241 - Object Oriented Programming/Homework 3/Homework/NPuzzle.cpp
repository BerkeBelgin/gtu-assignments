#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Board.cpp"

using namespace std;

class NPuzzle{
	private:
		Board board;
		
	public:
		int moveCount = 0;
		
		void showSolvedPuzzle(string solution){
			if(solution != ""){
				for(int i = 0; i < solution.size(); i++){
					move(solution.at(i));
					print();
					cout << endl;
				}
			}
			else{
				cout << "Couldn't solve the puzzle" << endl;
			}
		}
		
		bool isSolved(){
			return board.isSolved();
		}
		
		void print(){
			board.print();
		}
		
		void printReport(){
			if(solvePuzzle() != "")cout << "Solution is found." << endl;
			else cout << "Solution is not found." << endl;
			cout << "Moves Done: " << to_string(moveCount) << endl;
		}
		
		void readFromFile(){
			board.readFromFile();
		}
		
		void writeToFile(){
			board.writeToFile();
		}
		
		void shuffle(int n){
			for(int i = 0; i < n; i++){
				moveRandom();
			}
		}
		
		void reset(){
			board.reset();
		}
		
		void setSize(){
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
		
		void moveRandom(){
			char moveChar;
			
			switch(rand() % 4){
				case 0: moveChar = 'l'; break;
				case 1: moveChar = 'r'; break;
				case 2: moveChar = 'u'; break;
				case 3: moveChar = 'd'; break;
			}
			
			if     (board.emptyCellx == 0             			 && moveChar == 'l')moveChar = 'r';
			else if(board.emptyCellx == board.boardSizex - 1 && moveChar == 'r')moveChar = 'l';
			else if(board.emptyCelly == 0             			 && moveChar == 'u')moveChar = 'd';
			else if(board.emptyCelly == board.boardSizey - 1 && moveChar == 'd')moveChar = 'u';
			
			move(moveChar);
		}
		
		void moveIntelligent(){
			char moveChar = board.checkIntelligentMove();	
			if(moveChar != 'n'){
				move(moveChar);
			}
			else{
				moveRandom();
			}
		}
		
		void move(char moveChar){
			board.move(moveChar);
		}
		
		string solvePuzzle(){
			string solution = "";
			int intelligenceMoveLimit = 18;
			for(int intelligence = 0; solution == "" && intelligence < intelligenceMoveLimit; intelligence++){
				cout << "\033[H\033[J";
				print();
				cout << endl << "Calculating - " << (int)(((double)(intelligence + 1) / (double)intelligenceMoveLimit) * 100) << "%" << endl;
				
				solution = board.solvePuzzle(intelligence);
			}
			return solution;
		}
};
