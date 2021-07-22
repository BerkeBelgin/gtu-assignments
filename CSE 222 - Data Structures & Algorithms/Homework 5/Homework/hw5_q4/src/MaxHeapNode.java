/**
 * An interface for a class that implements a max heap node.
 * @author Berke Belgin 171044065
 */
public interface MaxHeapNode {
	/**
	 * Getter method of the node which contains a field for the age information.
	 * @return the amount information
	 */
	public int getAge();
	
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
