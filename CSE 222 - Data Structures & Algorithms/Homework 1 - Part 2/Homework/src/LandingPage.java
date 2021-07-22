

import java.io.BufferedReader;
import java.io.InputStreamReader;

/**
 * Landing Page UI class, the first page displayed when program executed
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-03-03
 */
public class LandingPage extends Page {
	
	@Override
	public void build() {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		boolean retry;
		int choice;
		int id;
		
		super.clearScreen();
		do {
			retry = true;
			choice = -1;
			
			System.out.println();
			System.out.println("Welcome to cargosoft\n");
			System.out.println("0) Admin");
			System.out.println("1) Customer");
			System.out.println("2) Branch Employee");
			System.out.println("3) Transport Personnel");
			System.out.println("4) Exit");
			System.out.print("Please make a choice to proceed: ");
			try {
				choice = Integer.parseInt(reader.readLine());
				
				switch (choice) {
					case 0:
						AdminPage adminPage = new AdminPage(Company.getAdmin());
						adminPage.build();
						break;
					case 1:
						System.out.print("Please enter your id: ");
						id = Integer.parseInt(reader.readLine());
						CustomerPage customerPage = new CustomerPage(Company.getCustomer(id));
						customerPage.build();
						break;
					case 2:
						System.out.print("Please enter your id: ");
						id = Integer.parseInt(reader.readLine());
						BranchEmployeePage branchEmployeePage = new BranchEmployeePage(Company.getBranchEmployee(id));
						branchEmployeePage.build();
						break;
					case 3:
						System.out.print("Please enter your id: ");
						id = Integer.parseInt(reader.readLine());
						TransportPersonnelPage transportPersonnelPage = new TransportPersonnelPage(Company.getTransportPersonnel(id));
						transportPersonnelPage.build();
						break;
					case 4:
						retry = false;
						break;
				}
			} catch(Exception e) {
				System.out.println(e.getMessage());
			}
		} while(retry);
	}
}
