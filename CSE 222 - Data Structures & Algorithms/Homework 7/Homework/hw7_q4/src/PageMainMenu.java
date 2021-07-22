import java.util.Scanner;

/**
 * Main menu of the application where users can search softwares and admins can add update delete software informations
 * @author Berke Belgin 171044065
 */
public class PageMainMenu implements PageUI{
	private Scanner scnnr;
	private Store store;
	PageMainMenu(Scanner scnnr, Store store){
		this.scnnr = scnnr;
		this.store = store;
	}
	
	@Override
	public void build() {
		String response = "";
		do {
			do {
				System.out.println("n: Search by name");
				System.out.println("q: Search by quantity");
				System.out.println("p: Search by price");
				if(store.getCurrentUser() == UserType.ADMIN)System.out.println("a: Add software");
				if(store.getCurrentUser() == UserType.ADMIN)System.out.println("d: Delete software");
				if(store.getCurrentUser() == UserType.ADMIN)System.out.println("u: Update software");
				System.out.println("b: back");
				response = scnnr.nextLine();
				System.out.println();
				
			} while(!response.equals("n") && !response.equals("q") && !response.equals("p") && !response.equals("b") 
					&& !(response.equals("a") && store.getCurrentUser() == UserType.ADMIN) 
					&& !(response.equals("d") && store.getCurrentUser() == UserType.ADMIN) 
					&& !(response.equals("u") && store.getCurrentUser() == UserType.ADMIN));
			switch(response) {
		    	case "n":
		    		System.out.print("Software name: ");
		    		store.searchByName(scnnr.nextLine());
		    		System.out.println("\n");
		    		break;
		    	case "q":
		    		System.out.print("Software quantity: ");
		    		store.searchByQuantity(scnnr.nextInt());
		    		System.out.println("\n");
		    		break;
		    	case "p":
		    		System.out.print("Software price: ");
		    		store.searchByPrice(scnnr.nextInt());
		    		System.out.println("\n");
		    		break;
		    	case "a":
		    		System.out.print("Software name: ");
		    		String addName= scnnr.nextLine();
		    		if(!store.contains(addName)) {
		    			System.out.print("Software quantity: ");
			    		int addQuantity = scnnr.nextInt();
			    		System.out.print("Software price: ");
			    		int addPrice = scnnr.nextInt();
			    		store.addSoftware(addName, addQuantity, addPrice);
		    		} else System.out.println("The software already exists");
		    		System.out.println("\n");
		    		break;
		    	case "d":
		    		System.out.print("Software name: ");
		    		String delName= scnnr.nextLine();
		    		if(store.contains(delName)) {
		    			store.deleteSoftware(delName);
		    			System.out.println("\n");
		    		} else System.out.println("The software does not exist\n");
		    		break;
		    	case "u":
		    		System.out.print("Software name: ");
		    		String updateName= scnnr.nextLine();
		    		if(store.contains(updateName)) {
		    			System.out.print("Software quantity: ");
			    		int updateQuantity = scnnr.nextInt();
			    		System.out.print("Software price: ");
			    		int updatePrice = scnnr.nextInt();
			    		store.updateSoftware(updateName, updateQuantity, updatePrice);
		    		} else System.out.println("The software does not exists");
		    		System.out.println("\n");
		    		break;
		    }
		} while(!response.equals("b"));
	}

}
