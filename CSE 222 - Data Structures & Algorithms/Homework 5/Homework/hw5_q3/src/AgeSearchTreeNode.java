
/**
 * An interface for a class that implements an age search tree node.
 * @author Berke Belgin 171044065
 */
public interface AgeSearchTreeNode {
	
	/**
	 * Compares node with given int age
	 * @param age Age to be compared
	 * @return a negative integer, zero, or a positive integer as this object is less than, equal to, or greater than the specified object.
	 */
	public int compareTo(int age);
	
	
	/**
	 * Getter method of the node which contains a field for the amount information.
	 * @return the amount information
	 */
	public int getCount();
	
	/**
	 * Setter method of the node which contains a field for the amount information.
	 * @param count The amount the field which holds nodes amount will be set to
	 */
	public void setCount(int count);
}
