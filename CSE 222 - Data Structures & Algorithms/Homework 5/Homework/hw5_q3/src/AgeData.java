/**
 * Node class for AgeSearchTree to hold.
 * @author Berke Belgin 171044065
 * @see Comparable
 * @see AgeSearchTreeNode
 * @see AgeSearchTree
 */
public class AgeData implements Comparable<AgeData>, AgeSearchTreeNode {
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
	public int compareTo(AgeData ageData) {
		return this.age - ageData.age;
	}
	
	@Override
	public int compareTo(int age) {
		return this.age - age;
	}
	
	@Override
	public String toString() {
		return age + " - " + count;
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
