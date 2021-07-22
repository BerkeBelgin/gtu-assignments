#include "AbstractBoard.h"
#include "BoardVector.h"
#include "BoardArray2D.h"
#include "BoardArray1D.h"
#include <vector>

using namespace std;
using namespace ab;

bool isGoingToSolution(vector<AbstractBoard *> boards){
	if((*boards[boards.size() - 1]).isSolved()){
		for(int i = 0; i < boards.size() - 1; i++){
			if((*boards[i])((*boards[i + 1]).getEmptyCelly(), (*boards[i + 1]).getEmptyCellx()) == (*boards[i + 1])((*boards[i]).getEmptyCelly(), (*boards[i]).getEmptyCellx())
			&& (*boards[i]).getBoardSizex() == (*boards[i + 1]).getBoardSizex() && (*boards[i]).getBoardSizey() == (*boards[i + 1]).getBoardSizey()
			&& ((*boards[i]).getEmptyCellx() - (*boards[i + 1]).getEmptyCellx()) <= 1 && ((*boards[i]).getEmptyCellx() - (*boards[i + 1]).getEmptyCellx()) >= -1
			&& ((*boards[i]).getEmptyCelly() - (*boards[i + 1]).getEmptyCelly()) <= 1 && ((*boards[i]).getEmptyCelly() - (*boards[i + 1]).getEmptyCelly()) >= -1){
				for(int y = 0; y < (*boards[i]).getBoardSizey(); y++){
					for(int x = 0; x < (*boards[i]).getBoardSizex(); x++){
						if(((y != (*boards[i]).getEmptyCelly() && x != (*boards[i]).getEmptyCellx()) || (y != (*boards[i + 1]).getEmptyCelly() && x != (*boards[i + 1]).getEmptyCellx()))
						&& (*boards[i])(y, x) != (*boards[i + 1])(y, x)){
							cout << (*boards[i])(y, x) << endl;
							cout << (*boards[i + 1])(y, x) << endl;
							return false;
						}
					}
				}
			} else {
				return false;
			}
		}
		return true;
	} else{
		return false;
	}
}

