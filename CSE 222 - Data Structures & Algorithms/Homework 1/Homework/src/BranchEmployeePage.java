

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;


/**
 * Branch Employee Page UI class
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-02-25
 */
public class BranchEmployeePage extends Page {
	final int branchEmployeeId;
	
	public BranchEmployeePage(int branchEmployeeId) {
		super();
		this.branchEmployeeId = branchEmployeeId;
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
		
		do {
			retry = true;
			choice = -1;
			
			super.clearScreen();
			Company.showShipmentsByBranchId(((BranchEmployee) Company.getEmployee(branchEmployeeId)).getBranch().getId());
			System.out.println();
			Company.showCustomers();
			System.out.println();
			
			System.out.println(String.format("Branch: %s", ((BranchEmployee) Company.getEmployee(branchEmployeeId)).getBranch().getName()));
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
						Company.insertShipment(
								new Shipment(
										Company.getCustomer(sendingCustomerId),
										Company.getCustomer(recievingCustomerId),
										((BranchEmployee) Company.getEmployee(branchEmployeeId)).getBranch(),
										Shipment.GETTING_PREPARED
								)
						);
						break;
					case 2:
						System.out.print("Shipment Id: ");
						shipmentId = Integer.parseInt(reader.readLine());
						Company.deleteShipment(shipmentId);
						break;
					case 3:
						System.out.print("Shipment Id: ");
						shipmentId = Integer.parseInt(reader.readLine());
						Shipment.showShipmentStatus();
						System.out.print("Status Id: ");
						statusId = Integer.parseInt(reader.readLine());
						Company.getShipment(shipmentId).setStatus(statusId);
						break;
					case 4:
						System.out.print("First Name: ");
						firstName = reader.readLine();
						System.out.print("Last Name: ");
						lastName = reader.readLine();
						Company.insertCustomer(new Customer(firstName, lastName));
						break;
					case 5:
						System.out.print("Customer Id: ");
						customerId = Integer.parseInt(reader.readLine());
						Company.deleteCustomer(customerId);
						break;
					case 6:
						retry = false;
				}
			} catch(IOException e) {
				e.printStackTrace();
			}
		} while(retry);
	}
}
