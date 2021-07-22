package project.views;
import java.util.Map;
import java.util.Scanner;
import project.models.Federation;

public class ClubPage extends Page{
	Scanner scnnr;
	Federation federation;
	
	public ClubPage(Scanner scnnr, Federation federation) {
		this.scnnr = scnnr;
		this.federation=federation;
	}
	
	@Override
	public void buildPage() {
		super.buildPage();
		System.out.println("0 - Previous Page");
		for(int i=0;i<federation.getClubAmount();++i) {
			System.out.println((i+1)+" - "+federation.getClub(i).getName());
		}
		
		String in;
		int choice;
		do {
			System.out.println("Which team do you want to look for ?(Enter the number of the team.)");
			in = scnnr.nextLine();
			choice=(Integer.parseInt(in));
		} while(choice < 0 || choice >= federation.getClubAmount());
		
		if(choice == 0) {
			ChooseFederationPage cfp=new ChooseFederationPage(scnnr);
			cfp.buildPage();
		}
		TeamInfoPage teamInfo=new TeamInfoPage(scnnr, federation.getClub(choice-1),federation);
		teamInfo.buildPage();
		
	}
	
	
	
	
}
