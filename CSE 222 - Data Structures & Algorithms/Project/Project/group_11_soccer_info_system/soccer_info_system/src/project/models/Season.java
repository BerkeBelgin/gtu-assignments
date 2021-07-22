package project.models;

import java.util.ArrayList;

import project.binarySearchTree.BinarySearchTree;

public class Season {
	private String name;
	private BinarySearchTree<Player> players;//Balanced Binary Search Tree
	private ArrayList<Week> weeks;
	
	public String getName() {
		return name;
	}
	public BinarySearchTree<Player> getPlayers() {
		return players;
	}
	public ArrayList<Week> getWeeks() {
		return weeks;
	}
	
	public void setName(String name, int userId) {
		this.name = name;
	}
	public void setPlayers(BinarySearchTree<Player> players, int userId) {
		this.players = players;
	}
	public void setWeeks(ArrayList<Week> weeks, int userId) {
		this.weeks = weeks;
	}
	
	
}
