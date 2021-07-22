package project.views;

import java.util.Map;
import java.util.Scanner;

import project.models.Club;
import project.models.Federation;

public class PlayerListPage extends Page{
	Club club;
	Federation federation;
	
	public PlayerListPage(Club club,Federation federation) {
		this.club = club;
		this.federation=federation;
	}
	
	public void buildPage() {
		super.buildPage();
		
		int i=0;
		Scanner sc=new Scanner(System.in);
		String s=new String();
		int choice=0;
		
		do {
			
			for(i=0;i<club.getPlayerAmount();++i) {
				System.out.println((i+1)+" - "+ club.getPlayer(i));
			}
			System.out.println("Which player do you want to look ?");
			s=sc.nextLine();
			choice=Integer.parseInt(s);
			choice--;
			super.clearScreen();
		}while(choice < 0 || choice >= club.getPlayerAmount());
		
		PlayerInfoPage pp=new PlayerInfoPage(club.getPlayer(choice),club,federation);
		pp.buildPage();
	}
	

}
