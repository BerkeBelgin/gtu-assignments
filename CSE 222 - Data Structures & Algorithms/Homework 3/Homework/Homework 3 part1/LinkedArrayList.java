import java.util.AbstractList;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;
import java.util.NoSuchElementException;

/**
 * Linked array list class that implements List interface and extends AbstractList class. This class holds data type T in nodes which has an array in it and all nodes are linked together with each node pointing the next and previous node.
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-04-02
 * @see     List
 * @see     AbstractList
 * @param <T> the type of elements held in this linked array list
 */
public class LinkedArrayList<T> extends AbstractList<T> implements List<T> {
	/**
	 * Node that holds the head of the list
	 */
	private Node head;
	/**
	 * Node that holds the root of the list
	 */
	private Node root;
	/**
	 * int that holds the size of complete list
	 */
	private int size;
	
	/**
	 * Default constructor
	 */
	LinkedArrayList(){
		head = null;
		root = null;
		size = 0;
	}
	
	/**
	 * Method that prints the state of the list by showing every element of every node as seperate arrays
	 */
	public void printDebugState() {
		System.out.print("DEBUG: ");
		if(head != null) {
			for(Node node = head; node != null; node = node.getNext()) {
				System.out.print("[");
				for(int i = 0; i < node.getCapacity(); i++) {
					if(i < node.getSize()) System.out.print(node.get(i).toString());
					else System.out.print("n");
					
					if(i + 1 < node.getCapacity()) System.out.print(", ");
				}
				System.out.print("] ");
			}
			System.out.println("");
		} else {
			System.out.println("null");
		}
	}
	
	/**
	 * Method that prints the state of the list by showing every element of every node as one single array
	 */
	public void printNormalState() {
		System.out.print("INFO:  [");
		Iterator<T> iter = iterator();
		while(iter.hasNext()) {
			System.out.print(iter.next().toString());
			if(iter.hasNext()) System.out.print(", ");
		}
		System.out.println("] ");
	}
	
	/**
	 * Method that returns the size of list
	 * @return the size of list
	 */
	@Override
	public int size() {
		return size;
	}
	
	/**
	 * Method that returns the element held by the list on given index
	 * @param index the index of the element in the list
	 * @return the element held by the list on given index
	 * @throws ArrayIndexOutOfBoundsException if index is greater than size or less than 0
	 */
	@Override
	public T get(int index) throws ArrayIndexOutOfBoundsException{
		if(0 <= index && index < size) {
			Node node = head;
			int nodeIndex = index;
			
			while(nodeIndex >= node.getSize()) {
				nodeIndex -= node.getSize();
				node = node.getNext();
			}
			
			return node.get(nodeIndex);
		}
		else throw new ArrayIndexOutOfBoundsException();
	}
	
	/**
	 * Method that sets the value of the element on given index
	 * @param index of the element that will be changed
	 * @param obj the object that will be inserted on given index
	 * @return the object inserted
	 * @throws ArrayIndexOutOfBoundsException if index is greater than size or less than 0
	 * @throws NullPointerException if object is equal to null
	 */
	@Override
	public T set(int index, T obj) throws ArrayIndexOutOfBoundsException, NullPointerException {
		if(0 <= index && index < size) {
			if(obj != null) {
				Node node = head;
				int nodeIndex = index;
				
				while(nodeIndex >= node.getSize()) {
					nodeIndex -= node.getSize();
					node = node.getNext();
				}
				
				node.set(nodeIndex, obj);
				return node.get(nodeIndex);
			} else {
				throw new NullPointerException();
			}
		}
		else throw new ArrayIndexOutOfBoundsException();
	}
	
	/**
	 * Method that inserts the object to the list on given index and shifts all other elements which has greater index, to left
	 * @param index the element that will be inserted
	 * @param obj the object that will be inserted on given index
	 * @throws ArrayIndexOutOfBoundsException if index is greater than size or less than 0
	 * @throws NullPointerException if object is equal to null
	 */
	@Override
	public void add(int index, T obj) throws ArrayIndexOutOfBoundsException, NullPointerException {
		if(0 <= index && index <= size) {
			if(obj != null) {
				if(head == null && root == null) {
					Node node = new Node();
					head = node;
					root = node;
					
					root.set(0, obj);
					size++;
				} else {
					if(index == size) {
						if(root.isFull()) {
							Node node = root;
							Node node2 = new Node();
							node2.setPrev(root);
							root.setNext(node2);
							root = node2;
							
							for(int i = 0, halfSize = node.getSize()/2; i < halfSize; i++) {
								node2.set(i, node.get(halfSize + i));
								node.set(halfSize + i, null);
							}
						}
						
						root.set(root.getSize(), obj);
						size++;
					} else {
						Node node = head;
						int nodeIndex = index;
						
						while(nodeIndex > node.getSize()) {
							nodeIndex -= node.getSize();
							node = node.getNext();
						}
						
						if(node.isFull()) {
							Node node2 = new Node();
							if(root == node)root = node2;
							else node.getNext().setPrev(node2);
							node2.setNext(node.getNext());
							node2.setPrev(node);
							node.setNext(node2);
							
							for(int i = 0, halfSize = node.getSize()/2; i < halfSize; i++) {
								node2.set(i, node.get(halfSize + i));
								node.set(halfSize + i, null);
							}
							
							if(nodeIndex > node.getSize()) {
								nodeIndex -= node.getSize();
								node = node.getNext();
							}
						}
						
						for(int i = node.getSize(); nodeIndex < i; i--) {
							node.set(i, node.get(i - 1));
						}
						node.set(nodeIndex, obj);
						size++;
					}
				}
			} else {
				throw new NullPointerException();
			}
		} else {
			throw new ArrayIndexOutOfBoundsException();
		}
	}
	
