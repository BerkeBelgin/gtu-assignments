package project.views;

import java.util.Scanner;

import project.models.Club;
import project.models.User;

public class AddClubAdminPage extends Page{
	Club club;

	public AddClubAdminPage(Club club) {
		super();
		this.club = club;
	}
	
	public void buildPage() {
		super.buildPage();
		String name="";
		String surname="";
		String username="";
		String password="";
		Scanner sc=new Scanner(System.in);
		System.out.println("What is the name of the new club admin?");
		name=sc.nextLine();
		System.out.println("What is the surname of the new club admin?");
		surname=sc.nextLine();
		System.out.println("What is the username of the new club admin?");
		username=sc.nextLine();
		System.out.println("What is the password of the new club admin?");
		password=sc.nextLine();
		User newClubAdmin=new User(name,surname,username,password);
		club.addClubAdmin(newClubAdmin);
		sc.close();
		
		
	}
}
