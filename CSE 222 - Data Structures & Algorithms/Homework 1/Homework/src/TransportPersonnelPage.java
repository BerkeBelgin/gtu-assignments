

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Transport Personnel Page UI class
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-02-25
 */
public class TransportPersonnelPage extends Page {
	final int transportPersonnelId;
	
	public TransportPersonnelPage(int transportPersonnelId) {
		super();
		this.transportPersonnelId = transportPersonnelId;
	}
	
	@Override
	public void build() {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		boolean retry;
		int choice;
		
		int shipmentId;
		
		do {
			retry = true;
			choice = -1;
			
			super.clearScreen();
			Company.showShipments();
			
			System.out.println("1) Update Shipment Status As Delivered");
			System.out.println("2) Back");
			System.out.print("Please choose the operation you would likte to do: ");
			try {
				choice = Integer.parseInt(reader.readLine());
				
				switch(choice) {
					case 1:
						System.out.print("Shipment Id: ");
						shipmentId = Integer.parseInt(reader.readLine());
						Company.getShipment(shipmentId).setStatus(Shipment.DELIVERED_TO_THE_CUSTOMER);
						break;
					case 2:
						retry = false;
						break;
				}
			} catch(IOException e) {
				e.printStackTrace();
			}
		} while(retry);
	}
}
