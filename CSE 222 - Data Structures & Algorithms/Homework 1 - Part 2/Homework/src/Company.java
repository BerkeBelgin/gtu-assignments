

import java.util.ArrayList;
import java.util.List;

/**
 * Company class which stores datas of the company like Employees, Customers, Branches, Shipments etc.
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-03-03
 */
public abstract class Company {
	/**
	 * list of customers the company has
	 */
	protected static List<Customer> customers = new ArrayList<Customer>();
	/**
	 * admin of the company
	 */
	protected static Admin admin = new Admin();
	/**
	 * list of employees the company has
	 */
	protected static List<BranchEmployee> branchEmployees = new ArrayList<BranchEmployee>();
	/**
	 * list of employees the company has
	 */
	protected static List<TransportPersonnel> transportPersonnels = new ArrayList<TransportPersonnel>();
	/**
	 * list of branches the company has
	 */
	protected static List<Branch> branches = new ArrayList<Branch>();
	/**
	 * list of shipments the company has
	 */
	protected static List<Shipment> shipments = new ArrayList<Shipment>();

	/**
	 * Method that gets the customer with the given id in company
	 * @param id id of the customer
	 * @return int returns the index of the customer with given id
	 * @throws Exception throws excepiton if id is wrong
	 */
	protected static int getCustomerIndexById(int id) throws Exception{
		for(int i = 0; i < customers.size(); i++) {
			if(customers.get(i).getTrackingId() == id)return i;
		}
		throw new Exception("Customer could not found.");
	}
	/**
	 * Method that gets the employee with the given id in company
	 * @param id id of the employee
	 * @return int returns the index of the branch employee with given id
	 * @throws Exception throws excepiton if id is wrong
	 */
	protected static int getBranchEmployeeIndexById(int id) throws Exception{
		for(int i = 0; i < branchEmployees.size(); i++) {
			if(branchEmployees.get(i).getId() == id)return i;
		}
		throw new Exception("Branch Employee could not found.");
	}
	/**
	 * Method that gets the employee with the given id in company
	 * @param id id of the employee
	 * @return int returns the index of the transport personnel with given id
	 * @throws Exception throws excepiton if id is wrong
	 */
	protected static int getTransportPersonnelIndexById(int id) throws Exception{
		for(int i = 0; i < transportPersonnels.size(); i++) {
			if(transportPersonnels.get(i).getId() == id)return i;
		}
		throw new Exception("Transport Personnel could not found.");
	}
	/**
	 * Method that gets the branch with the given id in company
	 * @param id id of the branch
	 * @return int returns the index of the branch with given id
	 * @throws Exception throws excepiton if id is wrong
	 */
	protected static int getBranchIndexById(int id) throws Exception{
		for(int i = 0; i < branches.size(); i++) {
			if(branches.get(i).getId() == id)return i;
		}
		throw new Exception("Branch could not found.");
	}
	/**
	 * Method that gets the shipment with the given id in company
	 * @param id id of the shipment
	 * @return int returns the index of the shipment with given id
	 * @throws Exception throws excepiton if id is wrong
	 */
	protected static int getShipmentIndexById(int id) throws Exception{
		for(int i = 0; i < shipments.size(); i++) {
			if(shipments.get(i).getId() == id)return i;
		}
		throw new Exception("Shipment could not found.");
	}

	/**
	 * Method that gets the customer with the given id in company
	 * @param id id of the customer
	 * @return Customer returns the customer as an object
	 * @throws Exception throws excepiton if id is wrong
	 */
	public static Customer getCustomer(int id) throws Exception {
		return customers.get(getCustomerIndexById(id));
	}
	
	/**
	 * Method that gets the admin
	 * @return Admin returns the admin of the company
	 */
	public static Admin getAdmin() {
		return admin;
	}
	
	/**
	 * Method that gets the branch employee with the given id in company
	 * @param id id of the branch employee
	 * @return BranchEmployee returns the branch employee as an object
	 * @throws Exception throws excepiton if id is wrong
	 */
	public static BranchEmployee getBranchEmployee(int id) throws Exception {
		return branchEmployees.get(getBranchEmployeeIndexById(id));
	}
	
	/**
	 * Method that gets the transport personnel with the given id in company
	 * @param id id of the transport personnel
	 * @return TransportPersonnel returns the transport personnel as an object
	 * @throws Exception throws excepiton if id is wrong
	 */
	public static TransportPersonnel getTransportPersonnel(int id) throws Exception {
		return transportPersonnels.get(getTransportPersonnelIndexById(id));
	}
	
	/**
	 * Method that prints all customers the company has like a table in Terminal
	 */
	public static void showCustomers() {
		System.out.println("Customers:");
		for(Customer customer : customers) {
			System.out.println(customer.toString());
		}
	}
	/**
	 * Method that prints all branch employees the company has like a table in Terminal
	 */
	public static void showBranchEmployees() {
		System.out.println("BranchEmployees:");
		for(BranchEmployee employee : branchEmployees) {
			System.out.println(employee.toString());
		}
	}
	/**
	 * Method that prints all transport personnels the company has like a table in Terminal
	 */
	public static void showTransportPersonnels() {
		System.out.println("TransportPersonnels:");
		for(TransportPersonnel employee : transportPersonnels) {
			System.out.println(employee.toString());
		}
	}
	/**
	 * Method that prints all branches the company has like a table in Terminal
	 */
	public static void showBranches() {
		System.out.println("Branches:");
		for(Branch branch : branches) {
			System.out.println(branch.toString());
		}
	}
	/**
	 * Method that prints all shipments the company has like a table in Terminal
	 */
	public static void showShipments() {
		System.out.println("Shipments:");
		for(Shipment shipment : shipments) {
			System.out.println(shipment.toString());
		}
	}
	/**
	 * Method that prints all shipments the company has with the given id like a table in Terminal
	 * @param id id of the branch
	 */
	public static void showShipmentsByBranchId(int id) {
		System.out.println("Shipments:");
		for(Shipment shipment : shipments) {
			if(shipment.getBranch().getId() == id)System.out.println(shipment.toString());
		}
	}
}
