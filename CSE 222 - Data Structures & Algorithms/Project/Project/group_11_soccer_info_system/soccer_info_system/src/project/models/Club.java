package project.models;

import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.concurrent.ConcurrentSkipListSet;

public class Club {
	private String name;
	private User president;
	private User coach;
	private ArrayList<Person> healthOfficers;
	private ArrayList<Player> players;
	private PriorityQueue<Player> playersByGoals;
	private ConcurrentSkipListSet<User> clubAdmins;
	
	public Club() {
		this.healthOfficers = new ArrayList<Person>();
		this.players = new ArrayList<Player>();
		this.playersByGoals = new PriorityQueue<Player>();
		this.clubAdmins=new ConcurrentSkipListSet<>();
	}
	
	public String getName() {
		return name;
	}
	public User getPresident() {
		return president;
	}
	public User getCoach() {
		return coach;
	}
	public Person getHealthOfficer(int index) {
		return healthOfficers.get(index);
	}
	public Player getPlayer(int index) {
		return players.get(index);
	}
	public Player getTopPlayer() {
		return playersByGoals.peek();
	}
	public int getPlayerAmount() {
		return players.size();
	}
	public ConcurrentSkipListSet<User> getClubAdmins() {
		return clubAdmins;
	}
	public void setPresident(User president) {
		this.president=president;
	}
	
	public void setCoach(User coach) {
		this.coach=coach;
	}
	
	public void addHealthOfficer(int role, Person person) {
		
	}
	public void addPlayer(int role, Player player) {
		
	}
	public void addClubAdmin(User newAdmin) {
		clubAdmins.add(newAdmin);
	}
	
	public void setHealthOfficer(int role, Person person, int id) {
		
	}
	public void setPlayer(int role, Player player, int id) {
		
	}
	public void setClubAdmin(int role, User admin, int id) {
		
	}
	
	public void removeHealthOfficer(int role, int id) {
		
	}
	public void removePlayer(int role, int id) {
		
	}
	public void removeClubAdmin(User clubAdmin) {
		clubAdmins.remove(clubAdmin);
	}
}
