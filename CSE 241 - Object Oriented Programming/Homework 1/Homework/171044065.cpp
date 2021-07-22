#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//Function that gets boardSize from the user.
void setBoardSize(int *boardSize){
	do {
		cout << "Please enter a board size between 3 and 9:" << endl;
		cin >> *boardSize;
	} 
	while(!cin && *boardSize >= 3 && *boardSize <= 9);
}

//Function that fills the board with correct numbers.
void fillBoard(int **board, int boardSize){
	for(int y = 0; y < boardSize; y++){
		for(int x = 0; x < boardSize; x++){
			board[y][x] = (y * boardSize + (x + 1)) % (boardSize * boardSize);
		}
	}
}

//The function which handles shift operation from a cell into empty cell
void shiftCell(int **board, int boardSize, int *emptyCellx, int *emptyCelly, char move){
	switch(move){
		case 'L':
		case 'l':
			if(*emptyCellx != 0){
				int temp = board[*emptyCelly][*emptyCellx];
				board[*emptyCelly][*emptyCellx] = board[*emptyCelly][(*emptyCellx) - 1];
				board[*emptyCelly][(*emptyCellx) - 1] = temp;
				(*emptyCellx)--;
			}
			break;
		case 'R':
		case 'r':
			if(*emptyCellx != boardSize - 1){
				int temp = board[*emptyCelly][*emptyCellx];
				board[*emptyCelly][*emptyCellx] = board[*emptyCelly][(*emptyCellx) + 1];
				board[*emptyCelly][(*emptyCellx) + 1] = temp;
				(*emptyCellx)++;
			}
			break;
		case 'U':
		case 'u':
			if(*emptyCelly != 0){
				int temp = board[*emptyCelly][*emptyCellx];
				board[*emptyCelly][*emptyCellx] = board[(*emptyCelly) - 1][*emptyCellx];
				board[(*emptyCelly) - 1][*emptyCellx] = temp;
				(*emptyCelly)--;
			}
			break;
		case 'D':
		case 'd':
			if(*emptyCelly != boardSize - 1){
				int temp = board[*emptyCelly][*emptyCellx];
				board[*emptyCelly][*emptyCellx] = board[(*emptyCelly) + 1][*emptyCellx];
				board[(*emptyCelly) + 1][*emptyCellx] = temp;
				(*emptyCelly)++;
			}
			break;
	}
}

//The function which intelligentMove uses in order to understand will that move gets user closer to the solution or not.
int calculateMove(int **board, int boardSize, int *emptyCellx, int *emptyCelly, char move){
	int *boardCopy[boardSize]; 
    for(int i = 0; i < boardSize; i++)boardCopy[i] = (int *)malloc(boardSize * sizeof(int));
    
    for(int y = 0; y < boardSize; y++){
		for(int x = 0; x < boardSize; x++){
			boardCopy[y][x] = board[y][x];
		}
	}
	
	int emptyCellxCopy = *emptyCellx;
	int emptyCellyCopy = *emptyCelly;
	
	shiftCell(boardCopy, boardSize, &emptyCellxCopy, &emptyCellyCopy, move);
	
	int score = 0;
	for(int y = 0; y < boardSize; y++){
		for(int x = 0; x < boardSize; x++){
			if(boardCopy[y][x] != (y * boardSize + (x + 1)) % (boardSize * boardSize))score++;
		}
	}
	
	return score;
}

