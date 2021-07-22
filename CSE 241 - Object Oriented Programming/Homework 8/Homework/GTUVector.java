/**
 * A vector class which extends GTUContainer
 * @author Berke Belgin
 * @param T Any given type for the array to allocate memory space and determine which type to hold
 */
public class GTUVector<T> extends GTUContainer<T>{
	@SuppressWarnings("unchecked")
	GTUVector(int maxSize){
		this.array = (T[]) new Object[maxSize];
		this.size = new Integer(0);
	}
	
	public boolean empty() {
		if(this.size == 0) {
			return true;
		} else {
			return false;
		}
	}
	public int size() {
		return this.size;
	}
	public int max_size() {
		return this.array.length;
	}
	public void insert(T obj) {
		if(this.size < this.array.length) {
			this.array[this.size] = obj;
			this.size++;
		}
	}
	public void erase(GTUIterator<T> iter) {
		if(iter.remove()) {
			for(int i = 0; i < this.max_size() - 1; i++) {
				if(this.array[i] == null) {
					this.array[i] = this.array[i + 1];
					this.array[i + 1] = null;
				}
			}
			this.size--;
		}
	}
	public void clear() {
		for(int i = 0; i < this.max_size(); i++) {
			this.array[i] = null;
		}
		this.size = 0;
	}
	public GTUIterator<T> iterator() {
		return new GTUIterator<T>(this.array, -1);
	}
	public boolean contains(Object obj) {
		for(int i = 0; i < this.array.length; i++) {
			if(this.array[i] instanceof Object && this.array[i].equals(obj)) {
				return true;
			}
		}
		return false;
	}
}
