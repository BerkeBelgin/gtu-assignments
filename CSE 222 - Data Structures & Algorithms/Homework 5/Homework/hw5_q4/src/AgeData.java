/**
 * Node class for MaxHeap to hold.
 * @author Berke Belgin 171044065
 * @see MaxHeapNode
 * @see MaxHeap
 */
public class AgeData implements MaxHeapNode{
	/**
	 * Holds the age data of the node
	 */	
	protected int age;
		
	/**
	 * Holds how many people are there in the node (also in the tree) that has the same age.
	 */
	protected int count;
		
	public AgeData(int age) {
		this.age = age;
		this.count = 1;
	}
	
	@Override
	public String toString() {
		return age + " - " + count;
	}

	@Override
	public int getAge() {
		return age;
	}

	@Override
	public int getCount() {
		return count;
	}

	@Override
	public void setCount(int count) {
		if(count > 0)this.count= count;
		else throw new IllegalArgumentException();
	}
}
