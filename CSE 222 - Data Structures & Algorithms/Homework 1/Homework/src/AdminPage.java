

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Admin Page UI class
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-02-25
 */
public class AdminPage extends Page {

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
		
		do {
			retry = true;
			choice = -1;
			
			super.clearScreen();
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
						if(!Company.doesBranchExist(branchId))continue;
						Company.insertEmployee(new BranchEmployee(Company.getBranch(branchId), firstName, lastName));
						break;
					case 2:
						System.out.print("Branch Employee Id: ");
						id = Integer.parseInt(reader.readLine());
						if(Company.getEmployee(id) instanceof BranchEmployee) Company.deleteEmployee(id);
						break;
					case 3:
						System.out.print("First Name: ");
						firstName = reader.readLine();
						System.out.print("Last Name: ");
						lastName = reader.readLine();
						Company.insertEmployee(new TransportPersonnel(firstName, lastName));
						break;
					case 4:
						System.out.print("Transport Personnel Id: ");
						id = Integer.parseInt(reader.readLine());
						if(Company.getEmployee(id) instanceof TransportPersonnel) Company.deleteEmployee(id);
						break;
					case 5:
						System.out.print("Name: ");
						name = reader.readLine();
						Company.insertBranch(new Branch(name));
						break;
					case 6:
						System.out.print("Branch Id: ");
						id = Integer.parseInt(reader.readLine());
						Company.deleteBranch(id);
						break;
					case 7:
						retry = false;
						break;
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		} while(retry);
	}
}
