package project.models;

public class Player extends Person implements Comparable<Player> {
	private int priority;
	private int age;
	private int height;
	private int weight;
	private boolean isInjured;
	private int goals;
	private int assists;
	
	public int compareTo(Player player) {
		return 0;
	}

	public int getPriority() {
		return priority;
	}
	public int getAge() {
		return age;
	}
	public int getHeight() {
		return height;
	}
	public int getWeight() {
		return weight;
	}
	public boolean isInjured() {
		return isInjured;
	}
	public int getGoals() {
		return goals;
	}
	public int getAssists() {
		return assists;
	}

	public void setPriority(int role, int priority) {
		this.priority = priority;
	}
	public void setAge(int age) {
		this.age = age;
	}
	public void setHeight(int height) {
		this.height = height;
	}
	public void setWeight(int weight) {
		this.weight = weight;
	}
	public void setInjured(boolean isInjured) {
		this.isInjured = isInjured;
	}
	public void setGoals(int goals) {
		this.goals = goals;
	}
	public void setAssists(int assists) {
		this.assists = assists;
	}
	
	
}
