package project.views;

import java.io.IOException;

public abstract class Page {
	public void clearScreen() {
		try {
	        if (System.getProperty("os.name").contains("Windows")) {
	        	new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
	        } else {
	        	 System.out.print("\033[H\033[2J");  
	        	 System.out.flush();
	        }
	    } catch (IOException | InterruptedException ex) {
	    	
	    }
	}
	
	public void buildPage() {
		clearScreen();
	}
}
