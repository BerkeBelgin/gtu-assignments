

/**
 * A Branch class to hold and transfer branch informations
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-03-03
 */
public class Branch {
	/**
	 * Id of the branch
	 */
	private int id;
	/**
	 * Name of the branch
	 */
	private String name;
	
	public Branch(int id, String name) {
		this.id = id;
		this.name = name;
	}
	
	public int getId() {
		return id;
	}
	public String getName() {
		return name;
	}
	
	@Override
	public String toString() {
		return String.format("%d %s", id, name);
	}
}
