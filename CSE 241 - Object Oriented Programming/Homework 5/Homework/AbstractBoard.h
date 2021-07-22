#ifndef ABSTRACT_BOARD_H
#define ABSTRACT_BOARD_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace ab{
	class AbstractBoard{
		protected:
			int boardSizex = 0;
			int boardSizey = 0;
			int emptyCellx = 0;
			int emptyCelly = 0;
			static int boardCount;
			char lastMove = 's';
			int moveCount = 0;
		public:
			AbstractBoard();
			~AbstractBoard();
			
			virtual int getBoardSizex();
			virtual int getBoardSizey();
			virtual int getEmptyCellx();
			virtual int getEmptyCelly();
			virtual void setCellValue(int, int, int) = 0;				//Function that sets given yth xth cell with given value.
			string formatStringByDigitCount(string, string, int);
			int convertToInt(string);
			
			virtual void print();
			virtual void readFromFile(string);
			virtual void writeToFile(string);
			virtual void reset();
			virtual void setSize(int, int) = 0;									//Function that creates the board.
			virtual void move(char);
			virtual bool isSolved();
			virtual int operator () (int, int) = 0; 						//Operator which returns the element in y'th row and x'th column
			virtual bool operator == (AbstractBoard &);
			virtual int getNumberOfBoards();
			virtual char getLastMove();
			virtual int getNumberOfMoves();
	};
}
#endif
