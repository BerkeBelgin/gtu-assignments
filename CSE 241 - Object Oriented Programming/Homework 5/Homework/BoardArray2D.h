#ifndef BOARD_ARRAY_2D_H
#define BOARD_ARRAY_2D_H
#include "AbstractBoard.h"

using namespace ab;

class BoardArray2D : public AbstractBoard{
	private:
		int **board = nullptr;
	public:
		~BoardArray2D();
		
		void setCellValue(int, int, int);
		
		void setSize(int, int);
		int operator () (int, int);
};

#endif
