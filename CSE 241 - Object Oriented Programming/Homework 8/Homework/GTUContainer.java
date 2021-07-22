/**
 * An abstract class for other container classes to extend
 * @author Berke Belgin
 * @param T Any given type for the array to allocate memory space and determine which type to hold
 */
public abstract class GTUContainer<T> {
	/**
	 * 1D array to hold objects of type T
	 */
	protected T[] array = null;
	/**
	 * An integer to hold the arrays current size
	 */
	protected Integer size = null;
	
	/**
	 * Checks if the array has any objects
	 * @return boolean true if array is empty
	 */
	public abstract boolean empty();
	/**
	 * Allows us to get how many objects that the array has currently
	 * @return int object count in the array
	 */
	public abstract int size();
	/**
	 * Allows us to get how many objects can the array contain
	 * @return int the actual size of the array
	 */
	public abstract int max_size();
	/**
	 * Lets us insert an object at the end of the array
	 * @param obj The object we want to insert in the type of T
	 */
	public abstract void insert(T obj);
	/**
	 * Lets us erase the object, given iterator pointing to
	 * @param iter The iterator which points to an elements to erase
	 */
	public abstract void erase(GTUIterator<T> iter);
	/**
	 * Lets us erase all the objects in the array
	 */
	public abstract void clear();
	/**
	 * Returns an iterrator pointing to the beginning of the array
	 * @return an iterrator pointing to the beginning of the array
	 */
	public abstract GTUIterator<T> iterator();
	/**
	 * Searches if the given object is in the array or not
	 * @param obj an object to search
	 * @return boolean true if array contains that object
	 */
	public abstract boolean contains(Object obj);
}