int main(){
	BoardVector boardVector_1;
	boardVector_1.setSize(12, 12);
	boardVector_1.reset();
	boardVector_1.move('l');
	boardVector_1.move('l');
	boardVector_1.move('u');
	boardVector_1.move('r');
	boardVector_1.move('d');
	boardVector_1.move('r');
	boardVector_1.print();
	if(boardVector_1.isSolved()) cout << "Board is solution." << endl;
	else cout << "Board is not solution." << endl;
	cout << "Boards created: " << boardVector_1.getNumberOfBoards() << endl;
	cout << "Last move: " << boardVector_1.getLastMove() << endl;
	cout << "Moves made: " << boardVector_1.getNumberOfMoves() << endl << endl;
	
	BoardArray2D boardArray2D_1;
	boardArray2D_1.setSize(12, 12);
	boardArray2D_1.reset();
	boardArray2D_1.move('l');
	boardArray2D_1.move('l');
	boardArray2D_1.move('u');
	boardArray2D_1.move('r');
	boardArray2D_1.move('d');
	boardArray2D_1.print();
	if(boardArray2D_1.isSolved()) cout << "Board is solution." << endl;
	else cout << "Board is not solution." << endl;
	cout << "Boards created: " << boardArray2D_1.getNumberOfBoards() << endl;
	cout << "Last move: " << boardArray2D_1.getLastMove() << endl;
	cout << "Moves made: " << boardArray2D_1.getNumberOfMoves() << endl << endl;
	
	BoardArray1D boardArray1D_1;
	boardArray1D_1.setSize(12, 12);
	boardArray1D_1.reset();
	boardArray1D_1.move('l');
	boardArray1D_1.move('l');
	boardArray1D_1.move('u');
	boardArray1D_1.move('r');
	boardArray1D_1.print();
	if(boardArray1D_1.isSolved()) cout << "Board is solution." << endl;
	else cout << "Board is not solution." << endl;
	cout << "Boards created: " << boardArray1D_1.getNumberOfBoards() << endl;
	cout << "Last move: " << boardArray1D_1.getLastMove() << endl;
	cout << "Moves made: " << boardArray1D_1.getNumberOfMoves() << endl;
	boardArray1D_1.writeToFile("game.txt");
	
	BoardVector boardVector_2;
	boardVector_2.readFromFile("game.txt");
	boardVector_2.move('l');
	boardVector_2.print();
	if(boardVector_2.isSolved()) cout << "Board is solution." << endl;
	else cout << "Board is not solution." << endl;
	cout << "Boards created: " << boardVector_2.getNumberOfBoards() << endl;
	cout << "Last move: " << boardVector_2.getLastMove() << endl;
	cout << "Moves made after read: " << boardVector_2.getNumberOfMoves() << endl;
	boardVector_2.writeToFile("game.txt");
	
	BoardArray2D boardArray2D_2;
	boardArray2D_2.readFromFile("game.txt");
	boardArray2D_2.move('d');
	boardArray2D_2.print();
	if(boardArray2D_2.isSolved()) cout << "Board is solution." << endl;
	else cout << "Board is not solution." << endl;
	cout << "Boards created: " << boardArray2D_2.getNumberOfBoards() << endl;
	cout << "Last move: " << boardArray2D_2.getLastMove() << endl;
	cout << "Moves made after read: " << boardArray2D_2.getNumberOfMoves() << endl;
	boardArray2D_2.writeToFile("game.txt");
	
	BoardArray1D boardArray1D_2;
	boardArray1D_2.readFromFile("game.txt");
	boardArray1D_2.move('r');
	boardArray1D_2.print();
	if(boardArray1D_2.isSolved()) cout << "Board is solution." << endl;
	else cout << "Board is not solution." << endl;
	cout << "Boards created: " << boardArray1D_2.getNumberOfBoards() << endl;
	cout << "Last move: " << boardArray1D_2.getLastMove() << endl;
	cout << "Moves made after read: " << boardArray1D_2.getNumberOfMoves() << endl;
	boardArray1D_2.writeToFile("game.txt");
	
	BoardVector boardVector_3;
	boardVector_3.readFromFile("game.txt");
	boardVector_3.move('r');
	boardVector_3.print();
	if(boardVector_3.isSolved()) cout << "Board is solution." << endl;
	else cout << "Board is not solution." << endl;
	cout << "Boards created: " << boardVector_3.getNumberOfBoards() << endl;
	cout << "Last move: " << boardVector_3.getLastMove() << endl;
	cout << "Moves made after read: " << boardVector_3.getNumberOfMoves() << endl;
	boardVector_3.writeToFile("game.txt");
	
	cout << endl << "Adding all boards into a vector one by one and checking if it is solution..." << endl;
	vector<AbstractBoard *> boards;
	boards.push_back(&boardVector_1);
	if(isGoingToSolution(boards)) cout << "Boards are solution" << endl;
	else cout << "Boards are not solution." << endl;
	
	boards.push_back(&boardArray2D_1);
	if(isGoingToSolution(boards)) cout << "Boards are solution" << endl;
	else cout << "Boards are not solution." << endl;
	
	boards.push_back(&boardArray1D_1);
	if(isGoingToSolution(boards)) cout << "Boards are solution" << endl;
	else cout << "Boards are not solution." << endl;
	
	boards.push_back(&boardVector_2);
	if(isGoingToSolution(boards)) cout << "Boards are solution" << endl;
	else cout << "Boards are not solution." << endl;
	
	boards.push_back(&boardArray2D_2);
	if(isGoingToSolution(boards)) cout << "Boards are solution" << endl;
	else cout << "Boards are not solution." << endl;
	
	boards.push_back(&boardArray1D_2);
	if(isGoingToSolution(boards)) cout << "Boards are solution" << endl;
	else cout << "Boards are not solution." << endl;
	
	boards.push_back(&boardVector_3);
	if(isGoingToSolution(boards)) cout << "Boards are solution" << endl;
	else cout << "Boards are not solution." << endl;
	
	cout << endl << "Checking if all boards placed succesfully..." << endl;
	cout << "Board 1: ";
	if((*boards[0]) == boardVector_1 && (*boards[0])((*boards[0]).getEmptyCelly(), (*boards[0]).getEmptyCellx()) == -1) cout << "true" << endl;
	else "false";
	cout << "Board 2: ";
	if((*boards[1]) == boardArray2D_1 && (*boards[1])((*boards[1]).getEmptyCelly(), (*boards[1]).getEmptyCellx()) == -1) cout << "true" << endl;
	else "false";
	cout << "Board 3: ";
	if((*boards[2]) == boardArray1D_1 && (*boards[2])((*boards[2]).getEmptyCelly(), (*boards[2]).getEmptyCellx()) == -1) cout << "true" << endl;
	else "false";
	cout << "Board 4: ";
	if((*boards[3]) == boardVector_2 && (*boards[3])((*boards[3]).getEmptyCelly(), (*boards[3]).getEmptyCellx()) == -1) cout << "true" << endl;
	else "false";
	cout << "Board 5: ";
	if((*boards[4]) == boardArray2D_2 && (*boards[4])((*boards[4]).getEmptyCelly(), (*boards[4]).getEmptyCellx()) == -1) cout << "true" << endl;
	else "false";
	cout << "Board 6: ";
	if((*boards[5]) == boardArray1D_2 && (*boards[5])((*boards[5]).getEmptyCelly(), (*boards[5]).getEmptyCellx()) == -1) cout << "true" << endl;
	else "false";
	cout << "Board 7: ";
	if((*boards[6]) == boardVector_3 && (*boards[6])((*boards[6]).getEmptyCelly(), (*boards[6]).getEmptyCellx()) == -1) cout << "true" << endl;
	else "false";
}
