package project.models;

import java.util.ArrayList;
import java.util.Queue;
import java.util.concurrent.ConcurrentSkipListSet;

public class Federation {
	private String name;
	private Queue<Person> referees;
	private ArrayList<Club> clubs;
	private Person president;
	private ArrayList<Season> seasons;
	private ConcurrentSkipListSet<Person> federationAdmins;
	
	public String getName() {
		return name;
	}
	public Person getTopReferee() {
		return referees.peek();
	}
	public Club getClub(int index) {
		return clubs.get(index);
	}
	public int getClubAmount() {
		return clubs.size();
	}
	public Person getPresident() {
		return president;
	}
	public ArrayList<Season> getSeasons() {
		return seasons;
	}
	public void addReferee(Person person) {
		referees.add(person);
	}
	public boolean removeReferee(Person person){
		return referees.remove(person);
	}
	public void addClub(Club club) {
		clubs.add(club);
	}
	public boolean removeClub(Club club){
		return clubs.remove(club);
	}
	public void addFederationAdmin(Person person) {
		federationAdmins.add(person);
	}
	public boolean removeFederationAdmin(Person person){
		return federationAdmins.remove(person);
	}
	
	public void generateFixture() {
		
	}
}
