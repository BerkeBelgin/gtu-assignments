

/**
 * Transport Personnel class to hold information of a Transport Personnel and handle transport personnel operations
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-03-03
 */
public class TransportPersonnel extends Company implements Employee{
	/**
	 * id of the employee
	 */
	private int id;
	/**
	 * First name of the employee
	 */
	private String firstName;
	/**
	 * Last name of the employee
	 */
	private String lastName;
	
	public TransportPersonnel(int id, String firstName, String lastName) {
		this.id = id;
		this.firstName = firstName;
		this.lastName = lastName;
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
	
	public void updateShipmentStatus(int id, int status) throws Exception {
		shipments.get(getShipmentIndexById(id)).setStatus(status);
	}
	
	@Override
	public String toString() {
		return String.format("%d %s %s", id, firstName, lastName);
	}
}
