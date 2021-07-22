#include "BoardArray2D.h"

BoardArray2D::~BoardArray2D(){
	for(int i = 0; i < boardSizey; ++i) delete[] board[i];
	delete[] board;
}

void BoardArray2D::setCellValue(int y, int x, int value){
	board[y][x] = value;
}

void BoardArray2D::setSize(int sizeX, int sizeY){
	for(int i = 0; i < boardSizey; ++i) delete[] board[i];
	delete[] board;
	
	boardSizex = sizeX;
	boardSizey = sizeY;
	
	board = new int *[sizeY];
	for(int i = 0; i < sizeY; ++i) board[i] = new int[sizeX];
}

int BoardArray2D::operator () (int y, int x){
	if(y < boardSizey && x < boardSizex){
		return board[y][x];
  } else{
		exit(0);
  }
}
