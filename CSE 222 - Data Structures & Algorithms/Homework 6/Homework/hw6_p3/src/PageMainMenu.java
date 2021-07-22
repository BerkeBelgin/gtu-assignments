import java.util.Scanner;
public class PageMainMenu implements PageUI{
	private Scanner scnnr;
	
	PageMainMenu(Scanner scnnr){
		this.scnnr = scnnr;
	}
	
	@Override
	public void build() {
		String response = "";
		do {
			do {
				System.out.println("a: Search by author");
				System.out.println("o: Search by book title");
				if(Library.getCurrentUser() == UserType.ADMIN)System.out.println("d: Add book");
				if(Library.getCurrentUser() == UserType.ADMIN)System.out.println("e: Delete book");
				if(Library.getCurrentUser() == UserType.ADMIN)System.out.println("u: Update book");
				System.out.println("b: back");
				response = scnnr.nextLine();
				System.out.println();
				
			} while(!response.equals("a") && !response.equals("o") && !response.equals("b") 
					&& !(response.equals("d") && Library.getCurrentUser() == UserType.ADMIN) 
					&& !(response.equals("e") && Library.getCurrentUser() == UserType.ADMIN) 
					&& !(response.equals("u") && Library.getCurrentUser() == UserType.ADMIN));
			switch(response) {
		    	case "a":
		    		System.out.print("Author name: ");
		    		Library.searchByAuthor(scnnr.nextLine());
		    		System.out.println();
		    		break;
		    	case "o":
		    		System.out.print("Book name: ");
		    		Library.searchByBook(scnnr.nextLine());
		    		System.out.println();
		    		break;
		    	case "d":
		    		System.out.print("Author name: ");
		    		String addAuthor = scnnr.nextLine();
		    		System.out.print("Book name: ");
		    		String addBook = scnnr.nextLine();
		    		System.out.print("Corridor index: ");
		    		String addCorridor = scnnr.nextLine();
		    		System.out.print("Shelf Index: ");
		    		String addShelf = scnnr.nextLine();
		    		System.out.print("Book Index: ");
		    		String addIndex = scnnr.nextLine();
		    		Library.addBook(addAuthor, addBook, addCorridor, addShelf, addIndex);
		    		System.out.println();
		    		break;
		    	case "e":
		    		System.out.print("Book name: ");
		    		String deleteBook = scnnr.nextLine();
		    		System.out.print("Corridor index: ");
		    		String deleteCorridor = scnnr.nextLine();
		    		System.out.print("Shelf Index: ");
		    		String deleteShelf = scnnr.nextLine();
		    		System.out.print("Book Index: ");
		    		String deleteIndex = scnnr.nextLine();
		    		if(Library.doesBookExist(deleteBook, deleteCorridor, deleteShelf, deleteIndex)) {
		    			Library.removeBook(deleteBook, deleteCorridor, deleteShelf, deleteIndex);
			    		System.out.println();
		    		} else {
		    			System.out.println("The book couldn't be found.");
		    			System.out.println();
		    		}
		    		break;
		    	case "u":
		    		System.out.print("Book name: ");
		    		String updateOldBook = scnnr.nextLine();
		    		System.out.print("Old Corridor index: ");
		    		String updateOldCorridor = scnnr.nextLine();
		    		System.out.print("Old Shelf Index: ");
		    		String updateOldShelf = scnnr.nextLine();
		    		System.out.print("Old Book Index: ");
		    		String updateOldIndex = scnnr.nextLine();
		    		if(Library.doesBookExist(updateOldBook, updateOldCorridor, updateOldShelf, updateOldIndex)) {
		    			System.out.println();
			    		
			    		System.out.print("New Corridor index: ");
			    		String updateNewCorridor = scnnr.nextLine();
			    		System.out.print("New Shelf Index: ");
			    		String updateNewShelf = scnnr.nextLine();
			    		System.out.print("New Book Index: ");
			    		String updateNewIndex = scnnr.nextLine();
			    		Library.updateBook(updateOldBook, updateOldCorridor, updateOldShelf, updateOldIndex, updateNewCorridor, updateNewShelf, updateNewIndex);
			    		System.out.println();
		    		} else {
		    			System.out.println("The book couldn't be found.");
		    			System.out.println();
		    		}
		    		break;
		    }
		} while(!response.equals("b"));
	}

}
