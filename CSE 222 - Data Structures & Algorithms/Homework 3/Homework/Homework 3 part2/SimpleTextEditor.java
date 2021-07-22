import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

/**
 * Simple Text Editor class that manipulates the text read from a txt file on memory and prints it to console
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-04-02
 */
public class SimpleTextEditor {
	public static final int ARRAY_LIST = 0;
	public static final int LINKED_LIST = 1;
	private List<Character> text;
	
	/**
	 * Default constructor
	 */
	SimpleTextEditor(){
		text = new ArrayList<Character>();
	}
	/**
	 * Constructor that lets developer choose how to store the text between ArrayList and LinkedList
	 * @param listType the way that this class stores the text
	 */
	SimpleTextEditor(int listType){
		switch(listType) {
		case ARRAY_LIST:
			text = new ArrayList<Character>();
			break;
		case LINKED_LIST:
			text = new LinkedList<Character>();
			break;
		default:
			text = new ArrayList<Character>();
			break;
		}
	}
	
	/**
	 * Method that prints the text on the list to console
	 */
	public void print() {
		for(Character chr : text) {
			System.out.print(chr);
		}
	}
	
	/**
	 * Method that reads the txt file using indexes and stores it in the list
	 * @param file the path of the file
	 */
	public void readWithIndex(String file) {
		while(text.size() > 0)text.remove(0);
		Scanner myReader = null;
		try {
			myReader = new Scanner(new File(file));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
  		while (myReader.hasNextLine()) {
	  		String data = myReader.nextLine();
    		for(int i = 0; i < data.length(); i++) text.add(data.charAt(i));
    		text.add('\n');
  		}
  		myReader.close();
	}
	
	/**
	 * Method that reads the txt file using iterators and stores it in the list
	 * @param file the path of the file
	 */
	public void readWithIterator(String file) {
		while(text.size() > 0)text.remove(0);
		Scanner myReader = null;
		try {
			myReader = new Scanner(new File(file));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		ListIterator<Character> iter = text.listIterator();
  		while (myReader.hasNextLine()) {
	  		String str = myReader.nextLine();
    		for(int i = 0; i < str.length(); i++) iter.add(str.charAt(i));
    		iter.add('\n');
  		}
  		myReader.close();
	}
	
	/**
	 * Method that inserts given string into stored text on given index using indexes
	 * @param index the index string will be inserted
	 * @param str the string to be inserted
	 */
	public void addWithIndex(int index, String str) {
		for(int i = 0; i < str.length(); i++)text.add(index + i, str.charAt(i));
	}
	
	/**
	 * Method that inserts given string into stored text on given index using iterators
	 * @param index the index string will be inserted
	 * @param str the string to be inserted
	 */
	public void addWithIterator(int index, String str) {
		ListIterator<Character> iter = text.listIterator(index);
		for(int i = 0; i < str.length(); i++)iter.add(str.charAt(i));
	}
	
	/**
	 * Method that finds given string in the text and returns its index using indexes
	 * @param str String to be found
	 * @return the starting index of the string
	 */
	public int findWithIndex(String str) {
		for(int i = 0; i < text.size(); i++) {
			for(int j = 0; j < str.length() && text.get(i + j).equals(str.charAt(j)); j++) {
				if(j + 1 >= str.length())return i;
			}
		}
		return -1;
	}
	
	/**
	 * Method that finds given string in the text and returns its index using iterators
	 * @param str String to be found
	 * @return the starting index of the string
	 */
	public int findWithIterator(String str) {
		ListIterator<Character> iter = text.listIterator();
		while(iter.hasNext()) {
			for(int j = 0; j < str.length() && text.get(iter.nextIndex() + j).equals(str.charAt(j)); j++) {
				if(j + 1 >= str.length())return iter.nextIndex();
			}
			iter.next();
		}
		return -1;
	}
	
	/**
	 * Method that finds all occurrencies of a given string and replaces it with other given string using indexes
	 * @param find String to be replaced
	 * @param replace String to be replaced with
	 */
	public void findAndReplaceWithIndex(String find, String replace) {
		for(int i = 0; i < text.size(); i++) {
			for(int j = 0; j < find.length() && text.get(i + j).equals(find.charAt(j)); j++) {
				if(j + 1 >= find.length()) {
					for(int k = 0; k < find.length(); k++) text.remove(i);
					for(int k = 0; k < replace.length(); k++) text.add(i + k, replace.charAt(k));
				}
			}
		}
	}
	
	/**
	 * Method that finds all occurrencies of a given string and replaces it with other given string using iterators
	 * @param find String to be replaced
	 * @param replace String to be replaced with
	 */
	public void findAndReplaceWithIterator(String find, String replace) {
		ListIterator<Character> iter = text.listIterator();
		while(iter.hasNext()) {
			for(int j = 0; j < find.length() && text.get(iter.nextIndex() + j).equals(find.charAt(j)); j++) {
				if(j + 1 >= find.length()) {
					for(int k = 0; k < find.length(); k++) {
						iter.next();
						iter.remove();
					}
					for(int k = 0; k < replace.length(); k++) iter.add(replace.charAt(k));
				}
			}
			iter.next();
		}
	}
}
