

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Customer Page UI class
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-03-03
 */
public class CustomerPage extends Page {
	final Customer customer;
	
	public CustomerPage(Customer customer) {
		super();
		this.customer = customer;
	}
	
	@Override
	public void build() {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		boolean retry;
		int choice;
		
		super.clearScreen();
		do {
			retry = true;
			choice = -1;
			
			System.out.println();
			customer.showCargos();
			System.out.println();
			
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
				System.out.println(e.getMessage());
			}
		} while(retry);
	}
}
