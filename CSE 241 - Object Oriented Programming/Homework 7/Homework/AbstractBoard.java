import java.io.File;
import java.io.FileWriter;
import java.io.IOException; 
import java.util.Vector;
import java.util.List;
import java.nio.charset.StandardCharsets; 
import java.nio.file.Files;
import java.nio.file.Paths;

/**
 * An abstract board class for other board classes to extend
 * @author Berke Belgin
 */
public abstract class AbstractBoard{
	/**
	 * Boards horizontal length
	 */
	protected int sizeX = 0;
	/**
	 * Boards verical length
	 */
	protected int sizeY = 0;
	
	/**
	 * Empty Cells horizontal index
	 */
	protected int emptyX = 0;
	/**
	 * Empty Cells vertical index
	 */
	protected int emptyY = 0;
	
	/**
	 * Amount of boards created so far
	 */
	protected static int boardCount = 0;
	/**
	 * Amount of moves made on this board
	 */
	protected int moveCount = 0;
	/**
	 * Last move made on this board
	 */
	protected char lastMove = 'N';
	
	/**
	 * Default constructor which creates a board 3 to 3
	 */
	public AbstractBoard(){
		this.setSize(3, 3);
		boardCount++;
	}
	/**
	 * Constructor which takes 2 arguments, one for y-axis and one for x-axis
	 * @param y horizontal size of the board
	 * @param x vertical size of the board
	 */
	public AbstractBoard(int y, int x){
		this.setSize(y, x);
		boardCount++;
	}
	
	/**
	 * Equivelant of destructor in C++, decrements board count by one when a board is garbage collected
	 */
	protected void finalize(){
		boardCount--;
	}
	
	//Helper methods
	/**
	 * A helper method that takes a string and appends placeholder characters in order to reach a character count
	 * @param element The original string
	 * @param placeHolder The character that will be appended at the end of the original string
	 * @param digits The amount how many digits should the string reach
	 * @return returns the result
	 */
	private String formatStringByDigitCount(String element, String placeHolder, int digits){
		String placeHolders = "";
		for(int i = 0; i < digits - element.length(); i++) placeHolders += placeHolder;
		return placeHolders + element;
	}
	/**
	 * Takes a number as a string and converts it into int
	 * @param number the number as string
	 * @return returns the number as int
	 */
	private int convertToInt(String number){
		int result = 0;
		int multiplier;
		for(int i = number.length() - 1; i >= 0; i--){
			multiplier = 1;
			for(int n = i + 1; number.length() - n > 0; n++)multiplier *= 10;
			result += (number.charAt(i) - '0') * multiplier;
		}
		return result;
	}
	/**
	 * Method to get horizontal size
	 * @return horizontal size
	 */
	public int getSizeX(){
		return sizeX;
	}
	/**
	 * Method to get vertical size
	 * @return vertical size
	 */
	public int getSizeY(){
		return sizeY;
	}
	/**
	 * Method to get empty cells horizontal index
	 * @return empty cells horizontal index
	 */
	public int getEmptyX(){
		return emptyX;
	}
	/**
	 * Method to get empty cells vertical index
	 * @return empty cells vertical index
	 */
	public int getEmptyY(){
		return emptyY;
	}
	/**
	 * Sets the value of the cell(y, x) by value variable
	 * @param y y-axis index
	 * @param x x-axis index
	 * @param value the value cell will be set
	 */
	public abstract void setCell(int y, int x, int value);
	
	//Methods at pdf
	/**
	 * Allocates memory for an array of size sizeY to sizeX
	 * @param sizeY y-axis size
	 * @param sizeX x-axis size
	 */
	public abstract void setSize(int sizeY, int sizeX);
	/**
	 * Gets the value of the cell(y, x)
	 * @param y y-axis index
	 * @param x x-axis index
	 * @return value of the cell
	 */
	public abstract int cell(int y, int x);
	
	/**
	 * Lets us have the board configuration as string
	 * @return Returns the board configuration as string
	 */
	public String toString(){
		String result = "";
		
		for(int y = 0; y < sizeY; y++){
			for(int x = 0; x < sizeX; x++){
				if(this.cell(y, x) == 0) result += "##";
				else if(this.cell(y, x) == -1) result += formatStringByDigitCount(" ", " ", Integer.toString(sizeX * sizeY - 1).length());
				else result += formatStringByDigitCount(Integer.toString(this.cell(y, x)), "0", Integer.toString(sizeX * sizeY - 1).length());
				result += " ";
			}
			result += "\n";
		}
		
		return result;
	}
	
	/**
	 * Reads board configuration from a text file named filename
	 * @param filename name of the text file
	 */
	public void readFromFile(String filename){
		int fileSizeX = 0;
		int fileSizeY = 0;
		List<String> lines = new Vector<String>();
		
    try{ 
      lines = Files.readAllLines(Paths.get(filename), StandardCharsets.UTF_8); 
    } catch(IOException e){ 
    	System.out.println("An error occurred.");
      e.printStackTrace(); 
    }
    
    fileSizeY = lines.size();
    fileSizeX = lines.get(0).split(" ").length;
    
    String[][] board = new String[fileSizeY][fileSizeX];
    
    for(int y = 0; y < fileSizeY; y++){
    	if(fileSizeX != lines.get(y).split(" ").length){
    		System.out.println("A mismatch between column and row sizes is detected. Please fix it and try again");
    		break;
    	}
    	board[y] = lines.get(y).split(" ");
    }
    
    setSize(fileSizeX, fileSizeY);
    
    for(int y = 0; y < sizeY; y++){
			for(int x = 0; x < sizeX; x++){
				if(board[y][x].equals(formatStringByDigitCount("b", "b", Integer.toString(sizeX * sizeY - 1).length()))){
					emptyX = x;
					emptyY = y;
					setCell(y, x, -1);
				}
				else{
					setCell(y, x, convertToInt(board[y][x]));
				}
			}
		}
	}
	
