#ifndef BOARD_VECTOR_H
#define BOARD_VECTOR_H
#include "AbstractBoard.h"
#include <vector>

using namespace ab;

class BoardVector : public AbstractBoard{
	private:
		vector<vector<int>> board;
	public:
		void setCellValue(int, int, int);
		
		void setSize(int, int);
		int operator () (int, int);
};

#endif
