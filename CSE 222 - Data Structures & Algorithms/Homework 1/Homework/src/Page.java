

/**
 * Abstract page class for UI classes to extend
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-02-25
 */
public abstract class Page {
	/**
	 * The method that clears screen when the program is executed on any OS Terminal
	 */
	protected void clearScreen() {
		try {
	        if (System.getProperty("os.name").contains("Windows")) Runtime.getRuntime().exec("cls");
	        else Runtime.getRuntime().exec("clear");
	    } catch (final Exception e) {
	        System.out.println();
	    }
	}
	
	/**
	 * The method that builds UI on Terminal
	 */
	protected void build() {
		clearScreen();
	}
}
