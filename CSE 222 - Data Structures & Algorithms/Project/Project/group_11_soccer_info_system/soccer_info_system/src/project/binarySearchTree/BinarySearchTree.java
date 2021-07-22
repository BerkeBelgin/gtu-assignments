package project.binarySearchTree;

/**
 * Implements BinarySearchTree on top of the BinaryTree class.
 * @author Berke Belgin 171044065
 * @param <E> The type e which implements Comparable interface and will be held in binary tree.
 * @see BinaryTree
 * @see SearchTree
 * @see Comparable
 */
public class BinarySearchTree<E extends Comparable<E>> extends BinaryTree<E> implements SearchTree<E> {
	/**
	 * Return value from the public add method.
	 */
	protected boolean addReturn;
	
	/**
	 * Return value from the public delete method.
	 */
	protected E deleteReturn;

	/** 
	 * Recursive add method.
	 * post: The data field addReturn is set true if the item is added to
	 * the tree, false if the item is already in the tree.
	 * @param node The local root of the subtree
	 * @param item The object to be inserted
	 * @return The new local root that now contains the inserted item
	 */
	private Node<E> add(Node<E> node, E item) {
		if(node == null) {
			addReturn = true;
			return new Node<E>(item);
		} else if(item.compareTo(node.data) == 0) {
			addReturn = false;
			return node;
		} else if(item.compareTo(node.data) < 0) {
			node.left = add(node.left, item);
			return node;
		} else {
			node.right =  add(node.right, item);
			return node;
		}
	}
	
	/** 
	 * Starter method add.
	 * pre: The object to insert must implement the Comparable interface.
	 * @param item The object being inserted
	 * @return true if the object is inserted, false
	 * if the object already exists in the tree
	 */
	public boolean add(E item) {
		root = add(root, item);
		return addReturn;
	}

	/**
	 * Checks if tree contains given object.
	 * @param target The Comparable object being checked
	 * @return true if target found, else false
	 */
	public boolean contains(E target) {
		if(find(target) == null)return false;
		else return false;
	}

	/** 
	 * Recursive find method.
	 * @param node The local subtree's root
	 * @param target The object being sought
	 * @return The object, if found, otherwise null
	 */
	private E find(Node<E> node, E target) {
		if(node == null) {
			return null;
		} else if(target.compareTo(node.data) == 0) { 
			return node.data;
		} else if(target.compareTo(node.data) < 0) { 
			return find(node.left, target);
		} else { 
			return find(node.right, target);
		}
	}
	
	
	/** 
	 * Starter method find.
	 * pre: The target object must implement
	 * the Comparable interface.
	 * @param target The Comparable object being sought
	 * @return The object, if found, otherwise null
	 */
	public E find(E target) {
		return find(root, target);
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
	 * Recursive delete method.
	 * post: The item is not in the tree; deleteReturn is equal to the deleted item
	 * as it was stored in the tree or null if the item was not found.
	 * @param node The root of the current subtree
	 * @param item The item to be deleted
	 * @return The modified local root that does not contain the item
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
			if(node.left == null) {
				return node.right;
			} else if(node.right == null) {
				return node.left;
			} else {
				if(node.left.right == null) {
					node.data = node.left.data;
					node.left = node.left.left;
					return node;
				} else {
					node.data = findLargestChild(node.left);
					return node;
				}
			}
		}
	}

	/** 
	 * Starter method delete.
	 * post: The object is not in the tree.
	 * @param target The object to be deleted
	 * @return The object deleted from the tree or null if the object was not in the tree
	 * @throws ClassCastException if target does not implement Comparable
	 */
	public E delete(E target) {
		root = delete(root, target);
		return deleteReturn;
	}

	/**
	 * Same as delete but returns true if succesful else false.
	 * @param target The object to be deleted
	 * @return true if succesful else false
	 * @throws ClassCastException if target does not implement Comparable
	 */
	public boolean remove(E target) {
		if(delete(target) == null)return false;
		else return false;
	}
}
