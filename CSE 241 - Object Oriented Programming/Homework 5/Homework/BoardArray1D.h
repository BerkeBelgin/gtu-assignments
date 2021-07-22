#ifndef BOARD_ARRAY_1D_H
#define BOARD_ARRAY_1D_H
#include "AbstractBoard.h"

using namespace ab;

class BoardArray1D : public AbstractBoard{
	private:
		int *board = nullptr;
	public:
		~BoardArray1D();
		
		void setCellValue(int, int, int);
		
		void setSize(int, int);
		int operator () (int, int);
};

#endif
