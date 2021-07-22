import java.util.Scanner;

/**
 * Login Page for the store
 * @author Berke Belgin 171044065
 */
public class PageLogin implements PageUI {
	private Scanner scnnr;
	private Store store;
	PageLogin(Scanner scnnr, Store store){
		this.scnnr = scnnr;
		this.store = store;
	}
	
	@Override
	public void build() {
		
		String response = "";
		
		while(!response.equals("e")) {
			do {
				System.out.println("Login Menu");
				System.out.println("Admin Login: a");
				System.out.println("User Login: u");
				System.out.println("Exit: e");
			    response = scnnr.nextLine();
			    System.out.println();
			} while(!response.equals("a") && !response.equals("u") && !response.equals("e"));
			
			switch (response) {
				case "a":
					System.out.print("Please enter the password: ");
					String password = scnnr.nextLine();
					System.out.println();
					if(password.equals(store.PASSWORD)) {
						store.setCurrentUser(UserType.ADMIN);
						new PageMainMenu(scnnr, store).build();
					}
					break;
				case "u":
					store.setCurrentUser(UserType.USER);
					System.out.println();
					new PageMainMenu(scnnr, store).build();
					break;
			}
		}
		
		scnnr.close();
	}
}
