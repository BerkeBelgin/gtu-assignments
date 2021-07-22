package project.models;

import java.time.LocalDateTime;
import java.util.Set;

public class Match {
	private LocalDateTime matchDate;
	private boolean isPlayed;
	private Person referee;
	private Club home;
	private Club away;
	private int homeScore;
	private int awayScore;
	private Set<Player> homeTopEleven; //new HashSet<Player>();
	private Set<Player> homeSubstitutes;
	private Set<Player> awayTopEleven;
	private Set<Player> awaySubstitutes;
	
	
	public LocalDateTime getMatchDate() {
		return matchDate;
	}
	public boolean isPlayed() {
		return isPlayed;
	}
	public Person getReferee() {
		return referee;
	}
	public Club getHome() {
		return home;
	}
	public Club getAway() {
		return away;
	}
	public int getHomeScore() {
		return homeScore;
	}
	public int getAwayScore() {
		return awayScore;
	}
	public Set<Player> getHomeTopEleven() {
		return homeTopEleven;
	}
	public Set<Player> getHomeSubstitutes() {
		return homeSubstitutes;
	}
	public Set<Player> getAwayTopEleven() {
		return awayTopEleven;
	}
	public Set<Player> getAwaySubstitutes() {
		return awaySubstitutes;
	}
	
	public void setMatchDate(int userId, LocalDateTime matchDate) {
		this.matchDate = matchDate;
	}
	public void setPlayed(int userId, boolean isPlayed) {
		this.isPlayed = isPlayed;
	}
	public void setReferee(int userId, Person referee) {
		this.referee = referee;
	}
	public void setHome(int userId, Club home) {
		this.home = home;
	}
	public void setAway(int userId, Club away) {
		this.away = away;
	}
	public void setHomeScore(int userId, int homeScore) {
		this.homeScore = homeScore;
	}
	public void setAwayScore(int userId, int awayScore) {
		this.awayScore = awayScore;
	}
	public void setHomeTopEleven(int userId, Set<Player> homeTopEleven) {
		this.homeTopEleven = homeTopEleven;
	}
	public void setHomeSubstitutes(int userId, Set<Player> homeSubstitutes) {
		this.homeSubstitutes = homeSubstitutes;
	}
	public void setAwayTopEleven(int userId, Set<Player> awayTopEleven) {
		this.awayTopEleven = awayTopEleven;
	}
	public void setAwaySubstitutes(int userId, Set<Player> awaySubstitutes) {
		this.awaySubstitutes = awaySubstitutes;
	}
}
