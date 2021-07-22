#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Board{
	private:
		int **board;
		
		string formatStringByDigitCount(string element, string placeHolder, int digits){
			string placeHolders = "";
			for(int i = 0; i < digits - element.length(); i++) placeHolders += placeHolder;
			return placeHolders + element;
		}
		
		inline int convertToInt(string number){
			int result = 0;
			int multiplier;
			for(int i = number.length() - 1; i >= 0; i--){
				multiplier = 1;
				for(int n = i + 1; number.length() - n > 0; n++)multiplier *= 10;
				result += (number[i] - '0') * multiplier;
			}
			return result;
		}
		
		//Checks if there is any wrong placed cells for any given board.
		bool isSolvedForAnyBoard(int **boardCopy){
			int currentCellValue = 0;
			for(int y = 0; y < boardSizey; y++){
				for(int x = 0; x < boardSizex; x++){
					if(boardCopy[y][x] != 0){
						currentCellValue++;
						if(boardCopy[y][x] != -1 && boardCopy[y][x] != currentCellValue)return false;
					}
				}
			}
			return true;
		}
		
		//The function which handles shift operation from a cell into empty cell for any given board.
		void moveAnyBoard(int **boardCopy, char move, int *copyEmptyCellx, int *copyEmptyCelly){
			switch(move){
			case 'L':
			case 'l':
				if(*copyEmptyCellx != 0 && boardCopy[*copyEmptyCelly][*copyEmptyCellx - 1] != 0){
					int temp = boardCopy[*copyEmptyCelly][*copyEmptyCellx];
					boardCopy[*copyEmptyCelly][*copyEmptyCellx] = boardCopy[*copyEmptyCelly][(*copyEmptyCellx) - 1];
					boardCopy[*copyEmptyCelly][*copyEmptyCellx - 1] = temp;
					(*copyEmptyCellx)--;
				}
				break;
			case 'R':
			case 'r':
				if(*copyEmptyCellx != boardSizex - 1 && boardCopy[*copyEmptyCelly][*copyEmptyCellx + 1] != 0){
					int temp = boardCopy[*copyEmptyCelly][*copyEmptyCellx];
					boardCopy[*copyEmptyCelly][*copyEmptyCellx] = boardCopy[*copyEmptyCelly][*copyEmptyCellx + 1];
					boardCopy[*copyEmptyCelly][*copyEmptyCellx + 1] = temp;
					(*copyEmptyCellx)++;
				}
				break;
			case 'U':
			case 'u':
				if(*copyEmptyCelly != 0 && boardCopy[*copyEmptyCelly - 1][*copyEmptyCellx] != 0){
					int temp = boardCopy[*copyEmptyCelly][*copyEmptyCellx];
					boardCopy[*copyEmptyCelly][*copyEmptyCellx] = boardCopy[*copyEmptyCelly - 1][*copyEmptyCellx];
					boardCopy[*copyEmptyCelly - 1][*copyEmptyCellx] = temp;
					(*copyEmptyCelly)--;
				}
				break;
			case 'D':
			case 'd':
				if(*copyEmptyCelly != boardSizey - 1 && boardCopy[*copyEmptyCelly + 1][*copyEmptyCellx] != 0){
					int temp = boardCopy[*copyEmptyCelly][*copyEmptyCellx];
					boardCopy[*copyEmptyCelly][*copyEmptyCellx] = boardCopy[*copyEmptyCelly + 1][*copyEmptyCellx];
					boardCopy[*copyEmptyCelly + 1][*copyEmptyCellx] = temp;
					(*copyEmptyCelly)++;
				}
				break;
			}
		}
		
	public:
		int boardSizex;
		int boardSizey;
		
		int emptyCellx;
		int emptyCelly;
		
		//Checks if there is any intelligently moveable cell. If not returns "n" character.
		char checkIntelligentMove(){
			int trueCellValue = 0;
			
			bool exit = false;
			for(int y = 0; y < boardSizey; y++){
				for(int x = 0; x < boardSizex; x++){
					if(board[y][x] != 0)trueCellValue++;
					if(board[y][x] == -1)exit = true;
					if(exit)break;
				}
				if(exit)break;
			}
			
			if(emptyCellx != 0 && board[emptyCelly][emptyCellx - 1] == trueCellValue)return 'l';
			else if(emptyCellx != boardSizex - 1 && board[emptyCelly][emptyCellx + 1] == trueCellValue)return 'r';
			else if(emptyCelly != 0 && board[emptyCelly - 1][emptyCellx] == trueCellValue)return 'u';
			else if(emptyCelly != boardSizey - 1 && board[emptyCelly + 1][emptyCellx] == trueCellValue)return 'd';
			else return 'n';
		}
		
		string solvePuzzle(int intelligence){
			string left = "";
			string right = "";
			string up = "";
			string down = "";
			
			if(emptyCellx != 0 && board[emptyCelly][emptyCellx - 1] != 0)              left =  tryToSolve(board, intelligence, 'l', emptyCellx, emptyCelly);
			if(emptyCellx != boardSizex - 1 && board[emptyCelly][emptyCellx + 1] != 0) right = tryToSolve(board, intelligence, 'r', emptyCellx, emptyCelly);
			if(emptyCelly != 0 && board[emptyCelly - 1][emptyCellx] != 0)              up =    tryToSolve(board, intelligence, 'u', emptyCellx, emptyCelly);
			if(emptyCelly != boardSizey - 1 && board[emptyCelly + 1][emptyCellx] != 0) down =  tryToSolve(board, intelligence, 'd', emptyCellx, emptyCelly);
			
			string shortestPath = "";
			if((left  != "" && shortestPath == "") || (left  != "" && shortestPath != "" && left.size()  < shortestPath.size())) shortestPath = left;
			if((right != "" && shortestPath == "") || (right != "" && shortestPath != "" && right.size() < shortestPath.size())) shortestPath = right;
			if((up    != "" && shortestPath == "") || (up    != "" && shortestPath != "" && up.size()    < shortestPath.size())) shortestPath = up;
			if((down  != "" && shortestPath == "") || (down  != "" && shortestPath != "" && down.size()  < shortestPath.size())) shortestPath = down;
			return shortestPath;
		}
		
		//Recursive function which tries every possible move until it reaches it's steps limit
		string tryToSolve(int **boardCopy, int steps, char prev, int copyEmptyCellx, int copyEmptyCelly){
			int **boardTemp = (int **) malloc(boardSizey * sizeof(int *));
			for (int i = 0; i < boardSizey; i++) boardTemp[i] = (int *)malloc(boardSizex * sizeof(int));
			
			for(int y = 0; y < boardSizey; y++){
				for(int x = 0; x < boardSizex; x++){
					boardTemp[y][x] = boardCopy[y][x];
				}
			}
			
			moveAnyBoard(boardTemp, prev, &copyEmptyCellx, &copyEmptyCelly);
						
			if(isSolvedForAnyBoard(boardTemp)){
				return string(1, prev);
			}
			else{
				if(steps - 1 >= 0 ){
					if(prev != 'r' && copyEmptyCellx != 0 && boardCopy[copyEmptyCelly][copyEmptyCellx - 1] != 0){
						string leftSolution = tryToSolve(boardTemp, steps - 1, 'l', copyEmptyCellx, copyEmptyCelly);
						
						if(leftSolution != ""){
							return string(1, prev) + leftSolution;
						}
					}
					if(prev != 'l' && copyEmptyCellx != boardSizex - 1 && boardCopy[copyEmptyCelly][copyEmptyCellx + 1] != 0){
						string rightSolution = tryToSolve(boardTemp, steps - 1, 'r', copyEmptyCellx, copyEmptyCelly);
						
						if(rightSolution != ""){
							return string(1, prev) + rightSolution;
						}
					}
					if(prev != 'd' && copyEmptyCelly != 0 && boardCopy[copyEmptyCelly - 1][copyEmptyCellx] != 0){
						string upSolution = tryToSolve(boardTemp, steps - 1, 'u', copyEmptyCellx, copyEmptyCelly);
						
						if(upSolution != ""){
							return string(1, prev) + upSolution;
						}
					}
					if(prev != 'u' && copyEmptyCelly != boardSizey - 1 && boardCopy[copyEmptyCelly + 1][copyEmptyCellx] != 0){
						string downSolution = tryToSolve(boardTemp, steps - 1, 'd', copyEmptyCellx, copyEmptyCelly);
						
						if(downSolution != ""){
							return string(1, prev) + downSolution;
						}
					}
				}
				for (int i = 0; i < boardSizey; i++)free(boardTemp[i]);
				return "";
			}
		}
		
		//Prints the current state of the board.
		void print(){
			for(int y = 0; y < boardSizey; y++){
				for(int x = 0; x < boardSizex; x++){
					if(board[y][x] == 0) cout << "##";
					else if(board[y][x] == -1) cout << formatStringByDigitCount(" ", " ", to_string(boardSizex * boardSizey - 1).length());
					else cout << formatStringByDigitCount(to_string(board[y][x]), "0", to_string(boardSizex * boardSizey - 1).length());
					cout << " ";
				}
				cout << endl;
			}
		}
		
		//Function that loads the board from a text file.
		void readFromFile(){
			string filename;
			bool success;
			ifstream file;
			
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
				
				boardSizex = 0;
				boardSizey = 0;
				
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
			
			board = (int **) malloc(boardSizey * sizeof(int *));
			for (int i = 0; i < boardSizey; i++) board[i] = (int *)malloc(boardSizex * sizeof(int));
			
			string stream;
			string cell;
			
			file.open(filename, ios::in);
			for(int y = 0; y < boardSizey; y++){
				for(int x = 0; x < boardSizex; x++){
					file >> cell;
					if(cell == formatStringByDigitCount("b", "b", to_string(boardSizex * boardSizey - 1).length())){
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
		void writeToFile(){
			ofstream file;
			string filename;
			
			do{
				cout << endl << "Please enter a filename without \".txt\": ";
				cin >> filename;
				
				filename += ".txt";
				file.open(filename.c_str(), ios::out);
				if(!file.is_open()){
					cout << endl << "Please enter a valid name" << endl << endl;
				}
			} while(!file.is_open());
			
			string stream;
			for(int y = 0; y < boardSizey; y++){
				stream = "";
				for(int x = 0; x < boardSizex; x++){
					if(board[y][x] == -1)stream += formatStringByDigitCount("b", "b", to_string(boardSizex * boardSizey - 1).length());
					else stream += formatStringByDigitCount(to_string(board[y][x]), "0", to_string(boardSizex * boardSizey - 1).length());
					
					if(x == boardSizex - 1 && y == boardSizey - 1)stream += "\0";
					else if(x == boardSizex - 1 && y != boardSizey - 1)stream += "\n";
					else stream += " ";
				}
				file << stream;
			}
			file.close();
			
			cout << endl << "File is saved successfuly" << endl;
		}
		
		//Function that resets the board with correct numbers.
		void reset(){
			int cellValue = 1;
			
			for(int y = 0; y < boardSizey; y++){
				for(int x = 0; x < boardSizex; x++){
					if(board[y][x] != 0){
						board[y][x] = cellValue;
						cellValue++;
					}
				}
			}
			
			for(int y = 0; y < boardSizey; y++){
				for(int x = 0; x < boardSizex; x++){
					board[y][x] = (y * boardSizex + (x + 1));
				}
			}
	
			emptyCellx = boardSizex - 1;
			emptyCelly = boardSizey - 1;
			board[emptyCelly][emptyCellx] = -1;
		}
		
		//Function that creates the board.
		void setSize(int sizeX, int sizeY){
			boardSizex = sizeX;
			boardSizey = sizeY;
			
			board = (int **) malloc(boardSizey * sizeof(int *));
			for (int i = 0; i < boardSizey; i++) board[i] = (int *)malloc(boardSizex * sizeof(int));
			
			reset();
		}
		
		//The function which handles shift operation from a cell into empty cell
		void move(char move){
			switch(move){
			case 'L':
			case 'l':
				if(emptyCellx != 0 && board[emptyCelly][emptyCellx - 1] != 0){
					int temp = board[emptyCelly][emptyCellx];
					board[emptyCelly][emptyCellx] = board[emptyCelly][(emptyCellx) - 1];
					board[emptyCelly][emptyCellx - 1] = temp;
					emptyCellx--;
				}
				break;
			case 'R':
			case 'r':
				if(emptyCellx != boardSizex - 1 && board[emptyCelly][emptyCellx + 1] != 0){
					int temp = board[emptyCelly][emptyCellx];
					board[emptyCelly][emptyCellx] = board[emptyCelly][emptyCellx + 1];
					board[emptyCelly][emptyCellx + 1] = temp;
					emptyCellx++;
				}
				break;
			case 'U':
			case 'u':
				if(emptyCelly != 0 && board[emptyCelly - 1][emptyCellx] != 0){
					int temp = board[emptyCelly][emptyCellx];
					board[emptyCelly][emptyCellx] = board[emptyCelly - 1][emptyCellx];
					board[emptyCelly - 1][emptyCellx] = temp;
					emptyCelly--;
				}
				break;
			case 'D':
			case 'd':
				if(emptyCelly != boardSizey - 1 && board[emptyCelly + 1][emptyCellx] != 0){
					int temp = board[emptyCelly][emptyCellx];
					board[emptyCelly][emptyCellx] = board[emptyCelly + 1][emptyCellx];
					board[emptyCelly + 1][emptyCellx] = temp;
					emptyCelly++;
				}
				break;
			}
		}
		
		//Checks if there is any wrong placed cells, if not ends the game.
		bool isSolved(){
			int currentCellValue = 0;
			for(int y = 0; y < boardSizey; y++){
				for(int x = 0; x < boardSizex; x++){
					if(board[y][x] != 0){
						currentCellValue++;
						if(board[y][x] != -1 && board[y][x] != currentCellValue)return false;
					}
				}
			}
			cout << endl << "Puzzle Solved!" << endl;
			return true;
		}
};
