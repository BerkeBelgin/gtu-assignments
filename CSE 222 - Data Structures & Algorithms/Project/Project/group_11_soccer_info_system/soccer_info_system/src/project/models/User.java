package project.models;

public class User extends Person{
	private String username;
	private String password;
	
	public User(String firstName,String LastName,String username,String password) {
		this.firstName=firstName;
		this.LastName=LastName;
		this.username=username;
		this.password=password;
	}
	
	public String getUsername() {
		return username;
	}
	public String getPassword() {
		return password;
	}
	
	public void setUsername(String username, int userId) {
		this.username = username;
	}
	public void setPassword(String password, int userId) {
		this.password = password;
	}
	
	
}
