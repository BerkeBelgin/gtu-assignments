package project.views;

import java.util.Scanner;

import project.models.Football;

public class SignUpPage extends Page {
	private Scanner scnnr;
	
	public SignUpPage(Scanner scnnr) {
		this.scnnr = scnnr;
	}
	 @Override
	public void buildPage() {
		 super.buildPage();
		int choice = 0;
		
		do {
			System.out.println("1) Sign Up ");
			System.out.println("2) Log In ");
			System.out.println("3) Quit");
			choice = Integer.parseInt(scnnr.nextLine());
			
			switch (choice) {
			case 1:
				System.out.print("First Name: ");
				String firstName = scnnr.nextLine();
				System.out.print("Last Name: ");
				String lastName = scnnr.nextLine();
				System.out.print("username: ");
				String username = scnnr.nextLine();
				System.out.print("password: ");
				String password = scnnr.nextLine();
				if(!Football.userExists(username, password)) {
					Football.addUser(firstName, lastName, username, password);
					Football.identity = username;
					ChooseFederationPage cfp = new ChooseFederationPage(scnnr);
					cfp.buildPage();
				}
				break;
			case 2:
				SignUpPage sp = new SignUpPage(scnnr);
				sp.buildPage();
				break;
			}
		} while(choice != 3);
	}
}
