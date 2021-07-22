import java.util.ArrayList;

/**
 * Max Heap class which holds its elements in an array list and organises those elements according to the amount information in the nodes.
 * The greater a nodes amount value is, the closer it is to the root.
 * @author Berke Belgin 171044065
 * @param <E> Any type which implements MaxHeapNode interface
 * @see MaxHeapNode
 * @see ArrayList
 */
public class MaxHeap<E extends MaxHeapNode> {
	final protected MaxHeapComparator<E> comparator;
	protected ArrayList<E> heap;
	
	MaxHeap(){
		comparator = new MaxHeapComparator<E>();
		heap = new ArrayList<E>();
	}
	
	/**
	 * Returns the index of the specified target, if no such element occurs in this heap, then {@code -1} is returned.
	 * @param item target irem
	 * @return the index of the specified target, if no such element occurs in this heap, then {@code -1} is returned.
	 */
	private int indexOf(E target) {
		for(int i = heap.size() - 1; i >= 0; i--) {
			if(target.getAge() == heap.get(i).getAge()) return i;
		}
		return -1;
	}
	
	/**
	 * Helper method to swap elements
	 * @param i1 the first element
	 * @param i2 the second element
	 */
	private void swap(int i1, int i2) {
		E temp = heap.get(i1);
		heap.set(i1, heap.get(i2));
		heap.set(i2, temp);
	}
	
	/**
	 * Inserts a node with that age to the appropriate position if not exist already or increments its amount then reorganises the heap.
	 * @param item Item to be inserted.
	 * @return true if successful
	 * @throws NullPointerException if argument is null
	 */
	public boolean add(E item) throws NullPointerException {
		if(item == null)throw new NullPointerException("Given argument cannot be null");
		else {
			int childIndex = indexOf(item);
			if(childIndex == -1) {
				heap.add(item);
				childIndex = heap.size() - 1;
			} else {
				heap.get(childIndex).setCount(heap.get(childIndex).getCount() + item.getCount());
			}
			int parentIndex = (childIndex - 1) / 2;
			while(parentIndex >= 0 && comparator.compare(heap.get(childIndex), heap.get(parentIndex)) > 0) {
				swap(parentIndex, childIndex);
				childIndex = parentIndex;
				parentIndex = (childIndex - 1) / 2;
			}
			return true;
		}
	}
	
	/**
	 * Removes a node with the same age as targets age if its amount is one or decrements its amount then reorganises the heap.
	 * @param target item to be removed
	 * @return true if successful else false
	 * @throws NullPointerException if argument is null
	 */
	public boolean remove(E target) throws NullPointerException {
		if(target == null)throw new NullPointerException("Given argument cannot be null");
		else {
			int parentIndex = indexOf(target);
			if(parentIndex != -1) {
				if(heap.get(parentIndex).getCount() - target.getCount() > 0) {
					heap.get(parentIndex).setCount(heap.get(parentIndex).getCount() - target.getCount());
					
					boolean swapped;
					do {
						swapped = false;
						int leftChildIndex = 2 * parentIndex + 1;
						int rightChildIndex = leftChildIndex + 1;
						boolean hasLeft = leftChildIndex < heap.size();
						boolean hasRight = rightChildIndex < heap.size();
						
						if(hasLeft && comparator.compare(heap.get(leftChildIndex), heap.get(parentIndex)) >= 0) {
							swap(parentIndex, leftChildIndex);
							parentIndex = leftChildIndex;
							swapped = true;
						} else if (hasRight && comparator.compare(heap.get(rightChildIndex), heap.get(parentIndex)) >= 0){
							swap(parentIndex, rightChildIndex);
							parentIndex = rightChildIndex;
							swapped = true;
						}
					} while(swapped);
					
					return true;
				} else {
					boolean swapped;
					do {
						swapped = false;
						int leftChildIndex = 2 * parentIndex + 1;
						int rightChildIndex = leftChildIndex + 1;
						boolean hasLeft = leftChildIndex < heap.size();
						boolean hasRight = rightChildIndex < heap.size();
						
						if((hasLeft && hasRight && comparator.compare(heap.get(leftChildIndex), heap.get(rightChildIndex)) >= 0) || (hasLeft && !hasRight)) {
							swap(parentIndex, leftChildIndex);
							parentIndex = leftChildIndex;
							swapped = true;
						} else if (hasLeft && hasRight && comparator.compare(heap.get(leftChildIndex), heap.get(rightChildIndex)) < 0){
							swap(parentIndex, rightChildIndex);
							parentIndex = rightChildIndex;
							swapped = true;
						}
					} while(swapped);
					
					heap.remove(heap.size()- 1);
					return true;
				}
			} else return false;
		}
	}
	
	/** 
	 * Find method
	 * @param target The Comparable object being sought
	 * @return The object, if found, otherwise null
	 * @throws NullPointerException if argument is null
	 */
	public E find(E target) {
		if(target == null)throw new NullPointerException("Given argument cannot be null");
		else {
			for(int i = 0; i < heap.size(); i++)if(heap.get(i).getAge() == target.getAge()) return heap.get(i);
			return null;
		}
	}
	
	/**
	 * Method that returns the amount of people in the three whose age is younger than given age.
	 * @param age the age to be compared
	 * @return the amount of people as integer.
	 */
	public int youngerThan(int age) {
		int result = 0;
		for(int i = 0; i < heap.size(); i++)if(heap.get(i).getAge() < age)result += heap.get(i).getCount();
		return result;
	}
	
	/**
	 * Method that returns the amount of people in the three whose age is older than given age.
	 * @param age the age to be compared
	 * @return the amount of people as integer.
	 */
	public int olderThan(int age) {
		int result = 0;
		for(int i = 0; i < heap.size(); i++)if(heap.get(i).getAge() > age)result += heap.get(i).getCount();
		return result;
	}
	
	public String toString() {
		String out = "";
		for(int i = 0; i < heap.size(); i++) {
			out += heap.get(i).toString() + "\n";
		}
		return out;
	}
}
