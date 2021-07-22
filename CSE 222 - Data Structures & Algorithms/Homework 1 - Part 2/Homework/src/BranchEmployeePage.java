

import java.io.BufferedReader;
import java.io.InputStreamReader;

/**
 * Branch Employee Page UI class
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-03-03
 */
public class BranchEmployeePage extends Page {
	final BranchEmployee branchEmployee;
	
	public BranchEmployeePage(BranchEmployee branchEmployee) {
		super();
		this.branchEmployee = branchEmployee;
	}
	
	@Override
	public void build() {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		boolean retry;
		int choice;
		
		int sendingCustomerId;
		int recievingCustomerId;
		int shipmentId;
		int customerId;
		int statusId;
		String firstName = "";
		String lastName = "";
		
		super.clearScreen();
		do {
			retry = true;
			choice = -1;
			
			System.out.println();
			Company.showShipmentsByBranchId(branchEmployee.getBranch().getId());
			System.out.println();
			Company.showCustomers();
			System.out.println();
			
			System.out.println(String.format("Current Branch: %s", branchEmployee.getBranch().getName()));
			System.out.println("1) Insert Shipment");
			System.out.println("2) Delete Shipment");
			System.out.println("3) Update Shipment Status");
			System.out.println("4) Insert Customer");
			System.out.println("5) Delete Customer");
			System.out.println("6) Back");
			System.out.print("Please choose the operation you would likte to do: ");
			try {
				choice = Integer.parseInt(reader.readLine());
				
				switch(choice) {
					case 1:
						System.out.print("Sending Customer Id: ");
						sendingCustomerId = Integer.parseInt(reader.readLine());
						System.out.print("Recieving Customer Id: ");
						recievingCustomerId = Integer.parseInt(reader.readLine());
						branchEmployee.insertShipment(sendingCustomerId, recievingCustomerId);
						break;
					case 2:
						System.out.print("Shipment Id: ");
						shipmentId = Integer.parseInt(reader.readLine());
						branchEmployee.deleteShipment(shipmentId);
						break;
					case 3:
						System.out.print("Shipment Id: ");
						shipmentId = Integer.parseInt(reader.readLine());
						Shipment.showShipmentStatus();
						System.out.print("Status Id: ");
						statusId = Integer.parseInt(reader.readLine());
						branchEmployee.updateShipmentStatus(shipmentId, statusId);
						break;
					case 4:
						System.out.print("First Name: ");
						firstName = reader.readLine();
						System.out.print("Last Name: ");
						lastName = reader.readLine();
						branchEmployee.insertCustomer(firstName, lastName);
						break;
					case 5:
						System.out.print("Customer Id: ");
						customerId = Integer.parseInt(reader.readLine());
						branchEmployee.deleteCustomer(customerId);
						break;
					case 6:
						retry = false;
				}
			} catch(Exception e) {
				System.out.println(e.getMessage());
			}
		} while(retry);
	}
}
