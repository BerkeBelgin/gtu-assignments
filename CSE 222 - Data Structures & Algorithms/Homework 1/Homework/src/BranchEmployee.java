

/**
 * Branch Employee model class to hold information of a Branch Employee which is extended from Employee abstract class
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-02-25
 */
public class BranchEmployee extends Employee {
	/**
	 * Company branch that this employee is tied to
	 */
	final Branch branch;
	
	public BranchEmployee(Branch branch) {
		super();
		this.branch = branch;
	}
	public BranchEmployee(Branch branch, String firstName, String lastName) {
		super(firstName, lastName);
		this.branch = branch;
	}
	
	public Branch getBranch() {
		return branch;
	}
	
	@Override
	public String toString() {
		return String.format("%d %s %s %s", id, firstName, lastName, branch.getName());
	}
}
