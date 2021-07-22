public class Main{
	public static boolean isGoingToSolution(AbstractBoard[] boards, int size){
		if(boards[size - 1].isSolved()){
			for(int i = 0; i < boards.length - 1; i++){
				if(isMoveValid(boards[i], boards[i + 1]) && hasSameSize(boards[i], boards[i + 1])){
					for(int y = 0; y < boards[i].getSizeY(); y++){
						for(int x = 0; x < boards[i].getSizeX(); x++){
							if(!isEmptyCell(y, x, boards[i]) && !isEmptyCell(y, x, boards[i + 1]) && boards[i].cell(y, x) != boards[i + 1].cell(y, x)){
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
	
	private static boolean isMoveValid(AbstractBoard board1, AbstractBoard board2){
		if (board1.cell(board2.getEmptyY(), board2.getEmptyX()) == board2.cell(board1.getEmptyY(), board1.getEmptyX())
		&& (board1.getEmptyX() - board2.getEmptyX()) <= 1 && (board1.getEmptyX() - board2.getEmptyX()) >= -1
		&& (board1.getEmptyY() - board2.getEmptyY()) <= 1 && (board1.getEmptyY() - board2.getEmptyY()) >= -1){
			return true;
		} else{
			return false;
		}
	}
	private static boolean hasSameSize(AbstractBoard board1, AbstractBoard board2){
		if(board1.getSizeX() == board2.getSizeX() && board1.getSizeY() == board2.getSizeY()){
			return true;
		} else{
			return false;
		}
	}
	private static boolean isEmptyCell(int y, int x, AbstractBoard board){
		if(board.getEmptyY() == y && board.getEmptyX() == x){
			return true;
		} else{
			return false;
		}
	}
	
	public static void main(String[] args){
		BoardArray2D boardArray2D_1 = new BoardArray2D(9, 9);
		boardArray2D_1.reset();
		boardArray2D_1.move('l');
		boardArray2D_1.move('l');
		boardArray2D_1.move('u');
		boardArray2D_1.move('r');
		boardArray2D_1.move('d');
		boardArray2D_1.move('r');
		System.out.println(boardArray2D_1.toString());
		if(boardArray2D_1.isSolved()) System.out.println("Board is solution.");
		else System.out.println("Board is not solution.");
		System.out.println("Boards created: " + boardArray2D_1.numberOfBoards());
		System.out.println("Last move: " + boardArray2D_1.lastMove());
		System.out.println("Moves made: " + boardArray2D_1.numberOfMoves() + "\n\n");
		
		BoardArray1D boardArray1D_1 = new BoardArray1D(9, 9);
		boardArray1D_1.reset();
		boardArray1D_1.move('l');
		boardArray1D_1.move('l');
		boardArray1D_1.move('u');
		boardArray1D_1.move('r');
		boardArray1D_1.move('d');
		System.out.println(boardArray1D_1.toString());
		if(boardArray1D_1.isSolved()) System.out.println("Board is solution.");
		else System.out.println("Board is not solution.");
		System.out.println("Boards created: " + boardArray1D_1.numberOfBoards());
		System.out.println("Last move: " + boardArray1D_1.lastMove());
		System.out.println("Moves made: " + boardArray1D_1.numberOfMoves() + "\n\n");
		boardArray1D_1.writeToFile("game.txt");
		
		BoardArray2D boardArray2D_2 = new BoardArray2D(9, 9);
		boardArray2D_2.readFromFile("game.txt");
		boardArray2D_2.move('u');
		System.out.println(boardArray2D_2.toString());
		if(boardArray2D_2.isSolved()) System.out.println("Board is solution.");
		else System.out.println("Board is not solution.");
		System.out.println("Boards created: " + boardArray2D_2.numberOfBoards());
		System.out.println("Last move: " + boardArray2D_2.lastMove());
		System.out.println("Moves made after read: " + boardArray2D_2.numberOfMoves() + "\n\n");
		boardArray2D_2.writeToFile("game.txt");
		
		BoardArray1D boardArray1D_2 = new BoardArray1D(9, 9);
		boardArray1D_2.readFromFile("game.txt");
		boardArray1D_2.move('l');
		System.out.println(boardArray1D_2.toString());
		if(boardArray1D_2.isSolved()) System.out.println("Board is solution.");
		else System.out.println("Board is not solution.");
		System.out.println("Boards created: " + boardArray1D_2.numberOfBoards());
		System.out.println("Last move: " + boardArray1D_2.lastMove());
		System.out.println("Moves made after read: " + boardArray1D_2.numberOfMoves() + "\n\n");
		boardArray1D_2.writeToFile("game.txt");
		
		BoardArray2D boardArray2D_3 = new BoardArray2D(9, 9);
		boardArray2D_3.readFromFile("game.txt");
		boardArray2D_3.move('d');
		System.out.println(boardArray2D_3.toString());
		if(boardArray2D_3.isSolved()) System.out.println("Board is solution.");
		else System.out.println("Board is not solution.");
		System.out.println("Boards created: " + boardArray2D_3.numberOfBoards());
		System.out.println("Last move: " + boardArray2D_3.lastMove());
		System.out.println("Moves made after read: " + boardArray2D_3.numberOfMoves() + "\n\n");
		boardArray2D_3.writeToFile("game.txt");
		
		BoardArray1D boardArray1D_3 = new BoardArray1D(9, 9);
		boardArray1D_3.readFromFile("game.txt");
		boardArray1D_3.move('r');
		System.out.println(boardArray1D_3.toString());
		if(boardArray1D_3.isSolved()) System.out.println("Board is solution.");
		else System.out.println("Board is not solution.");
		System.out.println("Boards created: " + boardArray1D_3.numberOfBoards());
		System.out.println("Last move: " + boardArray1D_3.lastMove());
		System.out.println("Moves made after read: " + boardArray1D_3.numberOfMoves() + "\n\n");
		boardArray1D_3.writeToFile("game.txt");
		
		BoardArray2D boardArray2D_4 = new BoardArray2D(9, 9);
		boardArray2D_4.readFromFile("game.txt");
		boardArray2D_4.move('r');
		System.out.println(boardArray2D_4.toString());
		if(boardArray2D_4.isSolved()) System.out.println("Board is solution.");
		else System.out.println("Board is not solution.");
		System.out.println("Boards created: " + boardArray2D_4.numberOfBoards());
		System.out.println("Last move: " + boardArray2D_4.lastMove());
		System.out.println("Moves made after read: " + boardArray2D_4.numberOfMoves() + "\n\n");
		boardArray2D_4.writeToFile("game.txt");
		
		
		System.out.println("\nAdding all boards into an array one by one and checking if it is solution...");
		AbstractBoard[] boards = new AbstractBoard[7];
		int boardsSize = 0;
		
		boards[0] = boardArray2D_1;
		boardsSize++;
		if(isGoingToSolution(boards, boardsSize)) System.out.println("Boards are solution");
		else System.out.println("Boards are not solution.");
		
		boards[1] = boardArray1D_1;
		boardsSize++;
		if(isGoingToSolution(boards, boardsSize)) System.out.println("Boards are solution");
		else System.out.println("Boards are not solution.");
		
		boards[2] = boardArray2D_2;
		boardsSize++;
		if(isGoingToSolution(boards, boardsSize)) System.out.println("Boards are solution");
		else System.out.println("Boards are not solution.");
		
		boards[3] = boardArray1D_2;
		boardsSize++;
		if(isGoingToSolution(boards, boardsSize)) System.out.println("Boards are solution");
		else System.out.println("Boards are not solution.");
		
		boards[4] = boardArray2D_3;
		boardsSize++;
		if(isGoingToSolution(boards, boardsSize)) System.out.println("Boards are solution");
		else System.out.println("Boards are not solution.");
		
		boards[5] = boardArray1D_3;
		boardsSize++;
		if(isGoingToSolution(boards, boardsSize)) System.out.println("Boards are solution");
		else System.out.println("Boards are not solution.");
		
		boards[6] = boardArray2D_4;
		boardsSize++;
		if(isGoingToSolution(boards, boardsSize)) System.out.println("Boards are solution");
		else System.out.println("Boards are not solution.");
		
		
		System.out.println("\nChecking if all boards placed succesfully...");
		System.out.println("Board 1: ");
		if(boards[0] == boardArray2D_1 && boards[0].cell(boards[0].getEmptyY(), boards[0].getEmptyX()) == -1) System.out.println("true");
		else System.out.println("false");
		System.out.println("Board 2: ");
		if(boards[1] == boardArray1D_1 && boards[1].cell(boards[1].getEmptyY(), boards[1].getEmptyX()) == -1) System.out.println("true");
		else System.out.println("false");
		System.out.println("Board 3: ");
		if(boards[2] == boardArray2D_2 && boards[2].cell(boards[2].getEmptyY(), boards[2].getEmptyX()) == -1) System.out.println("true");
		else System.out.println("false");
		System.out.println("Board 4: ");
		if(boards[3] == boardArray1D_2 && boards[3].cell(boards[3].getEmptyY(), boards[3].getEmptyX()) == -1) System.out.println("true");
		else System.out.println("false");
		System.out.println("Board 5: ");
		if(boards[4] == boardArray2D_3 && boards[4].cell(boards[4].getEmptyY(), boards[4].getEmptyX()) == -1) System.out.println("true");
		else System.out.println("false");
		System.out.println("Board 6: ");
		if(boards[5] == boardArray1D_3 && boards[5].cell(boards[5].getEmptyY(), boards[5].getEmptyX()) == -1) System.out.println("true");
		else System.out.println("false");
		System.out.println("Board 7: ");
		if(boards[6] == boardArray2D_4 && boards[6].cell(boards[6].getEmptyY(), boards[6].getEmptyX()) == -1) System.out.println("true");
		else System.out.println("false");
	}
}
