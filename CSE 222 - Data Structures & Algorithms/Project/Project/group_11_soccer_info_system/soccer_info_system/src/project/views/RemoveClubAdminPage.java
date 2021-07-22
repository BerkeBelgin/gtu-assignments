package project.views;

import java.util.Scanner;

import project.models.Club;
import project.models.User;

public class RemoveClubAdminPage extends Page{
	Club club;
	
	public RemoveClubAdminPage(Club club) {
		this.club=club;
	}
	
	public void buildPage() {
		super.buildPage();
		String name="";
		String surname="";
		String username="";
		String password="";
		Scanner sc=new Scanner(System.in);
		System.out.println("What is the name of the club admin that is going to be deleted?");
		name=sc.nextLine();
		System.out.println("What is the surname of the club admin that is going to be deleted?");
		surname=sc.nextLine();
		System.out.println("What is the username of the club admin that is going to be deleted?");
		username=sc.nextLine();
		System.out.println("What is the password of the club admin that is going to be deleted?");
		password=sc.nextLine();
		User clubAdmin=new User(name,surname,username,password);
		club.removeClubAdmin(clubAdmin);
		sc.close();
	}
	
}
