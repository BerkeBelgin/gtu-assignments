

/**
 * Shipment class to hold information of a Shipment
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-03-03
 */
public class Shipment {
	public final static int GETTING_PREPARED = 0;
	public final static int ON_THE_WAY = 1;
	public final static int DELIVERED_TO_THE_CUSTOMER = 2;
	
	/**
	 * id of the shipment
	 */
	private int id;
	/**
	 * object of the customer who sends the cargo
	 */
	private Customer sender;
	/**
	 * object of the customer who recieves the cargo
	 */
	private Customer reciever;
	/**
	 * the branch of the company which is responsible from the delivery proccess
	 */
	private Branch branch;
	/**
	 * current status of the cargo
	 */
	private int status;
	
	public Shipment(int id, Customer sender, Customer reciever, Branch branch, int status) {
		this.id = id;
		this.sender = sender;
		this.reciever = reciever;
		this.branch = branch;
		this.status = status;
	}
	
	public int getId() {
		return id;
	}
	public Customer getSender() {
		return sender;
	}
	public Customer getReciever() {
		return reciever;
	}
	public Branch getBranch() {
		return branch;
	}
	public int getStatus() {
		return status;
	}
	
	public void setStatus(int status) {
		if(status >= 0 && status <= 2) this.status = status;
		else this.status = GETTING_PREPARED;
	}
	
	/**
	 * Method that shows all kind of Shipment Statuses a Shipment object can have
	 */
	public static void showShipmentStatus() {
		System.out.println("0) Getting Prepared");
		System.out.println("1) On The Way");
		System.out.println("2) Delivered To The Customer");
	}
	
	/**
	 * Method that converts status from int to String
	 * @return String returns text equivelant of status
	 */
	public String getStatusAsString(){
		switch(status) {
			case GETTING_PREPARED:
				return "Getting Prepared";
			case ON_THE_WAY:
				return "On The Way";
			case DELIVERED_TO_THE_CUSTOMER:
				return "Delivered To The Customer";
			default:
				return "";
		}
	}
	
	@Override
	public String toString() {
		return String.format("%d - %s %s -> %s %s - %s - %s", 
			id, 
			sender.getFirstName(), 
			sender.getLastName(),
			reciever.getFirstName(),
			reciever.getLastName(),
			branch.getName(),
			getStatusAsString()
		);
	}
}
