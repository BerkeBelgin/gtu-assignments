

/**
 * Customer model class to hold information of a Customer
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-02-25
 */
public class Customer{
	/**
	 * Tracking id for customer to track his/her cargo. Also works as customer id
	 */
	private int trackingId;
	/**
	 * First name of the customer
	 */
	private String firstName;
	/**
	 * Last name of the customer
	 */
	private String lastName;
	
	public Customer(String firstName, String lastName) {
		super();
		this.firstName = firstName;
		this.lastName = lastName;
	}
	
	public int getTrackingId() {
		return trackingId;
	}
	public String getFirstName() {
		return firstName;
	}
	public String getLastName() {
		return lastName;
	}
	
	public void setTrackingId(int trackingId) {
		this.trackingId = trackingId;
	}
	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}
	public void setLastName(String lastName) {
		this.lastName = lastName;
	}
	
	@Override
	public String toString() {
		return String.format("%d %s %s", trackingId, firstName, lastName);
	}
}
