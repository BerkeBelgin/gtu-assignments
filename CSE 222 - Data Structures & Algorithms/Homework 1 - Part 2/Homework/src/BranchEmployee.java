

/**
 * BranchEmployee class to be used to handle branch employee operations such as inserting/deleting shipments, customers etc. from the company
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-03-03
 */
public class BranchEmployee extends Company implements Employee{
	/**
	 * Company branch that this employee is tied to
	 */
	private final Branch branch;
	/**
	 * id of the employee
	 */
	private int id;
	/**
	 * First name of the employee
	 */
	private String firstName;
	/**
	 * Last name of the employee
	 */
	private String lastName;
	
	public BranchEmployee(int id, String firstName, String lastName, Branch branch) {
		this.id = id;
		this.firstName = firstName;
		this.lastName = lastName;
		this.branch = branch;
	}
	
	public int getId() {
		return id;
	}
	public String getFirstName() {
		return firstName;
	}
	public String getLastName() {
		return lastName;
	}
	public Branch getBranch() {
		return branch;
	}
	
	public String toString() {
		return String.format("%d %s %s %s", id, firstName, lastName, branch.getName());
	}
	
	/**
	 * Method that inserts customer at the end of the customers arrayList
	 * @param firstName first name of the customer
	 * @param lastName last name of the customer
	 */
	public void insertCustomer(String firstName, String lastName) {
		int id = customers.size() > 0 ? customers.get(customers.size() - 1).getTrackingId() + 1 : 1;
		customers.add(new Customer(id, firstName, lastName));
	}
	
	/**
	 * Method that inserts shipment at the end of the shipments arrayList
	 * @param sendingCustomerId id of the shipments sender
	 * @param recievingCustomerId id of the shipmetns reciever
	 * @throws Exception throws exception if customer with one of the ids does not exist 
	 */
	public void insertShipment(int sendingCustomerId, int recievingCustomerId) throws Exception {
		int id = shipments.size() > 0 ? shipments.get(shipments.size() - 1).getId() + 1 : 1;
		shipments.add(new Shipment(
				id,
				customers.get(getCustomerIndexById(sendingCustomerId)),
				customers.get(getCustomerIndexById(recievingCustomerId)),
				branch,
				Shipment.GETTING_PREPARED
		));
	}
	
	/**
	 * Method that deletes the customer with the given id
	 * @param id id of the customer
	 * @throws Exception throws exception if no customer exists with given id
	 */
	public void deleteCustomer(int id) throws Exception {
		customers.remove(getCustomerIndexById(id));
	}
	
	/**
	 * Method that deletes the shipment with the given id
	 * @param id id of the shipment
	 * @throws Exception throws exception if no customer exists with given id
	 */
	public void deleteShipment(int id) throws Exception {
		shipments.remove(getShipmentIndexById(id));
	}
	
	public void updateShipmentStatus(int id, int status) throws Exception {
		shipments.get(getShipmentIndexById(id)).setStatus(status);
	}
}
