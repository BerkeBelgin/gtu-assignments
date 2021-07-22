import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.Map.Entry;

/**
 * A class to hold general data like books, admin password etc.
 * @author Berke Belgin 171044065
 */
public class Library {
	/**
	 * The password an admin should enter
	 */
	public static final String PASSWORD = "1234";
	/**
	 * Type of the user (anonymous or admin)
	 */
	private static UserType currentUser = null;
	/**
	 * The map that holds authors and their books
	 */
	private static Map<String, Map<String, Set<String>>> authors = new HashMap<String, Map<String, Set<String>>>();
	
	
	public static UserType getCurrentUser() {
		return currentUser;
	}
	public static void setCurrentUser(UserType currentUser) {
		Library.currentUser = currentUser;
	}
	public static Map<String, Map<String, Set<String>>> getAuthors() {
		return authors;
	}
	
	/**
	 * Method that prints every book of the given author
	 * @param authorName the name of the author
	 */
	public static void searchByAuthor(String authorName) {
		if(Library.getAuthors().containsKey(authorName)) {
			Iterator<Entry<String, Set<String>>> authorIter = Library.getAuthors().get(authorName).entrySet().iterator();
			while(authorIter.hasNext()) {
				Entry<String, Set<String>> eAuthor = authorIter.next();
				Iterator<String> bookIter = eAuthor.getValue().iterator();
				while(bookIter.hasNext()) {
					System.out.println(authorName + " - " + eAuthor.getKey() + " - " + bookIter.next());
				}
			}
		}
	}
	
	
	/**
	 * Method that prints every book with the given name
	 * @param book the name of the book
	 */
	public static void searchByBook(String book) {
		Iterator<Entry<String, Map<String, Set<String>>>> iter = Library.getAuthors().entrySet().iterator();
		while(iter.hasNext()) {
			Entry<String, Map<String, Set<String>>> eAuthor = iter.next();
			if(eAuthor.getValue().containsKey(book)) {
				Iterator<String> locIter = eAuthor.getValue().get(book).iterator();
				while(locIter.hasNext()) {
					System.out.println(eAuthor.getKey() + " - " + book + " - " + locIter.next());
				}
			}
		}
	}
	
	/**
	 * Adds book to the map
	 * @param author the name of the author
	 * @param book the name of the book
	 * @param corridor corridor index
	 * @param shelf shelf index
	 * @param index book index
	 */
	public static void addBook(String author, String book, String corridor, String shelf, String index) {
		String loc = "c" + corridor + "s" + shelf + "." + index;
		
		if(Library.getAuthors().containsKey(author)) {
			if(Library.getAuthors().get(author).containsKey(book)) {
				if(Library.getAuthors().get(author).get(book).contains(loc)) {
					System.out.println(author + " - " + book + " - " + loc + " already exists.");
				} else {
					Library.getAuthors().get(author).get(book).add(loc);
				}
			} else {
				Set<String> set = new HashSet<String>();
				set.add("c" + corridor + "s" + shelf + "." + index);
				Library.getAuthors().get(author).put(book, set);
			}
		} else {
			Map<String, Set<String>> books = new HashMap<String, Set<String>>();
			Set<String> set = new HashSet<String>();
			set.add("c" + corridor + "s" + shelf + "." + index);
			books.put(book, set);
			Library.getAuthors().put(author, books);
		}
	}
	
	/**
	 * Checks whether given book exists in the library or not.
	 * @param bookName the name of the book
	 * @param corridor corridor index
	 * @param shelf shelf index
	 * @param index book index
	 * @return true if the book exists or false otherwise
	 */
	public static boolean doesBookExist(String bookName, String corridor, String shelf, String index) {
		String oldLoc = "c" + corridor + "s" + shelf + "." + index;
		
		Iterator<Entry<String, Map<String, Set<String>>>> iter = Library.getAuthors().entrySet().iterator();
		while(iter.hasNext()) {
			Entry<String, Map<String, Set<String>>> eAuthor = iter.next();
			if(eAuthor.getValue().containsKey(bookName)) {
				if(eAuthor.getValue().get(bookName).contains(oldLoc)) {
					return true;
				}
			}
		}
		return false;
	}
	
	/**
	 * Updates the location of the given book
	 * @param bookName name of the book
	 * @param oldCorridor old corridor index
	 * @param oldShelf old shelf index
	 * @param oldIndex old book index
	 * @param newCorridor new corridor index
	 * @param newShelf new shelf index
	 * @param newIndex new book index
	 */
	public static void updateBook(String bookName, String oldCorridor, String oldShelf, String oldIndex, String newCorridor, String newShelf, String newIndex) {
		String oldLoc = "c" + oldCorridor + "s" + oldShelf + "." + oldIndex;
		String newLoc = "c" + newCorridor + "s" + newShelf + "." + newIndex;
		
		Iterator<Entry<String, Map<String, Set<String>>>> iter = Library.getAuthors().entrySet().iterator();
		while(iter.hasNext()) {
			Entry<String, Map<String, Set<String>>> eAuthor = iter.next();
			if(eAuthor.getValue().containsKey(bookName)) {
				if(eAuthor.getValue().get(bookName).contains(oldLoc)) {
		    		eAuthor.getValue().get(bookName).remove(oldLoc);
		    		eAuthor.getValue().get(bookName).add(newLoc);
				}
			}
		}
	}

	/**
	 * Removes the given book
	 * @param deleteBook name of the book to be deleted
	 * @param deleteCorridor corridor index
	 * @param deleteShelf shelf index
	 * @param deleteIndex book index
	 */
	public static void removeBook(String deleteBook, String deleteCorridor, String deleteShelf, String deleteIndex) {
		String loc = "c" + deleteCorridor + "s" + deleteShelf + "." + deleteIndex;
		
		Iterator<Entry<String, Map<String, Set<String>>>> iter = Library.getAuthors().entrySet().iterator();
		while(iter.hasNext()) {
			Entry<String, Map<String, Set<String>>> eAuthor = iter.next();
			if(eAuthor.getValue().containsKey(deleteBook)) {
				Set<String> locations = eAuthor.getValue().get(deleteBook);
				if(locations.contains(loc)) {
					locations.remove(loc);
		    		if(locations.isEmpty())eAuthor.getValue().remove(deleteBook);
		    		if(eAuthor.getValue().isEmpty())iter.remove();
				}
			}
		}
	}
}
