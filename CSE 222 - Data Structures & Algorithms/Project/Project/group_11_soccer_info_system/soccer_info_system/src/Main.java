import java.util.Scanner;

import project.views.LoginPage;

public class Main {
	public static void main(String[] args) {
		Scanner scnnr = new Scanner(System.in);
		LoginPage loginPage = new LoginPage(scnnr);
		loginPage.buildPage();
		scnnr.close();
	}
}
