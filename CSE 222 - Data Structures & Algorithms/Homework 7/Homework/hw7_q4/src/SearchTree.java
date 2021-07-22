
/** 
 * An interface for a class that implements a binary search tree.
 * @author Berke Belgin 171044065
 * @param <E> Generic type that binary search tree holds in its nodes.
 */
public interface SearchTree<E> {
	/**
	 * Inserts item where it belongs in the tree. Returns true if item is inserted, false if it isn't (already in tree).
	 * @param item item to be added.
	 * @return true if item is inserted, false if it isn't
	 */
	boolean add(E item);
	
	/**
	 * Returns true if target is found in the tree.
	 * @param target Target object to be found.
	 * @return true if target is found in the tree.
	 */
	boolean contains(E target);
	
	/**
	 * Returns a refrence to the data in the node that is equal to target. If no such node is found, returns null.
	 * @param target Target object to be found.
	 * @return a refrence to the data in the node that is equal to target. If no such node is found, returns null.
	 */
	E find(E target);
	
	/**
	 * Removes target (if found) from tree and returns it, otherwise returns null.
	 * @param target Object to be removed.
	 * @return the object removed, otherwise returns null.
	 */
	E delete(E target);
	
	/**
	 * Removes target (if found) from tree and returns true, otherwise returns false
	 * @param target Object to be removed.
	 * @return true, otherwise returns false
	 */
	boolean remove(E target);
}
