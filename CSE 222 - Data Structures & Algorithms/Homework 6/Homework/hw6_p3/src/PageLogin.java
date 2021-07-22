import java.util.Scanner;

public class PageLogin implements PageUI {
	private Scanner scnnr;
	
	PageLogin(Scanner scnnr){
		this.scnnr = scnnr;
	}
	
	@Override
	public void build() {
		
		String response = "";
		
		while(!response.equals("e")) {
			do {
				System.out.println("Login Menu");
				System.out.println("Admin Login: a");
				System.out.println("Anonymous Login: n");
				System.out.println("Exit: e");
			    response = scnnr.nextLine();
			    System.out.println();
			} while(!response.equals("a") && !response.equals("n") && !response.equals("e"));
			
			switch (response) {
				case "a":
					System.out.print("Please enter the password: ");
					String password = scnnr.nextLine();
					System.out.println();
					if(password.equals(Library.PASSWORD)) {
						Library.setCurrentUser(UserType.ADMIN);
						new PageMainMenu(scnnr).build();
					}
					break;
				case "n":
					Library.setCurrentUser(UserType.ANONYMOUS);
					System.out.println();
					new PageMainMenu(scnnr).build();
					break;
			}
		}
		
		scnnr.close();
	}
}
