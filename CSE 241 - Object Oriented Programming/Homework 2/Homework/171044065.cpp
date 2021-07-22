#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

string formatStringByDigitCount(string element, string placeHolder, int digits){
	string placeHolders = "";
	for(int i = 0; i < digits - element.length(); i++) placeHolders += placeHolder;
	return placeHolders + element;
}

int convertToInt(string number){
	int result = 0;
	int multiplier;
	for(int i = number.length() - 1; i >= 0; i--){
		multiplier = 1;
		for(int n = i + 1; number.length() - n > 0; n++)multiplier *= 10;
		result += (number[i] - '0') * multiplier;
	}
	return result;
}

//Function that creates the board with correct numbers.
void createBoard(int ***board, int *boardSizex, int *boardSizey, int *emptyCellx, int *emptyCelly){
	do {
		cout << "Enter a board width: ";
		cin >> *boardSizex;
		if(*boardSizex < 3){
			cout << "Please enter a valid size" << endl;
		}
	}
	while(!cin || *boardSizex < 3);
	do {
		cout << "Enter a board height: ";
		cin >> *boardSizey;
		if(*boardSizey < 3){
			cout << "Please enter a valid size" << endl;
		}
	}
	while(!cin || *boardSizey < 3);
	
	*board = (int **) malloc(*boardSizey * sizeof(int *));
	for (int i = 0; i < *boardSizey; i++) (*board)[i] = (int *)malloc(*boardSizex * sizeof(int));
	
	for(int y = 0; y < *boardSizey; y++){
		for(int x = 0; x < *boardSizex; x++){
			(*board)[y][x] = (y * *boardSizex + (x + 1));
		}
	}
	
	*emptyCellx = *boardSizex - 1;
	*emptyCelly = *boardSizey - 1;
	(*board)[*emptyCelly][*emptyCellx] = -1;
}

//Function that loads the board from a text file.
void loadBoard(int ***board, int *boardSizex, int *boardSizey, int *emptyCellx, int *emptyCelly){
	ifstream file;
	string filename;
	bool success;
	
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
		
		*boardSizex = 0;
		*boardSizey = 0;
		
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
			if(*boardSizex == 0){
				*boardSizex = boardSizexCount;
			} 
			else if(*boardSizex != boardSizexCount){
				success = false;
				cout << "A mismatch between column and row sizes is detected. Please fix it and try again" << endl << endl;
				break;
			}
			(*boardSizey)++;
		}
		file.close();
	}while(!success);
	
	*board = (int **) malloc(*boardSizey * sizeof(int *));
	for (int i = 0; i < *boardSizey; i++) (*board)[i] = (int *)malloc(*boardSizex * sizeof(int));
	
	string stream;
	string cell;
	
	file.open(filename, ios::in);
	for(int y = 0; y < *boardSizey; y++){
		for(int x = 0; x < *boardSizex; x++){
			file >> cell;
			if(cell == formatStringByDigitCount("b", "b", to_string(*boardSizex * *boardSizey - 1).length())){
				*emptyCellx = x;
				*emptyCelly = y;
				(*board)[y][x] = -1;
			}
			else{
				(*board)[y][x] = convertToInt(cell);
			}
		}
	}
	file.close();
}

