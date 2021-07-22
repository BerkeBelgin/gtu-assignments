#include "BoardVector.h"

void BoardVector::setCellValue(int y, int x, int value){
	board[y][x] = value;
}

void BoardVector::setSize(int sizeX, int sizeY){
	boardSizex = sizeX;
	boardSizey = sizeY;
	
	board.resize(sizeY);
	for(int i = 0; i < sizeY; i++)board[i].resize(sizeX);
}

int BoardVector::operator () (int y, int x){
	if(y < boardSizey && x < boardSizex){
		return board[y][x];
  } else{
		exit(0);
  }
}
