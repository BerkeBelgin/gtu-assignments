import java.util.NoSuchElementException;

/**
 * An iterator class to handle iteration operations of container classes
 * @author Berke Belgin
 * @param T Any given type
 */
public class GTUIterator<T> {
	/**
	 * Refrence to a container classes array
	 */
	private T[] array = null;
	/**
	 * Iterators position on the array
	 */
	private Integer position = null;
	
	/**
	 * Constructor to set array and position values
	 * @param array
	 * @param position
	 */
	GTUIterator(T[] array, Integer position){
		this.array = array;
		this.position = position;
	}
	
	/**
	 * Checks if the position exceeded the array size
	 * @return true if position is less then the legnth of the array by minimum 1
	 */
	public boolean hasNext() {
		if(this.array.length - 1 > position){
			return true;
		} else {
			return false;
		}
	}
	
	/**
	 * Shifts the iterator to the next element and returns the element
	 * @return the next element
	 * @throws NoSuchElementException if out of the boundaries of the array size, throws NoSuchElementException
	 */
	public T next() throws NoSuchElementException{
		if(this.array.length - 1 > position){
			return this.array[++position];
		} else {
			throw new NoSuchElementException();
		}
	}
	
	/**
	 * Erases the element iterator is pointing to
	 * @return true if deletion is successful
	 */
	public boolean remove() {
		if(this.array[position] == null) {
			return false;
		} else if (this.array.length > position){
			this.array[position] = null;
			return true;
		} else {
			return false;
		}
	}
}