	/**
	 * Method that removes the object on given index
	 * @param index the element that will be removed
	 * @return the removed element
	 * @throws ArrayIndexOutOfBoundsException if index is greater than size or less than 0
	 */
	@Override
	public T remove(int index) throws ArrayIndexOutOfBoundsException {
		if(0 <= index && index < size) {
			Node node = head;
			int nodeIndex = index;
			
			while(nodeIndex >= node.getSize()) {
				nodeIndex -= node.getSize();
				node = node.getNext();
			}
			
			for(int i = nodeIndex; i < node.getSize() - 1; i++) {
				node.set(i, node.get(i + 1));
			}
			node.set(node.getSize() - 1, null);
			size--;
			
			if(node.isEmpty()) {
				if(head == node)head = node.getNext();
				else node.getPrev().setNext(node.getNext());
				if(root == node)root = node.getPrev();
				else node.getNext().setPrev(node.getPrev());
			}
			return node.get(nodeIndex);
		}
		else throw new ArrayIndexOutOfBoundsException();
	}
	
	/**
	 * Method that returns an iterator pointing to the head of the list
	 * @return iterator pointing to the head
	 */
	@Override
	public Iterator<T> iterator() {
        return new CustomItr();
    }
	
	/**
	 * Method that returns a list iterator pointing to the head of the list
	 * @return iterator pointing to the head
	 */
	@Override
	public ListIterator<T> listIterator() {
        return listIterator(0);
    }
	
	/**
	 * Method that returns a list iterator pointing to the given index of the list
	 * @param index list iterator will be pointing to
	 * @return iterator pointing to the given index
	 */
	@Override
	public ListIterator<T> listIterator(final int index) {
		if(0 <= index && index < size) return new CustomListItr(index);
		else throw new ArrayIndexOutOfBoundsException();
    }
	
	/**
	 * Custom Iterator class that implements Iterator interface
	 * @author Berke Belgin
	 */
	private class CustomItr implements Iterator<T> {
        int cursor = 0;

        public boolean hasNext() {
            return cursor < size();
        }

        public T next() {
        	T next;
            try {
                next = get(cursor);
            } catch (ArrayIndexOutOfBoundsException e) {
                throw new NoSuchElementException();
            }
            cursor++;
            return next;
        }

        public void remove() {
            try {
            	LinkedArrayList.this.remove(cursor - 1);
            } catch (ArrayIndexOutOfBoundsException e) {
                throw new NoSuchElementException();
            }
            cursor--;
        }
    }
	
	/**
	 * Custom ListIterator class that implements ListIterator interface
	 * @author Berke Belgin
	 */
	private class CustomListItr extends CustomItr implements ListIterator<T> {
        CustomListItr(int index) {
            cursor = index;
        }

        public boolean hasPrevious() {
            return cursor != 0;
        }

        public T previous() {
        	T previous;
            try {
                previous = get(cursor - 1);
            } catch (ArrayIndexOutOfBoundsException e) {
                throw new NoSuchElementException();
            }
            cursor--;
            return previous;
        }

        public int nextIndex() {
            return cursor;
        }

        public int previousIndex() {
            return cursor-1;
        }

        public void set(T obj) {
            try {
            	LinkedArrayList.this.set(cursor - 1, obj);
            } catch (ArrayIndexOutOfBoundsException | NullPointerException e) {
            	throw new NoSuchElementException();
            }
        }

        public void add(T obj) {
            try {
                LinkedArrayList.this.add(cursor, obj);
            } catch (ArrayIndexOutOfBoundsException | NullPointerException e) {
                throw new NoSuchElementException();
            }
            cursor++;
        }
    }
	
	/**
	 * Node class that holds elements of type T in an array in it
	 * @author Berke Belgin
	 */
	private class Node {
		private T[] array;
		private final int capacity = 8;
		private int size;
		private Node next;
		private Node prev;
		
		@SuppressWarnings("unchecked")
		public Node() {
			array = (T[]) new Object[capacity];
			size = 0;
			next = null;
			prev = null;
		}

		public int getCapacity() {
			return capacity;
		}
		public int getSize() {
			return size;
		}
		public Node getNext() {
			return next;
		}
		public Node getPrev() {
			return prev;
		}

		public void setNext(Node next) {
			this.next = next;
		}
		public void setPrev(Node prev) {
			this.prev = prev;
		}
		
		/**
		 * Method that gets the element in given local index
		 * @param index the index of the element in the array
		 * @return the element held in the array on given index
		 * @throws ArrayIndexOutOfBoundsException if index is greater than size or less than 0
		 */
		T get(int index) throws ArrayIndexOutOfBoundsException {
			if(0 <= index && index < capacity) return array[index];
			else throw new ArrayIndexOutOfBoundsException();
		}
		
		/**
		 * Method that sets the value of the element on given index in the array
		 * @param index of the element that will be set
		 * @param obj the object that will be inserted on given index
		 * @return the object inserted
		 * @throws ArrayIndexOutOfBoundsException if index is greater than size or less than 0
		 */
		T set(int index, T obj) throws ArrayIndexOutOfBoundsException {
			if(0 <= index && index < capacity) {
				if		(obj == null && array[index] != null) size--;
				else if	(obj != null && array[index] == null) size++;
				array[index] = obj;
				return array[index];
			} else throw new ArrayIndexOutOfBoundsException();
		}
		
		boolean isFull() {
			return size == capacity;
		}
		
		boolean isEmpty() {
			return size == 0;
		}
	}
}
