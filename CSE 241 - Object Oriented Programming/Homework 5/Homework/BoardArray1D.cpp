#include "BoardArray1D.h"

BoardArray1D::~BoardArray1D(){
	delete[] board;
}

void BoardArray1D::setCellValue(int y, int x, int value){
	board[y * boardSizey + x] = value;
}

void BoardArray1D::setSize(int sizeX, int sizeY){
	delete[] board;
	
	boardSizex = sizeX;
	boardSizey = sizeY;
	
	board = new int[sizeY * sizeX];
}

int BoardArray1D::operator () (int y, int x){
	if(y < boardSizey && x < boardSizex){
		return board[y * boardSizey + x];
  } else{
		exit(0);
  }
}
