package project.models;

import java.util.ArrayList;

public class Week {
	private ArrayList<Match> matches;

	public ArrayList<Match> getMatches() {
		return matches;
	}
	public void setMatches(ArrayList<Match> matches, int userId) {
		this.matches = matches;
	}
}