//Intelligent Move Function compares the wrong placed cells as outcome after every possible move and picks the most meaningful one.
void intelligentMove(int **board, int boardSize, int *emptyCellx, int *emptyCelly){
	int score = boardSize * boardSize;
	
	int scoreLeft = calculateMove(board, boardSize, emptyCellx, emptyCelly, 'l');
	int scoreRight = calculateMove(board, boardSize, emptyCellx, emptyCelly, 'r');
	int scoreUp = calculateMove(board, boardSize, emptyCellx, emptyCelly, 'u');
	int scoreDown = calculateMove(board, boardSize, emptyCellx, emptyCelly, 'd');
	
	char move;
	
	if(*emptyCellx != 0 && scoreLeft <= score){
		move = 'l';
		score = scoreLeft;
	}
	if(*emptyCellx != boardSize - 1 && scoreRight <= score){
		move = 'r';
		score = scoreRight;
	}
	if(*emptyCelly != 0 && scoreUp <= score){
		move = 'u';
		score = scoreUp;
	}
	if(*emptyCelly != boardSize - 1 && scoreDown <= score){
		move = 'd';
		score = scoreDown;
	}
	
	shiftCell(board, boardSize, emptyCellx, emptyCelly, move);
}
//Shuffles the table as playing by the rules but totally random
void shuffleBoard(int **board, int boardSize, int *emptyCellx, int *emptyCelly){
	char move;
	
	for(int i = 0; i < boardSize * boardSize; i++){
		switch(rand() % 4){
		case 0: move = 'l'; break;
		case 1: move = 'r'; break;
		case 2: move = 'u'; break;
		case 3: move = 'd'; break;
		}
		
		if     (*emptyCellx == 0             && move == 'l')move = 'r';
		else if(*emptyCellx == boardSize - 1 && move == 'r')move = 'l';
		else if(*emptyCelly == 0             && move == 'u')move = 'd';
		else if(*emptyCelly == boardSize - 1 && move == 'd')move = 'u';
		
		shiftCell(board, boardSize, emptyCellx, emptyCelly, move);
	}
}

//Prints the current state of the board.
void printBoard(int **board, int boardSize){
	cout << "\033[H\033[J";
	for(int y = 0; y < boardSize; y++){
		for(int x = 0; x < boardSize; x++){
			if(board[y][x] == 0) cout << "  ";
			else if(board[y][x] < 10 && board[y][x] > 0) cout << " " << board[y][x];
			else cout << board[y][x];
			cout << " ";
		}
		cout << endl;
	}
}

//Checks if there is any wrong placed cells, if not ends the game.
bool checkWin(int **board, int boardSize){
	for(int y = 0; y < boardSize; y++){
		for(int x = 0; x < boardSize; x++){
			if(board[y][x] != (y * boardSize + (x + 1)) % (boardSize * boardSize))return false;
		}
	}
	printBoard(board, boardSize);
	cout << "Puzzle Solved!" << endl;
	return true;
}

//Controls the user input if it is valid.
bool checkInputIsValid(char move){
	switch (move){
		case 'L':
		case 'l':
		case 'R':
		case 'r':
		case 'U':
		case 'u':
		case 'D':
		case 'd':
		case 'I':
		case 'i':
		case 'S':
		case 's':
		case 'Q':
		case 'q':
			return true;
		default:
			return false;
	}
}

//Main game function
void game(int **board, int boardSize, int *emptyCellx, int *emptyCelly){
	shuffleBoard(board, boardSize, emptyCellx, emptyCelly);//I shuffle table once before starting the game
	
	char move;
	do {
		do {
			printBoard(board, boardSize);
			cout << "Make a move: (l, r, u, d, i, s, q)" << endl;
			cin >> move;
		} while(!checkInputIsValid(move));
		
		if(move == 'q' || move == 'Q') break;
		else if(move == 'i' || move == 'I') intelligentMove(board, boardSize, emptyCellx, emptyCelly);
		else if(move == 's' || move == 'S') shuffleBoard(board, boardSize, emptyCellx, emptyCelly);
		else shiftCell(board, boardSize, emptyCellx, emptyCelly, move);
	} while(!checkWin(board, boardSize));
}

//main is the function where we allocate or create all necessary and shared variables
int main(){
	srand(time(NULL));
	
	int boardSize;
	setBoardSize(&boardSize);
	
	int *board[boardSize]; 
    for (int i = 0; i < boardSize; i++)board[i] = (int *)malloc(boardSize * sizeof(int));
    
    int emptyCellx = boardSize - 1;
	int emptyCelly = boardSize - 1;
	fillBoard(board, boardSize);

	game(board, boardSize, &emptyCellx, &emptyCelly);
}
