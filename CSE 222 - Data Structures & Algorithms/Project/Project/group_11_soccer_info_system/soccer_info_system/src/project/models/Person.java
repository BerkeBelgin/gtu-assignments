package project.models;

public class Person {
	protected String firstName;
	protected String LastName;
	
	public Person(String firstName,String LastName) {
		this.firstName=firstName;
		this.LastName=LastName;
	}
	
	public Person() {
		this.firstName="";
		this.LastName="";
	}
	
	public String getFirstName() {
		return firstName;
	}
	
	public String getLastName() {
		return LastName;
	}
}
