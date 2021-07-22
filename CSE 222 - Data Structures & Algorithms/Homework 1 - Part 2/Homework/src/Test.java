

/**
 * A class o test if everything works correctly
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-03-03
 */
public class Test {
	/**
	 * A method to call to test if whole program works correctly
	 */
	public static void test() {
		Admin admin = Company.getAdmin();
		System.out.println("Creating branches...");
		
		admin.insertBranch("Kadikoy");
		admin.insertBranch("Kartal");
		admin.insertBranch("Maltepe");
		
		System.out.println("Creating Employees...");
		
		try {
			admin.insertBranchEmployee("Lara", "Croft",1);
			admin.insertBranchEmployee("Captain", "Price",1);
			admin.insertBranchEmployee("Geralt", "Rivia",2);
			admin.insertBranchEmployee("Adolf", "Kinder",2);
			admin.insertBranchEmployee("Josef", "Stalin",3);
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
		
		admin.insertTransportPersonnel("Luke", "Skywalker");
		admin.insertTransportPersonnel("Obi Wan", "Kenobi");
		admin.insertTransportPersonnel("Dol", "Amaroth");
		admin.insertTransportPersonnel("Minas", "Tirith");
		admin.insertTransportPersonnel("Enes", "Batur");
		
		BranchEmployee laraCroft;
		try {
			laraCroft = Company.getBranchEmployee(1);
			System.out.println("Creating customers...");
			
			laraCroft.insertCustomer("Winston", "Churchill");
			laraCroft.insertCustomer("Benito", "Musollini");
			laraCroft.insertCustomer("Neil", "Armstrong");
			laraCroft.insertCustomer("Tony", "Stark");
			laraCroft.insertCustomer("Bruce", "Banner");
			laraCroft.insertCustomer("Howard", "Stark");
			laraCroft.insertCustomer("Kylo", "Ren");
			
			System.out.println("Creating shipments...\n\n");
			
			laraCroft.insertShipment(1, 3);
			laraCroft.insertShipment(5, 2);
			laraCroft.insertShipment(4, 1);
			laraCroft.insertShipment(2, 3);
			laraCroft.insertShipment(7, 5);
			laraCroft.insertShipment(1, 3);
		
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
			
			System.out.println("\n\nDeleting the last element of all lists...\n\n");
		
			admin.deleteBranch(3);
			admin.deleteBranchEmployee(5);
			admin.deleteTransportPersonnel(5);
			laraCroft.deleteCustomer(7);
			laraCroft.deleteShipment(5);
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
		
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
