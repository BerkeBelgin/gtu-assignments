package project.models;

import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;

import com.google.gson.Gson;

public class Football {
	public static String identity;
	public static ArrayList<Federation> federations = new ArrayList<Federation>();
	private static ArrayList<Club> clubs = new ArrayList<Club>();
	private static ArrayList<Season> seasons = new ArrayList<Season>();
	private static ArrayList<Player> players = new ArrayList<Player>();
	private static ArrayList<User> users = new ArrayList<User>();
	
	public static void addUser(String firstName, String lastName, String username, String password) {
		users.add(new User(firstName, lastName, username, password));
	}
	
	public static void giveSystemAdminRole(String username) {
		
	}
	public static void giveFederationAdminRole(String username) {
		
	}
	public static void changeFederationPresident(User user) {
		
	}
	public static void giveClubAdminRole(User user) {
		
	}
	public static void changeClubPresident(User user) {
		
	}
	public static void changeCoach(int id, User user) {
		
	}
	
	public static boolean userExists(String username,String password) {
		for(int i=0;i < users.size();i++) {
			if(users.get(i).getUsername().equals(username) && users.get(i).getPassword().equals(password))
				return true;
		}
		return false;
	}
	
	private static void readFederationsStateFromFile() {
		Gson gson = new Gson();
		try {
			byte[] encoded = Files.readAllBytes(Paths.get("../data/federations.json"));
			Federation[] federationsArray = gson.fromJson(new String(encoded, StandardCharsets.UTF_8), Federation[].class);
			federations = new ArrayList<Federation>(Arrays.asList(federationsArray));
		} catch (IOException e) {
			federations = new ArrayList<Federation>();
		}
	}
	private static void readClubsStateFromFile() {
		Gson gson = new Gson();
		try {
			byte[] encoded = Files.readAllBytes(Paths.get("../data/clubs.json"));
			Club[] clubsArray = gson.fromJson(new String(encoded, StandardCharsets.UTF_8), Club[].class);
			clubs = new ArrayList<Club>(Arrays.asList(clubsArray));
		} catch (IOException e) {
			clubs = new ArrayList<Club>();
		}
	}
	private static void readSeasonsStateFromFile() {
		Gson gson = new Gson();
		try {
			byte[] encoded = Files.readAllBytes(Paths.get("../data/seasons.json"));
			Season[] seasonsArray = gson.fromJson(new String(encoded, StandardCharsets.UTF_8), Season[].class);
			seasons = new ArrayList<Season>(Arrays.asList(seasonsArray));
		} catch (IOException e) {
			seasons = new ArrayList<Season>();
		}
	}
	private static void readPlayersStateFromFile() {
		Gson gson = new Gson();
		try {
			byte[] encoded = Files.readAllBytes(Paths.get("../data/players.json"));
			Player[] playersArray = gson.fromJson(new String(encoded, StandardCharsets.UTF_8), Player[].class);
			players = new ArrayList<Player>(Arrays.asList(playersArray));
		} catch (IOException e) {
			players = new ArrayList<Player>();
		}
	}
	private static void readUsersStateFromFile() {
		Gson gson = new Gson();
		try {
			byte[] encoded = Files.readAllBytes(Paths.get("../data/users.json"));
			User[] usersArray = gson.fromJson(new String(encoded, StandardCharsets.UTF_8), User[].class);
			users = new ArrayList<User>(Arrays.asList(usersArray));
		} catch (IOException e) {
			users = new ArrayList<User>();
		}
	}
	
	public static void readStateFromFile(){
		readFederationsStateFromFile();
		readClubsStateFromFile();
		readSeasonsStateFromFile();
		readPlayersStateFromFile();
		readUsersStateFromFile();
	}
	
	private static void saveFederationsStateToFile(){
		Gson gson = new Gson();
		try {
			FileWriter fw = new FileWriter("data/federations.json");
			fw.write(gson.toJson(federations));
			fw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	private static void saveClubsStateToFile(){
		Gson gson = new Gson();
		try {
			FileWriter fw = new FileWriter("data/clubs.json");
			fw.write(gson.toJson(clubs));
			fw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	private static void saveSeasonsStateToFile(){
		Gson gson = new Gson();
		try {
			FileWriter fw = new FileWriter("data/seasons.json");
			fw.write(gson.toJson(seasons));
			fw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	private static void savePlayersStateToFile(){
		Gson gson = new Gson();
		try {
			FileWriter fw = new FileWriter("data/players.json");
			fw.write(gson.toJson(players));
			fw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	private static void saveUsersStateToFile(){
		Gson gson = new Gson();
		try {
			FileWriter fw = new FileWriter("data/federations.json");
			fw.write(gson.toJson(users));
			fw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	public static void saveStateToFile(){
		saveFederationsStateToFile();
		saveClubsStateToFile();
		saveSeasonsStateToFile();
		savePlayersStateToFile();
		saveUsersStateToFile();
	}
}
