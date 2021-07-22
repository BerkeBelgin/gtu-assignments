/**
 * Class that holds ages and how many people are there with that age in binary search tree nodes
 * @author Berke Belgin 171044065
 * @param <E> The type e which implements Comparable and AgeSearchTreeNode interfaces and will be held in a binary search tree.
 * @see AgeSearchTreeNode
 * @see Comparable
 * @see BinarySearchTree
 */
public class AgeSearchTree<E extends AgeSearchTreeNode & Comparable<E>> extends BinarySearchTree<E>{
	
	/**
	 * Helper recursive method to inserts a node with that age to the appropriate position if not exist already or increments its amount.
	 * @param node local node
	 * @param item Item to be inserted.
	 * @return local node
	 */
	private Node<E> add(Node<E> node, E item) {
		if(node == null) {
			addReturn = true;
			return new Node<E>(item);
		} else if(item.compareTo(node.data) == 0) {
			node.data.setCount(node.data.getCount() + item.getCount());
			return node;
		} else if(item.compareTo(node.data) < 0) {
			node.left = add(node.left, item);
			return node;
		} else {
			node.right =  add(node.right, item);
			return node;
		}
	}
	
	public boolean add(E item) throws NullPointerException {
		if(item == null) throw new NullPointerException("Given argument cannot be null");
		else {
			root = add(root, item);
			return addReturn;
		} 
	}
	
	/** 
	 * Find the node that is the inorder predecessor and replace it with its left child (if any).
	 * post: The inorder predecessor is removed from the tree.
	 * @param parent The parent of possible inorder predecessor (ip)
	 * @return The data in the ip
	 */
	private E findLargestChild(Node<E> parent) {
		if(parent.right.right == null) {
			E returnValue = parent.right.data;
			parent.right = parent.right.left;
			return returnValue;
		} else return findLargestChild(parent.right);
	}
	
	/**
	 * Helper recursive method to delete a node with that age if its amount is one or decrements its amount.
	 * @param node local node
	 * @param target item to be removed
	 * @return local node
	 */
	private Node<E> delete(Node<E> node, E target) {
		if(node == null) {
			deleteReturn = null;
			return node;
		} else if(target.compareTo(node.data) < 0) { 
			node.left = delete(node.left, target);
			return node;
		} else if(target.compareTo(node.data) > 0) { 
			node.right = delete(node.right, target);
			return node;
		} else { 
			deleteReturn = node.data;
			if(node.data.getCount() > 1) {
				node.data.setCount(node.data.getCount() - target.getCount());
				return node;
			} else {
				if(node.left == null) {
					return node.right;
				} else if(node.right == null) {
					return node.left;
				} else {
					if(node.left.right == null) {
						node.data = node.left.data;
						node.left =node.left.left;
						return node;
					} else {
						node.data = findLargestChild(node.left);
						return node;
					}
				}
			}
		}
	}
	
	public E delete(E target) throws NullPointerException {
		if(target == null) throw new NullPointerException("Given argument cannot be null");
		else {
			root = delete(root, target);
			return deleteReturn;
		}
	}
	
	public boolean remove(E target) throws NullPointerException {
		if(target == null) throw new NullPointerException("Given argument cannot be null");
		else if(delete(target) == null)return false;
		else return false;
	}
	
	/**
	 * Helper recursive method that returns the amount of people in the three whose age is younger than given age.
	 * @param node local root
	 * @param age the age to be compared
	 * @return the amount of people as integer.
	 */
	private int youngerThan(Node<E> node, int age) {
		if(node == null) {
			return 0;
		} else if(node.data.compareTo(age) >= 0) {
			return youngerThan(node.left, age);
		} else {
			int leftSum = youngerThan(node.left, age);
			int rightSum = youngerThan(node.right, age);
			return node.data.getCount() + leftSum + rightSum;
		}
	}
	
	/**
	 * Method that returns the amount of people in the three whose age is younger than given age.
	 * @param age the age to be compared
	 * @return the amount of people as integer.
	 */
	public int youngerThan(int age) {
		return youngerThan(root, age);
	}
	
	/**
	 * Helper recursive method that returns the amount of people in the three whose age is older than given age.
	 * @param node local root
	 * @param age the age to be compared
	 * @return the amount of people as integer.
	 */
	private int olderThan(Node<E> node, int age) {
		if(node == null) {
			return 0;
		} else if(node.data.compareTo(age) <= 0) {
			return olderThan(node.right, age);
		} else {
			int leftSum = olderThan(node.left, age);
			int rightSum = olderThan(node.right, age);
			return node.data.getCount() + leftSum + rightSum;
		}
	}
	
	/**
	 * Method that returns the amount of people in the three whose age is older than given age.
	 * @param age the age to be compared
	 * @return the amount of people as integer.
	 */
	public int olderThan(int age) {
		return olderThan(root, age);
	}
}
