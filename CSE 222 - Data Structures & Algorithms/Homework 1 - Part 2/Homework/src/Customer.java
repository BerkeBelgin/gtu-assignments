

/**
 * Customer class to hold information of a Customer
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-03-03
 */
public class Customer extends Company{
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
	
	public Customer(int id, String firstName, String lastName) {
		this.trackingId = id;
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
	
	@Override
	public String toString() {
		return String.format("%d %s %s", trackingId, firstName, lastName);
	}
	
	public void showCargos() {
		for(Shipment shipment : shipments) {
			if(shipment.getSender().getTrackingId() == trackingId || shipment.getReciever().getTrackingId() == trackingId) {
				System.out.println(shipment.toString());
			}
		}
	}
}
