

/**
 * Admin class to be initialized and used to handle the admin operations such as inserting/deleting employees, branches etc. from the company
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-03-03
 */
public class Admin extends Company{
	/**
	 * Method that inserts branchEmployee at the end of the branchEmployees arrayList
	 * @param firstName first name of the branch employee
	 * @param lastName last name of the branch employee
	 * @param branchId id of the branch employee
	 * @throws Exception if there is no branch with branch id throws exception
	 */
	public void insertBranchEmployee(String firstName, String lastName, int branchId) throws Exception {
		int id = branchEmployees.size() > 0 ? branchEmployees.get(branchEmployees.size() - 1).getId() + 1 : 1;
		Branch branch = branches.get(getBranchIndexById(branchId));
		branchEmployees.add(new BranchEmployee(id, firstName, lastName, branch));
	}
	/**
	 * Method that inserts transportPersonnel at the end of the transportPersonnels arrayList
	 * @param firstName first name of the transport personnel
	 * @param lastName last name of the transport personnel
	 */
	public void insertTransportPersonnel(String firstName, String lastName) {
		int id = transportPersonnels.size() > 0 ? transportPersonnels.get(transportPersonnels.size() - 1).getId() + 1 : 1;
		transportPersonnels.add(new TransportPersonnel(id, firstName, lastName));
	}
	/**
	 * Method that inserts branch at the end of the branches arrayList
	 * @param name name of branch
	 */
	public void insertBranch(String name) {
		int id = branches.size() > 0 ? branches.get(branches.size() - 1).getId() + 1 : 1;
		branches.add(new Branch(id, name));
	}
	
	/**
	 * Method that deletes the employee with the given id
	 * @param id id of the branch employee
	 * @throws Exception if branch employee does not exist, throws exception
	 */
	public void deleteBranchEmployee(int id) throws Exception {
		branchEmployees.remove(getBranchEmployeeIndexById(id));
	}
	/**
	 * Method that deletes the employee with the given id
	 * @param id id of the transport personnel
	 * @throws Exception  if transport personnel does not exist, throws exception
	 */
	public void deleteTransportPersonnel(int id) throws Exception {
		transportPersonnels.remove(getTransportPersonnelIndexById(id));
	}
	/**
	 * Method that deletes the branch with the given id
	 * @param id id of the branch
	 * @throws Exception throws exception if no branch with given id
	 */
	public void deleteBranch(int id) throws Exception {
		branches.remove(getBranchIndexById(id));
	}
}
