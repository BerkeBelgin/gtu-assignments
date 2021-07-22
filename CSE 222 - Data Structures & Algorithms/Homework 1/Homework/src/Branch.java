

/**
 * Branch model class to hold information of a Branch
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-02-25
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
	
	public Branch(String name) {
		super();
		this.name = name;
	}
	public Branch() {
		super();
	}
	
	public int getId() {
		return id;
	}
	public String getName() {
		return name;
	}
	
	public void setId(int id) {
		this.id = id;
	}
	public void setName(String name) {
		this.name = name;
	}
	
	@Override
	public String toString() {
		return String.format("%d %s", id, name);
	}
}
