package project.views;

import project.models.Club;
import project.models.Federation;
import project.models.Season;
import project.models.Week;
import project.models.Match;

import java.util.ArrayList;
import java.util.Map;
import java.util.Scanner;


public class FixturePage extends Page{
	Scanner scnnr;
	ArrayList<Season> seasons;
	Club club;
	Federation federation;
	
	public FixturePage(Scanner scnnr, ArrayList<Season> seasons,Club club,Federation federation) {
		this.scnnr = scnnr;
		this.seasons=seasons;
		this.club=club;
		this.federation=federation;
	}
	
	
	@SuppressWarnings("resource")
	public void buildPage() {
		super.buildPage();
		String s=new String();
		int i=0,choice=0;
		
		System.out.println("Which season do you want to look for ?");
		s=scnnr.nextLine();
		for(i=0;i < seasons.size();++i) {
			if(seasons.get(i).getName().equals(s)) {
				break;
			}
		}
		if(i >= seasons.size()) {
			System.out.println("Season not found.");
			do {
				System.out.println("1 - Search Again");
				System.out.println("2 - Previous Page");
				s=scnnr.nextLine();
				choice=Integer.parseInt(s);
				choice--;
				super.clearScreen();
			}while(choice < 0 || choice >= 2);
			if(choice == 0) {
				FixturePage fp=new FixturePage(scnnr, seasons,club,federation);
				fp.buildPage();
			}
			else {
				TeamInfoPage tp=new TeamInfoPage(scnnr, club,federation);
				tp.buildPage();
			}
		}
		else {
			Season targetSeason=seasons.get(i);
			System.out.println("Which week do you want to look for ?");
			s=scnnr.nextLine();
			choice=Integer.parseInt(s);
			choice--;
			if(choice < 0 || choice >= targetSeason.getWeeks().size()) {
				System.out.println("No week found.");
				do {
					System.out.println("1 - Search Again");
					System.out.println("2 - Previous Page");
					s=scnnr.nextLine();
					choice=Integer.parseInt(s);
					choice--;
					super.clearScreen();
				}while(choice < 0 || choice >= 2);
				if(choice == 0) {
					FixturePage fp=new FixturePage(scnnr, seasons,club,federation);
					fp.buildPage();
				}
				else {
					TeamInfoPage tp=new TeamInfoPage(scnnr, club,federation);
					tp.buildPage();
				}
			}
			else {
				Week targetWeek=targetSeason.getWeeks().get(choice);
				targetWeek.getMatches();
				for(int j=0;j<targetWeek.getMatches().size();++i) {
					Match temp=targetWeek.getMatches().get(j);
					if(temp.isPlayed()) {
						System.out.println(temp.getHome().getName()+" "+temp.getHomeScore()+"- "
										+ temp.getAwayScore() + temp.getAway().getName());
					}
				}
				System.out.println("Press any button to go previous page.");
				s=scnnr.nextLine();
				TeamInfoPage tp=new TeamInfoPage(scnnr, club,federation);
				tp.buildPage();
			}
		}
		
	}
	
}