	/**
	 * Writes to a text file named filename
	 * @param filename name of the text file
	 */
	public void writeToFile(String filename){
		try{
			File file = new File(filename);
			if(!file.exists() || file.isDirectory()){
				file.createNewFile();
			}
		} catch(IOException e){
			System.out.println("An error occurred.");
      e.printStackTrace();
		}
		
		try{
			FileWriter writer = new FileWriter(filename);
			String stream = "";
			for(int y = 0; y < sizeY; y++){
				stream = "";
				for(int x = 0; x < sizeX; x++){
					if(this.cell(y, x) == -1)stream += formatStringByDigitCount("b", "b", Integer.toString(sizeX * sizeY - 1).length());
					else stream += formatStringByDigitCount(Integer.toString(this.cell(y, x)), "0", Integer.toString(sizeX * sizeY - 1).length());
					
					if(x == sizeX - 1 && y != sizeY - 1)stream += "\n";
					else stream += " ";
				}
				writer.write(stream);
			}
			writer.close();
		} catch(IOException e){
			System.out.println("An error occurred.");
      e.printStackTrace();
		}
	}
	
	/**
	 * Method that resets the board configuration to solution
	 */
	public void reset(){
		for(int y = 0; y < sizeY; y++){
			for(int x = 0; x < sizeX; x++){
				setCell(y, x, y * sizeY + (x + 1));
			}
		}

		emptyX = sizeX - 1;
		emptyY = sizeY - 1;
		setCell(emptyY, emptyX, -1);
	}
	
	/**
	 * Makes a move on the board according to the given char variable
	 * @param move char variable that determines which way the board moves
	 */
	public void move(char move){
		switch(move){
			case 'L':
			case 'l':
				if(emptyX != 0 && this.cell(emptyY, emptyX - 1) != 0){
					int temp = this.cell(emptyY, emptyX);
					setCell(emptyY, emptyX, this.cell(emptyY, emptyX - 1));
					setCell(emptyY, emptyX - 1, temp);
					emptyX--;
					lastMove = 'l';
					moveCount++;
				}
				break;
			case 'R':
			case 'r':
				if(emptyX != sizeX - 1 && this.cell(emptyY, emptyX + 1) != 0){
					int temp = this.cell(emptyY, emptyX);
					setCell(emptyY, emptyX, this.cell(emptyY, emptyX + 1));
					setCell(emptyY, emptyX + 1, temp);
					emptyX++;
					lastMove = 'r';
					moveCount++;
				}
				break;
			case 'U':
			case 'u':
				if(emptyY != 0 && this.cell(emptyY - 1, emptyX) != 0){
					int temp = this.cell(emptyY, emptyX);
					setCell(emptyY, emptyX, this.cell(emptyY - 1, emptyX));
					setCell(emptyY - 1, emptyX, temp);
					emptyY--;
					lastMove = 'u';
					moveCount++;
				}
				break;
			case 'D':
			case 'd':
				if(emptyY != sizeY - 1 && this.cell(emptyY + 1, emptyX) != 0){
					int temp = this.cell(emptyY, emptyX);
					setCell(emptyY, emptyX, this.cell(emptyY + 1, emptyX));
					setCell(emptyY + 1, emptyX, temp);
					emptyY++;
					lastMove = 'd';
					moveCount++;
				}
				break;
		}
	}
	
	/**
	 * Method that checkes if the board is solution
	 * @return true if board is solution
	 */
	public boolean isSolved(){
		int currentCellValue = 0;
		for(int y = 0; y < sizeY; y++){
			for(int x = 0; x < sizeX; x++){
				if(this.cell(y, x) != 0){
					currentCellValue++;
					if(this.cell(y, x) != -1 && this.cell(y, x) != currentCellValue)return false;
				}
			}
		}
		return true;
	}
	
	/**
	 * Checks if two boards configurations are equal
	 * @param abstractBoard
	 * @return true if boards are equal
	 */
	public boolean Equals(AbstractBoard abstractBoard){
		if(sizeY == abstractBoard.getSizeY() && sizeX == abstractBoard.getSizeX()){
		 for(int y = 0; y < sizeY; y++){
		 	for(int x = 0; x < sizeX; x++){
		 		if(this.cell(y, x) != abstractBoard.cell(y, x))return false;
		 	}
		 }
	 }
	 return true;
	}
	
	/**
	 * Method that returns number of boards created and alive so far
	 * @return number of boards created and alive so far
	 */
	public int numberOfBoards(){
		return boardCount;
	}
	
	/**
	 * Method that returns amount of moves made on this board
	 * @return amount of moves made on this board
	 */
	public char lastMove(){
		return lastMove;
	}
	
	/**
	 * Method that returns last move made on this board
	 * @return last move made on this board
	 */
	public int numberOfMoves(){
		return moveCount;
	}
}
