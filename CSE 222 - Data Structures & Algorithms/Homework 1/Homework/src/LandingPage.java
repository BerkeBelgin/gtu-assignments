

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Landing Page UI class, the first page displayed when program executed
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-02-25
 */
public class LandingPage extends Page {
	
	@Override
	public void build() {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		boolean retry;
		boolean innerRetry;
		int choice;
		
		do {
			retry = true;
			choice = -1;
			
			super.clearScreen();
			System.out.println("Welcome to cargosoft\n");
			System.out.println("0) Admin");
			System.out.println("1) Customer");
			System.out.println("2) Employee");
			System.out.println("3) Exit");
			System.out.print("Please make a choice to proceed: ");
			try {
				choice = Integer.parseInt(reader.readLine());
				
				switch (choice) {
					case 0:
						AdminPage adminPage = new AdminPage();
						adminPage.build();
						break;
					case 1:
						do {
							innerRetry = false;
							
							this.clearScreen();
							System.out.print("Please enter your id: ");
							choice = Integer.parseInt(reader.readLine());
							
							if(Company.doesCustomerExist(choice)) {
								CustomerPage customerPage = new CustomerPage(choice);
								customerPage.build();
							} else {
								innerRetry = true;
							}
						} while(innerRetry);
						break;
					case 2:
						do {
							innerRetry = false;
							
							this.clearScreen();
							System.out.print("Please enter your id: ");
							choice = Integer.parseInt(reader.readLine());
							
							if(Company.doesEmployeeExist(choice)) {
								Employee employee = Company.getEmployee(choice);
								if(employee instanceof BranchEmployee) {
									BranchEmployeePage branchEmployeePage = new BranchEmployeePage(employee.getId());
									branchEmployeePage.build();
								} else if (employee instanceof TransportPersonnel){
									TransportPersonnelPage transportPersonnelPage = new TransportPersonnelPage(employee.getId());
									transportPersonnelPage.build();
								}
							} else {
								innerRetry = true;
							}
						} while(innerRetry);
						break;
					case 3:
						retry = false;
						break;
				}
			} catch(IOException e) {
				e.printStackTrace();
			}
		} while(retry);
	}
}
