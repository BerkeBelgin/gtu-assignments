

/**
 * Employee abstract model class to hold information of a Employee
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-02-25
 */
public abstract class Employee{
	/**
	 * id of the employee
	 */
	protected int id;
	/**
	 * First name of the employee
	 */
	protected String firstName;
	/**
	 * Last name of the employee
	 */
	protected String lastName;
	
	public Employee(String firstName, String lastName) {
		this.firstName = firstName;
		this.lastName = lastName;
	}
	public Employee() {
		
	}
	
	public int getId() {
		return id;
	}
	public String getFirstName() {
		return firstName;
	}
	public String getLastName() {
		return lastName;
	}
	
	public void setId(int id) {
		this.id = id;
	}
	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}
	public void setLastName(String lastName) {
		this.lastName = lastName;
	}
	
	@Override
	public String toString() {
		return String.format("%d %s %s", id, firstName, lastName);
	}
}