//The function where we save current game state
void saveBoard(int **board, int boardSizex, int boardSizey){
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

//The function which handles shift operation from a cell into empty cell
void shiftCell(int **board, int boardSizex, int boardSizey, int *emptyCellx, int *emptyCelly, char move){
	switch(move){
		case 'L':
		case 'l':
			if(*emptyCellx != 0 && board[*emptyCelly][*emptyCellx - 1] != 0){
				int temp = board[*emptyCelly][*emptyCellx];
				board[*emptyCelly][*emptyCellx] = board[*emptyCelly][(*emptyCellx) - 1];
				board[*emptyCelly][(*emptyCellx) - 1] = temp;
				(*emptyCellx)--;
			}
			break;
		case 'R':
		case 'r':
			if(*emptyCellx != boardSizex - 1 && board[*emptyCelly][*emptyCellx + 1] != 0){
				int temp = board[*emptyCelly][*emptyCellx];
				board[*emptyCelly][*emptyCellx] = board[*emptyCelly][(*emptyCellx) + 1];
				board[*emptyCelly][(*emptyCellx) + 1] = temp;
				(*emptyCellx)++;
			}
			break;
		case 'U':
		case 'u':
			if(*emptyCelly != 0 && board[*emptyCelly - 1][*emptyCellx] != 0){
				int temp = board[*emptyCelly][*emptyCellx];
				board[*emptyCelly][*emptyCellx] = board[(*emptyCelly) - 1][*emptyCellx];
				board[(*emptyCelly) - 1][*emptyCellx] = temp;
				(*emptyCelly)--;
			}
			break;
		case 'D':
		case 'd':
			if(*emptyCelly != boardSizey - 1 && board[*emptyCelly + 1][*emptyCellx] != 0){
				int temp = board[*emptyCelly][*emptyCellx];
				board[*emptyCelly][*emptyCellx] = board[(*emptyCelly) + 1][*emptyCellx];
				board[(*emptyCelly) + 1][*emptyCellx] = temp;
				(*emptyCelly)++;
			}
			break;
	}
}

//The function which intelligentMove uses in order to understand will that move gets user closer to the solution or not.
int calculateMove(int **board, int boardSizex, int boardSizey, int *emptyCellx, int *emptyCelly, char move){
	int *boardCopy[boardSizey]; 
    for(int i = 0; i < boardSizey; i++){
    	boardCopy[i] = (int *)malloc(boardSizex * sizeof(int));
  	}
    
    for(int y = 0; y < boardSizey; y++){
			for(int x = 0; x < boardSizex; x++){
				boardCopy[y][x] = board[y][x];
			}
	}
	
	int emptyCellxCopy = *emptyCellx;
	int emptyCellyCopy = *emptyCelly;
	
	shiftCell(boardCopy, boardSizex, boardSizey, &emptyCellxCopy, &emptyCellyCopy, move);
	
	int score = 0;
	for(int y = 0; y < boardSizey; y++){
		for(int x = 0; x < boardSizex; x++){
			if(boardCopy[y][x] != (y * boardSizey + (x + 1)) % (boardSizex * boardSizey))score++;
		}
	}
	
	return score;
}

//Intelligent Move Function compares the wrong placed cells as outcome after every possible move and picks the most meaningful one.
void intelligentMove(int **board, int boardSizex, int boardSizey, int *emptyCellx, int *emptyCelly){
	int score = boardSizex * boardSizey;
	
	int scoreLeft = calculateMove(board, boardSizex, boardSizey, emptyCellx, emptyCelly, 'l');
	int scoreRight = calculateMove(board, boardSizex, boardSizey, emptyCellx, emptyCelly, 'r');
	int scoreUp = calculateMove(board, boardSizex, boardSizey, emptyCellx, emptyCelly, 'u');
	int scoreDown = calculateMove(board, boardSizex, boardSizey, emptyCellx, emptyCelly, 'd');
	
	char move;
	
	if(*emptyCellx != 0 && scoreLeft <= score){
		move = 'l';
		score = scoreLeft;
	}
	if(*emptyCellx != boardSizex - 1 && scoreRight <= score){
		move = 'r';
		score = scoreRight;
	}
	if(*emptyCelly != 0 && scoreUp <= score){
		move = 'u';
		score = scoreUp;
	}
	if(*emptyCelly != boardSizey - 1 && scoreDown <= score){
		move = 'd';
		score = scoreDown;
	}
	
	shiftCell(board, boardSizex, boardSizey, emptyCellx, emptyCelly, move);
}

//Advanced Intelligent Move Function compares the wrong placed cells as outcome after every possible move and picks the most meaningful one.
void advancedIntelligentMove(int **board, int boardSizex, int boardSizey, int *emptyCellx, int *emptyCelly){
	int score = boardSizex * boardSizey;
	
	int scoreLeft = calculateMove(board, boardSizex, boardSizey, emptyCellx, emptyCelly, 'l');
	int scoreRight = calculateMove(board, boardSizex, boardSizey, emptyCellx, emptyCelly, 'r');
	int scoreUp = calculateMove(board, boardSizex, boardSizey, emptyCellx, emptyCelly, 'u');
	int scoreDown = calculateMove(board, boardSizex, boardSizey, emptyCellx, emptyCelly, 'd');
	
	char move;
	if(scoreLeft == scoreRight && scoreRight == scoreUp && scoreUp == scoreDown){
		switch(rand() % 4){
			case 0: move = 'l'; break;
			case 1: move = 'r'; break;
			case 2: move = 'u'; break;
			case 3: move = 'd'; break;
		}
		
		if     (*emptyCellx == 0              && move == 'l')move = 'r';
		else if(*emptyCellx == boardSizex - 1 && move == 'r')move = 'l';
		else if(*emptyCelly == 0              && move == 'u')move = 'd';
		else if(*emptyCelly == boardSizey - 1 && move == 'd')move = 'u';
	}
	else{
		if(*emptyCellx != 0 && scoreLeft <= score){
			move = 'l';
			score = scoreLeft;
		}
		if(*emptyCellx != boardSizex - 1 && scoreRight <= score){
			move = 'r';
			score = scoreRight;
		}
		if(*emptyCelly != 0 && scoreUp <= score){
			move = 'u';
			score = scoreUp;
		}
		if(*emptyCelly != boardSizey - 1 && scoreDown <= score){
			move = 'd';
			score = scoreDown;
		}
	}
	
	shiftCell(board, boardSizex, boardSizey, emptyCellx, emptyCelly, move);
}

//Shuffles the table as playing by the rules but totally random
void shuffleBoard(int **board, int boardSizex, int boardSizey, int *emptyCellx, int *emptyCelly){
	char move;
	
	for(int i = 0; i < boardSizex * boardSizey; i++){
		switch(rand() % 4){
			case 0: move = 'l'; break;
			case 1: move = 'r'; break;
			case 2: move = 'u'; break;
			case 3: move = 'd'; break;
		}
		
		if     (*emptyCellx == 0             && move == 'l')move = 'r';
		else if(*emptyCellx == boardSizex - 1 && move == 'r')move = 'l';
		else if(*emptyCelly == 0             && move == 'u')move = 'd';
		else if(*emptyCelly == boardSizey - 1 && move == 'd')move = 'u';
		
		shiftCell(board, boardSizex, boardSizey, emptyCellx, emptyCelly, move);
	}
}

//Prints the current state of the board.
void printBoard(int **board, int boardSizex, int boardSizey){
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

//Checks if there is any wrong placed cells, if not ends the game.
bool checkWin(int **board, int boardSizex, int boardSizey){
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

void printStatus(int moveCount, bool isSolutionFound){
	cout << endl << "Moves Done: " << to_string(moveCount) << endl;
	if(isSolutionFound)cout << "Solution is found." << endl;
	else cout << "Solution is not found." << endl;
}

//Main game function
void game(int ***board, int *boardSizex, int *boardSizey, int *emptyCellx, int *emptyCelly){
	char move;
	int moveCount = 0;
	bool isSolutionFound = false;
	
	cout << "\033[H\033[J";
	printBoard(*board, *boardSizex, *boardSizey);
	
	do {
		cout << endl << "Make a move:" << endl;
		cout << "l: Go Left" << endl;
		cout << "r: Go Right" << endl;
		cout << "u: Go Up" << endl;
		cout << "d: Go Down" << endl;
		cout << "i: Primitive Intelligent Move" << endl;
		cout << "s: Shuffle" << endl;
		cout << "v: Advanced Intelligent Move" << endl;
		cout << "t: Print Report" << endl;
		cout << "e: Save Game" << endl;
		cout << "y: Load Game" << endl;
		cout << "q: Quit" << endl << endl;
		cin >> move;
		
		switch(move){
		 	case 'q': case 'Q':
		 		return;
			case 'i': case 'I':
				intelligentMove(*board, *boardSizex, *boardSizey, emptyCellx, emptyCelly);
				moveCount++;
				break;
			case 'v': case 'V':
				advancedIntelligentMove(*board, *boardSizex, *boardSizey, emptyCellx, emptyCelly);
				moveCount++;
				break;
			case 's': case 'S':
				shuffleBoard(*board, *boardSizex, *boardSizey, emptyCellx, emptyCelly);
				moveCount += *boardSizex * *boardSizey;
				break;
			case 'y': case 'Y':
				loadBoard(board, boardSizex, boardSizey, emptyCellx, emptyCelly);
				moveCount = 0;
				break;
			case 'l': case 'L':
			case 'r': case 'R':
			case 'u': case 'U':
			case 'd': case 'D':
				shiftCell(*board, *boardSizex, *boardSizey, emptyCellx, emptyCelly, move);
				moveCount++;
				break;
		}
		
		cout << "\033[H\033[J";
		printBoard(*board, *boardSizex, *boardSizey);
		
		switch(move){
			case 'e': case 'E':
				saveBoard(*board, *boardSizex, *boardSizey);
				break;
			case 't': case 'T':
				printStatus(moveCount, isSolutionFound);
				break;
		}
	} while(!checkWin(*board, *boardSizex, *boardSizey));
}

//main is the function where we allocate or create all necessary and shared variables
int main(){
	srand(time(NULL));
	
	int **board;
	int boardSizex;
	int boardSizey;
	
	int emptyCellx;
	int emptyCelly;
	
	char choice;
	do{
		cout << "Enter \"l\" to load game from a text file or \"c\" to create one: ";
		cin >> choice;
		cout << endl;
		
		switch(choice){
			case 'l': case 'L': 
				loadBoard(&board, &boardSizex, &boardSizey, &emptyCellx, &emptyCelly);
				break;
			case 'c': case 'C': 
				createBoard(&board, &boardSizex, &boardSizey, &emptyCellx, &emptyCelly);
				break;
			default:
				cout << "Please enter a valid key" << endl;
				break;
		}
	} while(choice != 'l' && choice != 'L' && choice != 'c' && choice != 'C');
	game(&board, &boardSizex, &boardSizey, &emptyCellx, &emptyCelly);
}
