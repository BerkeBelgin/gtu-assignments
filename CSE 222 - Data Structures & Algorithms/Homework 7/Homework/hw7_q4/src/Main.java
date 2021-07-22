import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		Store store = new Store();
		Scanner scnnr = new Scanner(System.in);
		
		PageLogin loginPage = new PageLogin(scnnr, store);
		loginPage.build();
		
		scnnr.close();
	}

}
