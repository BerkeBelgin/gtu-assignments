

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Customer Page UI class
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-02-25
 */
public class CustomerPage extends Page {
	final int customerId;
	
	public CustomerPage(int customerId) {
		super();
		this.customerId = customerId;
	}
	
	@Override
	public void build() {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		boolean retry;
		int choice;
		do {
			retry = true;
			choice = -1;
			
			super.clearScreen();
			for(Shipment shipment : Company.getShipments()) {
				if(shipment.getSender().getTrackingId() == customerId || shipment.getReciever().getTrackingId() == customerId) {
					System.out.println(shipment.toString());
				}
			}
			
			System.out.println("1) Back");
			System.out.print("Please choose the operation you would likte to do: ");
			try {
				choice = Integer.parseInt(reader.readLine());
				
				switch(choice) {
					case 1:
						retry = false;
						break;
				}
			} catch(IOException e) {
				e.printStackTrace();
			}
		} while(retry);
	}
}
