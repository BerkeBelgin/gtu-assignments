public class BinarySearchTree<E extends Comparable<E>> extends BinaryTree<E> implements SearchTree<E>{
    protected boolean addReturn;
    protected E deleteReturn;
    /**
     * Starter method add.
     * pre: The object insert must implement the Comparable interface
     * @param item The object being inserted
     * @return true if the object is inserted, false if the object already exists in the tree
     */
    @Override
    public boolean add(E item) {
        root = add2(root,item);
        return addReturn;
    }
    /**
     * Recursive add method
     * post: the data field addReturn is set true if the item is added to
     * the tree, false if the item is already in the tree.
     * @param localRoot The local root of the subtree
     * @param item The object to be inserted
     * @return The new local root that now contains the inserted item
     */
    private Node<E> add2(Node<E> localRoot, E item){
        if(localRoot == null){
            addReturn = true;
            return new Node<E>(item);
        }
        else if(item.compareTo(localRoot.data) == 0){
            addReturn = false;
            return localRoot;
        }
        else if(item.compareTo(localRoot.data) < 0){
            localRoot.left = add2(localRoot.left,item);
            return localRoot;
        }
        else{
            localRoot.right = add2(localRoot.right,item);
            return localRoot;
        }
    }
    /**
     * @param target data
     * @return true if target is found in there tree otherwise false
     */
    @Override
    public boolean contains(E target) {
        E control = find(target);
        if(control == null)
            return false;
        else
            return true;
    }
    /**
     * Starter method find.
     * pre: The target object must implement the Comparable interface.
     * @param target The Comparable object being sought
     * @return The object, if found, otherwise null
     */
    @Override
    public E find(E target) {
        return (E) find2(root,target);
    }
    /**
     * Recursive find method.
     * @param localRoot The local subtree's root
     * @param target The object being sought
     * @return The object, if found, otherwise null
     */
    private E find2(Node<E> localRoot, E target){
        if(localRoot == null)
            return null;
        int compResult = target.compareTo(localRoot.data);
        if(compResult == 0)
            return localRoot.data;
        else if(compResult < 0)
            return find2(localRoot.left,target);
        else
            return find2(localRoot.right,target);
    }
    /**
     * Starter method delete
     * post: The object is not in the tree
     * @param target The object deleted from the tree
     * @return The object deleted from the tree or null
     * if the object was not in the tree
     */
    @Override
    public E delete(E target) {
        root = delete2(root,target);
        return deleteReturn;
    }
    /**
     * Recursive delete method
     * post: The item is not in the tree;
     * deleteReturn is equal to the deleted item as it was stored int the tree
     * or null if the item was not found.
     * @param localRoot The root current subtree
     * @param item The item to be deleted
     * @return The modified local root that does not contain the item
     */
    private Node<E> delete2(Node<E> localRoot, E item){
        if(localRoot == null){
            deleteReturn = null;
            return localRoot;
        }
        int compResult = item.compareTo(localRoot.data);
        if(compResult < 0){
            localRoot.left = delete2(localRoot.left,item);
            return localRoot;
        }
        else if(compResult > 0){
            localRoot.right = delete2(localRoot.right,item);
            return localRoot;
        }
        else{
            deleteReturn = localRoot.data;
            if(localRoot.left == null){
                return localRoot.right;
            }
            else if(localRoot.right == null){
                return localRoot.left;
            }
            else{
                if(localRoot.left.right == null){
                    localRoot.data = localRoot.left.data;
                    localRoot.left = localRoot.left.left;
                    return localRoot;
                }
                else{
                    localRoot.data = findLargestChild(localRoot.left);
                    return localRoot;
                }
            }
        }
    }
    /**
     * Find the node that is the inorder predecessor and replace it
     * with its left child (if any)
     * post: The inorder predecessor is removed from the tree
     * @param parent The parent of possible inorder predecessor (ip)
     * @return The data in the ip
     */
    private E findLargestChild(Node<E> parent){
        if(parent.right.right == null){
            E returnValue = parent.right.data;
            parent.right = parent.right.left;
            return returnValue;
        }
        else
            return findLargestChild(parent.right);
    }
    /**
     * Removes target(if found) from tree and returns true;
     * otherwise, returns false.
     */
    @Override
    public boolean remove(E target) {
        E control = delete(target);
        if(control == null)
            return false;
        else
            return true;
    }
}