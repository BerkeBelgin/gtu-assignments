import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner scnnr = new Scanner(System.in);
		
		PageLogin loginPage = new PageLogin(scnnr);
		loginPage.build();
		
		scnnr.close();
	}

}
