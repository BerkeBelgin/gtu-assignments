

import java.io.BufferedReader;
import java.io.InputStreamReader;

/**
 * Admin Page UI class
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-03-03
 */
public class AdminPage extends Page {
	final private Admin admin;
	
	AdminPage(Admin admin){
		this.admin = admin;
	}
	
	@Override
	public void build() {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		boolean retry;
		int choice;
		
		int id = -1;
		String firstName = "";
		String lastName = "";
		String name = "";
		int branchId;
		
		super.clearScreen();
		do {
			retry = true;
			choice = -1;
			
			System.out.println();
			Company.showBranchEmployees();
			System.out.println();
			Company.showTransportPersonnels();
			System.out.println();
			Company.showBranches();
			System.out.println();
			
			System.out.println("1) Insert Branch Employee");
			System.out.println("2) Delete Branch Employee");
			System.out.println("3) Insert Transport Personnel");
			System.out.println("4) Delete Transport Personnel");
			System.out.println("5) Insert Branch");
			System.out.println("6) Delete Branch");
			System.out.println("7) Back");
			System.out.print("Please choose the operation you would likte to do: ");
			
			try {
				choice = Integer.parseInt(reader.readLine());
				
				switch(choice) {
					case 1:
						System.out.print("First Name: ");
						firstName = reader.readLine();
						System.out.print("Last Name: ");
						lastName = reader.readLine();
						System.out.print("Branch Id: ");
						branchId = Integer.parseInt(reader.readLine());
						admin.insertBranchEmployee(firstName, lastName, branchId);
						break;
					case 2:
						System.out.print("Branch Employee Id: ");
						id = Integer.parseInt(reader.readLine());
						admin.deleteBranchEmployee(id);
						break;
					case 3:
						System.out.print("First Name: ");
						firstName = reader.readLine();
						System.out.print("Last Name: ");
						lastName = reader.readLine();
						admin.insertTransportPersonnel(firstName, lastName);
						break;
					case 4:
						System.out.print("Transport Personnel Id: ");
						id = Integer.parseInt(reader.readLine());
						admin.deleteTransportPersonnel(id);
						break;
					case 5:
						System.out.print("Name: ");
						name = reader.readLine();
						admin.insertBranch(name);
						break;
					case 6:
						System.out.print("Branch Id: ");
						id = Integer.parseInt(reader.readLine());
						admin.deleteBranch(id);
						break;
					case 7:
						retry = false;
						break;
				}
			} catch (Exception e) {
				System.out.println(e.getMessage());
			}
		} while(retry);
	}
}
