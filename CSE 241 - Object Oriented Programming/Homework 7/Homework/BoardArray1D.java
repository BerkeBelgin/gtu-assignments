/**
 * A board class that represents the board as 1D array
 * @author Berke Belgin
 */
public class BoardArray1D extends AbstractBoard{
	private int[] board;
	
	public BoardArray1D(){
		super();
	}
	public BoardArray1D(int y, int x){
		super(y, x);
	}
	
	protected void finalize(){
		super.finalize();
	}
	
	public void setCell(int y, int x, int value){
		board[y * sizeY + x] = value;
	}
	public void setSize(int sizeY, int sizeX){
		board = new int[sizeY * sizeX];
		
		this.sizeY = sizeY;
		this.sizeX = sizeX;
	}
	public int cell(int y, int x){
		if(y < sizeY && x < sizeX){
			return board[y * sizeY + x];
		} else{
			System.exit(0);
			return 0;
		}
	}
}
