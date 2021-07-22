public interface SearchTree<E> {
    /**
     * Inserts item where if belongs in the tree
     * @param item add data
     * @return true if item is inserted, false if it isn't (already in tree)
     */
    boolean add(E item);
    /**
     * @param target data
     * @return true if target is found in there tree
     */
    boolean contains(E target);
    /**
     * Returns a reference to the data in the node that is equal to target.
     * If no such node is found, returns null.
     */
    E find(E target);
    /**
     * Removes target(if found) from tree and returns it;
     * otherwise, returns null.
     */
    E delete(E target);
    /**
     * Removes target(if found) from tree and returns true;
     * otherwise, returns false.
     */
    boolean remove(E target);
}