package project.views;

import java.util.Scanner;

import project.models.Club;
import project.models.User;

public class ChangeCoachPage extends Page{
	Club club;
	
	public ChangeCoachPage(Club club) {
		this.club=club;
	}
	
	public void buildPage() {
		super.buildPage();
		String name="";
		String surname="";
		String username="";
		String password="";
		Scanner sc=new Scanner(System.in);
		System.out.println("What is the name of the new coach?");
		name=sc.nextLine();
		System.out.println("What is the surname of the new coach?");
		surname=sc.nextLine();
		System.out.println("What is the username of the new coach?");
		username=sc.nextLine();
		System.out.println("What is the password of the new coach?");
		password=sc.nextLine();
		User newCoach=new User(name,surname,username,password);
		club.setCoach(newCoach);
		sc.close();
	}
	
}
