

import java.io.BufferedReader;
import java.io.InputStreamReader;

/**
 * Transport Personnel Page UI class
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-03-03
 */
public class TransportPersonnelPage extends Page {
	final TransportPersonnel transportPersonnel;
	
	public TransportPersonnelPage(TransportPersonnel transportPersonnel) {
		super();
		this.transportPersonnel = transportPersonnel;
	}
	
	@Override
	public void build() {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		boolean retry;
		int choice;
		
		int shipmentId;
		
		super.clearScreen();
		do {
			retry = true;
			choice = -1;
			
			System.out.println();
			Company.showShipments();
			System.out.println();
			
			System.out.println("1) Update Shipment Status As Delivered");
			System.out.println("2) Back");
			System.out.print("Please choose the operation you would likte to do: ");
			try {
				choice = Integer.parseInt(reader.readLine());
				
				switch(choice) {
					case 1:
						System.out.print("Shipment Id: ");
						shipmentId = Integer.parseInt(reader.readLine());
						transportPersonnel.updateShipmentStatus(shipmentId, Shipment.DELIVERED_TO_THE_CUSTOMER);
						break;
					case 2:
						retry = false;
						break;
				}
			} catch(Exception e) {
				System.out.println(e.getMessage());
			}
		} while(retry);
	}
}
