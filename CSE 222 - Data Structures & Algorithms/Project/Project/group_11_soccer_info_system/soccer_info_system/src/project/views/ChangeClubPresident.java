package project.views;

import java.util.Scanner;

import project.models.Club;
import project.models.Person;
import project.models.User;

public class ChangeClubPresident extends Page {
	Club club;
	
	public ChangeClubPresident(Club club) {
		this.club=club;
	}
	
	public void buildPage() {
		super.buildPage();
		String name="";
		String surname="";
		String username="";
		String password="";
		Scanner sc=new Scanner(System.in);
		System.out.println("What is the name of the new president?");
		name=sc.nextLine();
		System.out.println("What is the surname of the new president?");
		surname=sc.nextLine();
		System.out.println("What is the username of the new president?");
		username=sc.nextLine();
		System.out.println("What is the password of the new president?");
		password=sc.nextLine();
		User newPresident=new User(name,surname,username,password);
		club.setPresident(newPresident);
		sc.close();
	}
	
}
