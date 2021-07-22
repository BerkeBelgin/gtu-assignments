


/**
 * Company controller class which handles all operations of the company as managing Employees, Customers, Branches, Shipments etc.
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-02-25
 */
public class Company {
	/**
	 * array of customers the company has
	 */
	private static Customer[] customers = new Customer[0];
	/**
	 * array of employees the company has
	 */
	private static Employee[] employees = new Employee[0];
	/**
	 * array of branches the company has
	 */
	private static Branch[] branches = new Branch[0];
	/**
	 * array of shipments the company has
	 */
	private static Shipment[] shipments = new Shipment[0];
	
	/**
	 * Method that checks if does company have an customer with the given id
	 * @param id the Id of the customer
	 * @return boolean
	 */
	public static boolean doesCustomerExist(int id) {
		for(Customer customer : customers) {
			if(customer.getTrackingId() == id) return true;
		}
		return false;
	}
	/**
	 * Method that checks if does company have an employee with the given id
	 * @param id the Id of the employee
	 * @return boolean
	 */
	public static boolean doesEmployeeExist(int id) {
		for(Employee employee : employees) {
			if(employee.getId() == id) return true;
		}
		return false;
	}
	/**
	 * Method that checks if does company have a branch with the given id
	 * @param id the Id of the branch
	 * @return boolean
	 */
	public static boolean doesBranchExist(int id) {
		for(Branch branch : branches) {
			if(branch.getId() == id) return true;
		}
		return false;
	}
	/**
	 * Method that checks if does company have a shipment with the given id
	 * @param id the Id of the shipment
	 * @return boolean
	 */
	public static boolean doesShipmentExist(int id) {
		for(Shipment shipment : shipments) {
			if(shipment.getId() == id) return true;
		}
		return false;
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
		for(Employee employee : employees) {
			if(employee instanceof BranchEmployee)System.out.println(employee.toString());
		}
	}
	/**
	 * Method that prints all transport personnels the company has like a table in Terminal
	 */
	public static void showTransportPersonnels() {
		System.out.println("TransportPersonnels:");
		for(Employee employee : employees) {
			if(employee instanceof TransportPersonnel)System.out.println(employee.toString());
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
	 * @param id id of the employee
	 */
	public static void showShipmentsByBranchId(int id) {
		System.out.println("Shipments:");
		for(Shipment shipment : shipments) {
			if(shipment.getBranch().getId() == id)System.out.println(shipment.toString());
		}
	}
	
	/**
	 * Method that gets the customer with the given id in company
	 * @param id id of the customer
	 * @return Customer returns the customer as an object
	 */
	public static Customer getCustomer(int id) {
		for(Customer customer : customers) {
			if(customer.getTrackingId() == id)return customer;
		}
		return null;
	}
	/**
	 * Method that gets the employee with the given id in company
	 * @param id id of the employee
	 * @return Employee returns the employee as an object
	 */
	public static Employee getEmployee(int id) {
		for(Employee employee : employees) {
			if(employee.getId() == id)return employee;
		}
		return null;
	}
	/**
	 * Method that gets the branch with the given id in company
	 * @param id id of the branch
	 * @return Branch returns the branch as an object
	 */
	public static Branch getBranch(int id) {
		for(Branch branch : branches) {
			if(branch.getId() == id)return branch;
		}
		return null;
	}
	/**
	 * Method that gets the shipment with the given id in company
	 * @param id id of the shipment
	 * @return Shipment returns the shipment as an object
	 */
	public static Shipment getShipment(int id) {
		for(Shipment shipment : shipments) {
			if(shipment.getId() == id)return shipment;
		}
		return null;
	}
	
	public static Customer[] getCustomers() {
		return customers;
	}
	public static Employee[] getEmployees() {
		return employees;
	}
	public static Branch[] getBranches() {
		return branches;
	}
	public static Shipment[] getShipments() {
		return shipments;
	}
	
	/**
	 * Method that inserts customer at the end of the customers array
	 * @param customer customer as an object
	 */
	public static void insertCustomer(Customer customer) {
		if(customers.length > 0)customer.setTrackingId(customers[customers.length - 1].getTrackingId() + 1);
		else customer.setTrackingId(1);
		
		Customer[] temp = new Customer[customers.length + 1];
		for(int i = 0; i < customers.length; i++) {
			temp[i] = customers[i];
		}
		temp[temp.length - 1] = customer;
		customers = temp;
	}
	/**
	 * Method that inserts employee at the end of the employees array
	 * @param employee employee as an object
	 */
	public static void insertEmployee(Employee employee) {
		if(employees.length > 0)employee.setId(employees[employees.length - 1].getId() + 1);
		else employee.setId(1);
		
		Employee[] temp = new Employee[employees.length + 1];
		for(int i = 0; i < employees.length; i++) {
			temp[i] = employees[i];
		}
		temp[temp.length - 1] = employee;
		employees = temp;
	}
	/**
	 * Method that inserts branch at the end of the branches array
	 * @param branch branch as an object
	 */
	public static void insertBranch(Branch branch) {
		if(branches.length > 0)branch.setId(branches[branches.length - 1].getId() + 1);
		else branch.setId(1);
		
		Branch[] temp = new Branch[branches.length + 1];
		for(int i = 0; i < branches.length; i++) {
			temp[i] = branches[i];
		}
		temp[temp.length - 1] = branch;
		branches = temp;
	}
	/**
	 * Method that inserts shipment at the end of the shipments array
	 * @param shipment shipment as an object
	 */
	public static void insertShipment(Shipment shipment) {
		if(shipments.length > 0)shipment.setId(shipments[shipments.length - 1].getId() + 1);
		else shipment.setId(1);
		
		Shipment[] temp = new Shipment[shipments.length + 1];
		for(int i = 0; i < shipments.length; i++) {
			temp[i] = shipments[i];
		}
		temp[temp.length - 1] = shipment;
		shipments = temp;
	}
	
	/**
	 * Method that deletes the customer with the given id
	 * @param id id of the customer
	 */
	public static void deleteCustomer(int id) {
		if(customers.length > 0 && doesCustomerExist(id)) {
			Customer[] temp = new Customer[customers.length - 1];
			int tempIndex = 0;
			int originalIndex = 0;
			while( originalIndex < customers.length) {
				if(customers[originalIndex].getTrackingId() != id) {
					temp[tempIndex] = customers[originalIndex];
					tempIndex++;
				}
				originalIndex++;
			}
			customers = temp;
		}
	}
	/**
	 * Method that deletes the employee with the given id
	 * @param id id of the employee
	 */
	public static void deleteEmployee(int id) {
		if(employees.length > 0 && doesEmployeeExist(id)) {
			Employee[] temp = new Employee[employees.length - 1];
			int tempIndex = 0;
			int originalIndex = 0;
			while( originalIndex < employees.length) {
				if(employees[originalIndex].getId() != id) {
					temp[tempIndex] = employees[originalIndex];
					tempIndex++;
				}
				originalIndex++;
			}
			employees = temp;
		}
	}
	/**
	 * Method that deletes the branch with the given id
	 * @param id id of the branch
	 */
	public static void deleteBranch(int id) {
		if(branches.length > 0 && doesBranchExist(id)) {
			Branch[] temp = new Branch[branches.length - 1];
			int tempIndex = 0;
			int originalIndex = 0;
			while( originalIndex < branches.length) {
				if(branches[originalIndex].getId() != id) {
					temp[tempIndex] = branches[originalIndex];
					tempIndex++;
				}
				originalIndex++;
			}
			branches = temp;
		}
	}
	/**
	 * Method that deletes the shipment with the given id
	 * @param id id of the shipment
	 */
	public static void deleteShipment(int id) {
		if(shipments.length > 0 && doesShipmentExist(id)) {
			Shipment[] temp = new Shipment[shipments.length - 1];
			int tempIndex = 0;
			int originalIndex = 0;
			while( originalIndex < shipments.length) {
				if(shipments[originalIndex].getId() != id) {
					temp[tempIndex] = shipments[originalIndex];
					tempIndex++;
				}
				originalIndex++;
			}
			shipments = temp;
		}
	}
}
