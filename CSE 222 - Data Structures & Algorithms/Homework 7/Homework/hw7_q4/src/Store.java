import java.util.ArrayList;

/**
 * Store class which holds all necessary information for the software store
 * @author Berke Belgin 171044065
 */
public class Store {
	/**
	 * Field that holds the password for admins
	 */
	public final String PASSWORD = "1234";
	
	/**
	 * the search three interface which holds software information
	 */
	private SearchTree<Software> softwares;
	/**
	 * An arraylist that holds the record of softwares in the store
	 */
	private ArrayList<String> softwareNames;
	/**
	 * user type field which indicates whether current iser is an admin or not
	 */
	private UserType currentUser;
	
	public Store(){
		this.softwares = new BinarySearchTree<Software>();
		this.softwareNames = new ArrayList<String>();
		addSoftware("Adobe Photoshop 6.0", 1, 40);
		addSoftware("Adobe Photoshop 6.2", 1, 80);
		addSoftware("Adobe Flash 3.3", 1, 20);
		addSoftware("Adobe Flash 4.0", 1, 50);
		addSoftware("Norton 4.5", 1, 30);
		addSoftware("Norton 5.5", 1, 60);
	}
	public Store(SearchTree<Software> store){
		this.softwares = store;
		this.softwareNames = new ArrayList<String>();
		addSoftware("Adobe Photoshop 6.0", 1, 40);
		addSoftware("Adobe Photoshop 6.2", 1, 80);
		addSoftware("Adobe Flash 3.3", 1, 20);
		addSoftware("Adobe Flash 4.0", 1, 50);
		addSoftware("Norton 4.5", 1, 30);
		addSoftware("Norton 5.5", 1, 60);
	}
	
	public UserType getCurrentUser() {
		return currentUser;
	}
	public void setCurrentUser(UserType currentUser) {
		this.currentUser = currentUser;
	}
	
	/**
	 * Method thath checks whether a software with given name exists in the store
	 * @param name name of the software
	 * @return true if exists false otherwise
	 */
	public boolean contains(String name) {
		return softwares.contains(new Software(name, 0, 0));
	}
	
	/**
	 * Method to add a software to the store
	 * @param name name of the software
	 * @param quantity quantity of the software
	 * @param price price of the software
	 */
	public void addSoftware(String name, int quantity, int price) {
		if(quantity > 0) {
			softwares.add(new Software(name, quantity, price));
			softwareNames.add(name);
		}
	}
	
	/**
	 * Method to update a softwares information
	 * @param name name of the software
	 * @param quantity quantity of the software
	 * @param price price of the software
	 */
	public void updateSoftware(String name, int quantity, int price) {
		if(softwares.contains(new Software(name, 0, 0))) {
			if(quantity <= 0) {
				deleteSoftware(name);
			} else {
				Software obj = softwares.find(new Software(name, 0, 0));
				obj.setQuantity(quantity);
				obj.setPrice(price);
			}
		} else throw new IllegalArgumentException("A software with given name could not be found");
	}

	/**
	 * Method to remove a software from the store
	 * @param name name of the software
	 */
	public void deleteSoftware(String name) {
		if(softwares.contains(new Software(name, 0, 0))) {
			softwares.remove(new Software(name, 0, 0));
			softwareNames.remove(name);
		} else throw new IllegalArgumentException("A software with given name could not be found");
	}
	
	/**
	 * Print the software with given name
	 * @param name name of the software
	 */
	public void searchByName(String name) {
		System.out.println(softwares.find(new Software(name, 0, 0)) + "\n");
	}
	
	/**
	 * Print all the softwares with given quantity
	 * @param quantity quantity of the software
	 */
	public void searchByQuantity(int quantity) {
		for(int i = 0; i < softwareNames.size(); i++) {
			Software obj = softwares.find(new Software(softwareNames.get(i), 0, 0));
			if(obj.getQuantity() == quantity) System.out.println(obj + "\n");
		}
	}
	
	/**
	 * Print all the softwares with given price
	 * @param price price of the software
	 */
	public void searchByPrice(int price) {
		for(int i = 0; i < softwareNames.size(); i++) {
			Software obj = softwares.find(new Software(softwareNames.get(i), 0, 0));
			if(obj.getPrice() == price) System.out.println(obj + "\n");
		}
	}

	/**
	 * A software class which holds the information for a single software
	 * @author Berke Belgin
	 */
	private static class Software implements Comparable<Software>{
		public final String name;
		private int quantity;
		private int price;
		
		public Software(String name, int quantity, int price){
			if(quantity < 0) throw new IllegalArgumentException("quantity can not be less than zero");
			if(price < 0) throw new IllegalArgumentException("price can not be less than zero");
			this.name = name;
			this.quantity = quantity;
			this.price = price;
		}

		public int getQuantity() {
			return quantity;
		}
		public int getPrice() {
			return price;
		}

		public void setQuantity(int quantity) {
			if(quantity >= 0) {
				this.quantity = quantity;
			} else throw new IllegalArgumentException("quantity can not be less than zero");
		}
		public void setPrice(int price) {
			if(price >= 0) {
				this.price = price;
			} else throw new IllegalArgumentException("price can not be less than zero");
		}

		@Override
		public int compareTo(Software o) {
			return name.compareTo(o.name);
		}
		
		@Override
		public String toString() {
			return "Name: " + name + "\nPrice: $" + price + "\nQuantity: " + quantity ;
		}
	}
}
