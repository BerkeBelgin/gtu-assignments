

/**
 * A class o test if everything works correctly
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-02-25
 */
public class Test {
	/**
	 * A method to call to test if whole program works correctly
	 */
	public static void test() {
		System.out.println("Creating branches...");
		
		Company.insertBranch(new Branch("Kadikoy"));
		Company.insertBranch(new Branch("Kartal"));
		Company.insertBranch(new Branch("Maltepe"));
		
		System.out.println("Creating Employees...");
		
		Company.insertEmployee(
			new BranchEmployee(
				Company.getBranch(1),
				"Lara",
				"Croft"
			)
		);
		Company.insertEmployee(
			new BranchEmployee(
				Company.getBranch(1),
				"Captain",
				"Price"
			)
		);
		Company.insertEmployee(
			new BranchEmployee(
				Company.getBranch(2),
				"Geralt",
				"Rivia"
			)
		);
		Company.insertEmployee(
			new BranchEmployee(
				Company.getBranch(2),
				"Adolf",
				"Kinder"
			)
		);
		
		Company.insertEmployee(
			new TransportPersonnel(
				"Luke",
				"Skywalker"
			)
		);
		Company.insertEmployee(
			new TransportPersonnel(
				"Obi Wan",
				"Kenobi"
			)
		);
		Company.insertEmployee(
			new TransportPersonnel(
				"Dol",
				"Amaroth"
			)
		);
		Company.insertEmployee(
			new TransportPersonnel(
				"Minas",
				"Tirith"
			)
		);
		Company.insertEmployee(
			new TransportPersonnel(
				"Enes",
				"Batur"
			)
		);
		
		System.out.println("Creating customers...");
		
		Company.insertCustomer(
			new Customer(
				"Winston",
				"Churchill"
			)
		);
		Company.insertCustomer(
			new Customer(
				"Benito",
				"Musollini"
			)
		);
		Company.insertCustomer(
			new Customer(
				"Neil",
				"Armstrong"
			)
		);
		Company.insertCustomer(
			new Customer(
				"Tony",
				"Stark"
			)
		);
		Company.insertCustomer(
			new Customer(
				"Bruce",
				"Banner"
			)
		);
		Company.insertCustomer(
			new Customer(
				"Howard",
				"Stark"
			)
		);
		Company.insertCustomer(
			new Customer(
				"Kylo",
				"Ren"
			)
		);
		
		System.out.println("Creating shipments...\n\n");
		
		Company.insertShipment(
			new Shipment(
				Company.getCustomer(1),
				Company.getCustomer(3),
				Company.getBranch(1),
				Shipment.GETTING_PREPARED
			)
		);
		Company.insertShipment(
			new Shipment(
				Company.getCustomer(5),
				Company.getCustomer(2),
				Company.getBranch(1),
				Shipment.GETTING_PREPARED
			)
		);
		Company.insertShipment(
			new Shipment(
				Company.getCustomer(4),
				Company.getCustomer(1),
				Company.getBranch(2),
				Shipment.GETTING_PREPARED
			)
		);
		Company.insertShipment(
			new Shipment(
				Company.getCustomer(2),
				Company.getCustomer(3),
				Company.getBranch(2),
				Shipment.GETTING_PREPARED
			)
		);
		Company.insertShipment(
			new Shipment(
				Company.getCustomer(7),
				Company.getCustomer(5),
				Company.getBranch(3),
				Shipment.ON_THE_WAY
			)
		);
		
		Company.showBranches();
		System.out.println();
		Company.showBranchEmployees();
		System.out.println();
		Company.showTransportPersonnels();
		System.out.println();
		Company.showCustomers();
		System.out.println();
		Company.showShipments();
		System.out.println();
		
		System.out.println("\n\nDeleting the last element of all arrays...\n\n");
		
		Company.deleteBranch(3);
		Company.deleteEmployee(9);
		Company.deleteCustomer(7);
		Company.deleteShipment(5);
		
		if(Company.doesBranchExist(3))System.out.println("Failed to delete!");
		if(Company.doesEmployeeExist(9))System.out.println("Failed to delete!");
		if(Company.doesCustomerExist(7))System.out.println("Failed to delete!");
		if(Company.doesShipmentExist(5))System.out.println("Failed to delete!");
		
		Company.showBranches();
		System.out.println();
		Company.showBranchEmployees();
		System.out.println();
		Company.showTransportPersonnels();
		System.out.println();
		Company.showCustomers();
		System.out.println();
		Company.showShipments();
	}
}
