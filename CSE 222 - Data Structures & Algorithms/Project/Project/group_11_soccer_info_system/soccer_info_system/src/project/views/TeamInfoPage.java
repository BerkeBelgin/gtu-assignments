package project.views;


import java.util.Scanner;

import project.models.Club;
import project.models.Federation;
import project.models.Football;

public class TeamInfoPage extends Page{
	Scanner scnnr;
	Club club;
	Federation federation;
	
	public TeamInfoPage(Scanner scnnr, Club club,Federation federation) {
		this.scnnr = scnnr;
		this.club=club;
		this.federation=federation;
	}
	
	@Override
	public void buildPage() {
		super.buildPage();
		System.out.println(club.getName()+"'s Informations");
		String s=new String();
		int choice=0;
		if(Football.identity.equals(club.getPresident().getUsername())) {
			do {
				System.out.println("1 - Players");
				System.out.println("2 - Fixture");
				System.out.println("3 - Add club admin");
				System.out.println("4 - Remove club admin");
				System.out.println("5 - Change club president");
				System.out.println("6 - Change coach");
				System.out.println("7 - Previous Page");
				s=scnnr.nextLine();
				choice=Integer.parseInt(s);
				choice--;
				super.clearScreen();
			}while(choice < 0 || choice > 6);
			if(choice == 0) {
				PlayerListPage page=new PlayerListPage(club,federation);
				page.buildPage();
			}
			else if(choice == 1) {
				FixturePage fp=new FixturePage(scnnr, federation.getSeasons(),club,federation);
				fp.buildPage();
			}
			else if(choice == 2) {
				AddClubAdminPage ap=new AddClubAdminPage(club);
				ap.buildPage();
			}
			else if(choice == 3) { // remove club admin
				RemoveClubAdminPage rcap=new RemoveClubAdminPage(club);
				rcap.buildPage();
			}
			else if(choice == 4) {
				ChangeClubPresident ccp= new ChangeClubPresident(club);
				ccp.buildPage();
			}
			else if(choice == 5) { // change coach
				ChangeCoachPage ccp=new ChangeCoachPage(club);
				ccp.buildPage();
			}
			else if(choice == 6) {
				ClubPage cp=new ClubPage(scnnr, federation);
				cp.buildPage();
			}
			else  {
				ClubPage cp=new ClubPage(scnnr, federation);
				cp.buildPage();
			}
		}
		
		else if(Football.identity.equals(club.getCoach().getUsername())) {
			do {
				System.out.println("1 - Players");
				System.out.println("2 - Fixture");
				System.out.println("3 - Choose Top Eleven and Substitute");
				System.out.println("4 - Previous Page");
				s=scnnr.nextLine();
				choice=Integer.parseInt(s);
				choice--;
				super.clearScreen();
			}while(choice < 0 || choice > 3);
			if(choice == 0) {
				PlayerListPage page=new PlayerListPage(club,federation);
				page.buildPage();
			}
			else if(choice == 1) {
				FixturePage fp=new FixturePage(scnnr, federation.getSeasons(),club,federation);
				fp.buildPage();
			}
			else if(choice == 2) {
				ClubPage cp=new ClubPage(scnnr, federation);
				cp.buildPage();
			}
			else if(choice == 3) {
				ClubPage cp=new ClubPage(scnnr, federation);
				cp.buildPage();
			}
			else {
				ClubPage cp=new ClubPage(scnnr, federation);
				cp.buildPage();
			}
		}
		
		else { // it is guest or not qualfied
			do {
				System.out.println("1 - Players");
				System.out.println("2 - Fixture");
				System.out.println("3 - Previous Page");
				s=scnnr.nextLine();
				choice=Integer.parseInt(s);
				choice--;
				super.clearScreen();
			}while(choice < 0 || choice > 2);
		}
		if(choice == 0) {
			PlayerListPage page=new PlayerListPage(club,federation);
			page.buildPage();
		}
		else if(choice == 1) {
			FixturePage fp=new FixturePage(scnnr, federation.getSeasons(),club,federation);
			fp.buildPage();
		}
		else if(choice == 2) {
			ClubPage cp=new ClubPage(scnnr, federation);
			cp.buildPage();
		}
		else {
			ClubPage cp=new ClubPage(scnnr, federation);
			cp.buildPage();
		}
	}
	
}
