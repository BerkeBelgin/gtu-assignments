package project.views;

import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;

import project.models.Club;
import project.models.Federation;
import project.models.Football;
import project.models.Player;
import project.models.User;


public class PlayerInfoPage extends Page{
	Player player;
	Club club;
	Federation federation;
	
	public PlayerInfoPage(Player player,Club club,Federation federation) {
		this.player = player;
		this.club=club;
		this.federation=federation;
	}
	
	
	public void buildPage() {
		super.buildPage();
		
		
		Scanner sc=new Scanner(System.in);
		String s=new String();
		int choice=0,choice2=0;
		Iterator<User> itr=club.getClubAdmins().iterator();
		String role="";
		
		while(itr.hasNext()) {
			User temp=itr.next();
			if(temp.getUsername().equals(Football.identity))
				role=new String("clubAdmin");
		}
		
		if(Football.identity.equals(role)) {
			do {
				super.clearScreen();
				System.out.println("Name : "+player.getFirstName());
				System.out.println("Surname : "+player.getLastName());
				System.out.println("Age : "+player.getAge());
				System.out.println("Weight : "+player.getWeight());
				System.out.println("Height : "+player.getHeight());
				System.out.println("Goals : "+player.getGoals());
				System.out.println("Assists : "+player.getAssists());
				System.out.print("Injury : ");
				if(player.isInjured()) System.out.print("Injured\n");
				else System.out.print("Not Injured\n");
				
				System.out.println("1 - Update player info's");
				System.out.println("2 - Previous page");
				s=sc.nextLine();
				choice=Integer.parseInt(s);
				choice--;
			}while(choice < 0 || choice >= 2);
			if(choice == 1) {
				do {
					super.clearScreen();
					System.out.println("What do you want to update?");
					System.out.println("1 - Weight");
					System.out.println("2 - Height");
					System.out.println("3 - Goals");
					System.out.println("4 - Assists");
					System.out.println("5 - Injury");
					System.out.println("6 - Back");
					s=sc.nextLine();
					choice2=Integer.parseInt(s);
					choice2--;
				}while(choice2 < 0  || choice2 >= 6);
				if(choice2 == 0) {
					int newvalue=0;
					System.out.println("What is the new weight?");
					newvalue=sc.nextInt();
					player.setWeight(newvalue);
				}
				else if(choice2 == 1) {
					int newvalue=0;
					System.out.println("What is the new height?");
					newvalue=sc.nextInt();
					player.setHeight(newvalue);
				}
				else if(choice2 == 2) {
					int newvalue=0;
					System.out.println("What is the new goal amount?");
					newvalue=sc.nextInt();
					player.setGoals(newvalue);
				}
				else if(choice2 == 3) {
					int newvalue=0;
					System.out.println("What is the new assist amount?");
					newvalue=sc.nextInt();
					player.setAssists(newvalue);
				}
				else if(choice2 == 4) {
					String str="";
					System.out.println("What is the new healt situation?('h' for healty,i for injured)");
					str=sc.nextLine();
					if(str.equalsIgnoreCase("h"))
						player.setInjured(false);
					else
						player.setInjured(true);
				}
				else if(choice2 == 5) {
					PlayerInfoPage temp=new PlayerInfoPage(player,club,federation);
					temp.buildPage();
				}
			}
			else { // previous page
				PlayerListPage temp=new PlayerListPage(club,federation);
				temp.buildPage();
			}
		}
		else {
			do {
				System.out.println("Name : "+player.getFirstName());
				System.out.println("Surname : "+player.getLastName());
				System.out.println("Age : "+player.getAge());
				System.out.println("Weight : "+player.getWeight());
				System.out.println("Height : "+player.getHeight());
				System.out.println("Goals : "+player.getGoals());
				System.out.println("Assists : "+player.getAssists());
				
				System.out.println("1 - Previous page");
				s=sc.nextLine();
				choice=Integer.parseInt(s);
				choice--;
				super.clearScreen();
			}while(choice != 0);
			PlayerListPage temp=new PlayerListPage(club,federation);
			sc.close();
			temp.buildPage();
		}
	}
	
}
