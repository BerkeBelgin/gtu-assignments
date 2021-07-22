/**
 * A board class that represents the board as 2D array
 * @author Berke Belgin
 */
public class BoardArray2D extends AbstractBoard{
	private int[][] board;
	
	public BoardArray2D(){
		super();
	}
	public BoardArray2D(int y, int x){
		super(y, x);
	}
	
	protected void finalize(){
		super.finalize();
	}
	
	public void setCell(int y, int x, int value){
		board[y][x] = value;
	}
	public void setSize(int sizeY, int sizeX){
		board = new int[sizeY][sizeX];
		
		this.sizeY = sizeY;
		this.sizeX = sizeX;
	}
	public int cell(int y, int x){
		if(y < sizeY && x < sizeX){
			return board[y][x];
		} else{
			System.exit(0);
			return 0;
		}
	}
}
