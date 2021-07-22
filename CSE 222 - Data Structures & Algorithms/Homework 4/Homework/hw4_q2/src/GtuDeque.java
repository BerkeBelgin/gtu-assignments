import java.util.AbstractCollection;
import java.util.Collection;
import java.util.Deque;
import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Deque class that implements Deque interface and extends AbstractCollection class.
 *  This class holds data type E as a double linked list and also stores removed nodes in a seperate linked 
 *  list in order to use them later to save time from memory allocation and garbage collection.
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-04-13
 * @see     Deque
 * @see     AbstractCollection
 * @param <E> the type of elements held in this double linked list
 */
public class GtuDeque<E> extends AbstractCollection<E> implements Deque<E> {
	/**
	 * Maximum list size
	 */
	private static final int MAX_SIZE = Integer.MAX_VALUE - 8;
	/**
	 * Node that holds the head of the removed nodes stack
	 */
	private Node nodeStack = null;
	/**
	 * Node that holds the head of the list
	 */
	private Node head = null;
	/**
	 * Node that holds the tail of the list
	 */
	private Node tail = null;
	/**
	 * int that holds the size of the list
	 */
	private int size = 0;
	
	/**
	 * Method that returns a node by either creating or using the top node of removed nodes stack
	 * @param e data that gathered node will hold
	 * @param next the next node that gathered node will point to
	 * @param prev the previous node that gathered node will point to
	 * @return the node gathered
	 */
	private Node createNode(E e, Node next, Node prev){
		if(nodeStack == null) {
			return new Node(e, next, prev);
		} else {
			Node node = nodeStack;
			nodeStack = nodeStack.getNext();
			
			node.setData(e);
			node.setNext(next);
			node.setPrev(prev);
			return node;
		}
	}
	
	/**
	 * Method that pushes unused node into removed nodes stack
	 * @param node the node to be pushed
	 */
	private void deleteNode(Node node){
		node.setData(null);
		node.setNext(nodeStack);
		node.setPrev(null);
		nodeStack = node;
	}
	
	/**
	 * Returns a string representation of the object
	 */
	@Override
	public String toString() {
		String out = "";
		Iterator<E> itr = iterator();
		while(itr.hasNext()) {
			out += itr.next();
			if(itr.hasNext())out += ", ";
		}
		return out;
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
     * Inserts the specified element into the queue represented by this deque.
     *
     * <p>This method is equivalent to {@link #addLast}.
     *
     * @param e the element to add
     * @return {@code true} (as specified by {@link Collection#add})
     * @throws IllegalStateException if the element cannot be added at this
     *         time due to capacity restrictions
     * @throws IllegalArgumentException if some property of the specified
     *         element prevents it from being added to this deque
     */
	@Override
	public boolean add(E e) throws IllegalStateException, IllegalArgumentException {
		addLast(e);
		return true;
    }
	
	/**
     * Pushes an element onto the stack represented by this deque.
     *
     * <p>This method is equivalent to {@link #addFirst}.
     *
     * @param e the element to push
     * @throws IllegalStateException if the element cannot be added at this
     *         time due to capacity restrictions
     * @throws IllegalArgumentException if some property of the specified
     *         element prevents it from being added to this deque
     */
	@Override
	public void push(E e) throws IllegalStateException, IllegalArgumentException {
		addFirst(e);
	}
	
	/**
     * Inserts the specified element at the front of this deque if it is
     * possible to do so immediately without violating capacity restrictions.
     *
     * @param e the element to add
     * @throws IllegalStateException if the element cannot be added at this
     *         time due to capacity restrictions
     * @throws IllegalArgumentException if some property of the specified
     *         element prevents it from being added to this deque
     */
	@Override
	public void addFirst(E e) throws IllegalStateException, IllegalArgumentException {
		if(!offerFirst(e))throw new IllegalStateException();
		
	}

	/**
     * Inserts the specified element at the end of this deque if it is
     * possible to do so immediately without violating capacity restrictions.
     *
     * <p>This method is equivalent to {@link #add}.
     *
     * @param e the element to add
     * @throws IllegalStateException if the element cannot be added at this
     *         time due to capacity restrictions
     * @throws IllegalArgumentException if some property of the specified
     *         element prevents it from being added to this deque
     */
	@Override
	public void addLast(E e) throws IllegalStateException, IllegalArgumentException {
		if(!offerLast(e))throw new IllegalStateException();
	}

	/**
     * Inserts the specified element into the queue represented by this deque
     * (in other words, at the tail of this deque) if it is possible to do so
     * immediately without violating capacity restrictions.
     *
     * <p>This method is equivalent to {@link #offerLast}.
     *
     * @param e the element to add
     * @return {@code true} if the element was added to this deque, else
     *         {@code false}
     * @throws IllegalArgumentException if some property of the specified
     *         element prevents it from being added to this deque
     */
	@Override
	public boolean offer(E e) throws IllegalArgumentException {
		return offerLast(e);
	}
	
	/**
     * Inserts the specified element at the front of this deque unless it would
     * violate capacity restrictions.
     *
     * @param e the element to add
     * @return {@code true} if the element was added to this deque, else
     *         {@code false}
     * @throws IllegalArgumentException if some property of the specified
     *         element prevents it from being added to this deque
     */
	@Override
	public boolean offerFirst(E e) throws IllegalArgumentException {
		if(e == null) {
			throw new IllegalArgumentException();
		} else {
			if(size >= MAX_SIZE) {
				return false;
			} else if(size == 0){
				Node node = createNode(e, null, null);
				head = node;
				tail = node;
				size++;
				return true;
			} else {
				Node node = createNode(e, head, null);
				head.setPrev(node);
				head = node;
				size++;
				return true;
			}
		}
	}

	/**
     * Inserts the specified element at the end of this deque unless it would
     * violate capacity restrictions.
     *
     * @param e the element to add
     * @return {@code true} if the element was added to this deque, else
     *         {@code false}
     * @throws IllegalArgumentException if some property of the specified
     *         element prevents it from being added to this deque
     */
	@Override
	public boolean offerLast(E e) throws IllegalArgumentException {
		if(e == null) {
			throw new IllegalArgumentException();
		} else {
			if(size >= MAX_SIZE) {
				return false;
			} else if(size == 0){
				Node node = createNode(e, null, null);
				tail = node;
				head = node;
				size++;
				return true;
			} else {
				Node node = createNode(e, null, tail);
				tail.setNext(node);
				tail = node;
				size++;
				return true;
			}
		}
	}

	/**
     * Pops an element from the stack represented by this deque.  In other
     * words, removes and returns the first element of this deque.
     *
     * <p>This method is equivalent to {@link #removeFirst()}.
     *
     * @return the element at the front of this deque (which is the top
     *         of the stack represented by this deque)
     * @throws NoSuchElementException if this deque is empty
     */
	@Override
	public E pop() throws NoSuchElementException {
		return removeFirst();
	}
	
	/**
     * Retrieves and removes the head of the queue represented by this deque
     * (in other words, the first element of this deque).
     *
     * <p>This method is equivalent to {@link #removeFirst()}.
     *
     * @return the head of the queue represented by this deque
     * @throws NoSuchElementException if this deque is empty
     */
	@Override
	public E remove() throws NoSuchElementException {
		return removeFirst();
	}
	
	/**
     * Retrieves and removes the first element of this deque.
     *
     * @return the head of this deque
     * @throws NoSuchElementException if this deque is empty
     */
	@Override
	public E removeFirst() throws NoSuchElementException {
		E e = pollFirst();
		if(e == null)throw new NoSuchElementException();
		else return e;
	}

	/**
     * Retrieves and removes the last element of this deque.
     *
     * @return the tail of this deque
     * @throws NoSuchElementException if this deque is empty
     */
	@Override
	public E removeLast() throws NoSuchElementException {
		E e = pollLast();
		if(e == null)throw new NoSuchElementException();
		else return e;
	}

	/**
     * Retrieves and removes the head of the queue represented by this deque
     * (in other words, the first element of this deque), or returns
     * {@code null} if this deque is empty.
     *
     * <p>This method is equivalent to {@link #pollFirst()}.
     *
     * @return the first element of this deque, or {@code null} if
     *         this deque is empty
     */
	@Override
	public E poll() {
		return pollFirst();
	}
	
	/**
     * Retrieves and removes the first element of this deque,
     * or returns {@code null} if this deque is empty.
     *
     * @return the head of this deque, or {@code null} if this deque is empty
     */
	@Override
	public E pollFirst() {
		if(size == 0) {
			return null;
		} else if(size == 1){
			E e = head.getData();
			deleteNode(head);
			head = null;
			tail = null;
			size--;
			return e;
		} else {
			E e = head.getData();
			head = head.getNext();
			deleteNode(head.getPrev());
			head.setPrev(null);
			size--;
			return e;
		}
	}

	/**
     * Retrieves and removes the last element of this deque,
     * or returns {@code null} if this deque is empty.
     *
     * @return the tail of this deque, or {@code null} if this deque is empty
     */
	@Override
	public E pollLast() {
		if(size == 0) {
			return null;
		} else if(size == 1){
			E e = tail.getData();
			deleteNode(tail);
			tail = null;
			head = null;
			size--;
			return e;
		} else {
			E e = tail.getData();
			tail = tail.getPrev();
			deleteNode(tail.getNext());
			tail.setNext(null);
			size--;
			return e;
		}
	}

	/**
     * Retrieves, but does not remove, the head of the queue represented by
     * this deque (in other words, the first element of this deque).
     *
     * <p>This method is equivalent to {@link #getFirst()}.
     *
     * @return the head of the queue represented by this deque
     * @throws NoSuchElementException if this deque is empty
     */
	@Override
	public E element() throws NoSuchElementException {
		return getFirst();
	}
	
	/**
     * Retrieves, but does not remove, the first element of this deque.
     *
     * @return the head of this deque
     * @throws NoSuchElementException if this deque is empty
     */
	@Override
	public E getFirst() throws NoSuchElementException {
		if(size == 0)throw new NoSuchElementException();
		else return head.getData();
	}

	/**
     * Retrieves, but does not remove, the last element of this deque.
     *
     * @return the tail of this deque
     * @throws NoSuchElementException if this deque is empty
     */
	@Override
	public E getLast() throws NoSuchElementException {
		if(size == 0)throw new NoSuchElementException();
		else return tail.getData();
	}

	/**
     * Retrieves, but does not remove, the head of the queue represented by
     * this deque (in other words, the first element of this deque), or
     * returns {@code null} if this deque is empty.
     *
     * <p>This method is equivalent to {@link #peekFirst()}.
     *
     * @return the head of the queue represented by this deque, or
     *         {@code null} if this deque is empty
     */
	@Override
	public E peek() {
		return peekFirst();
	}
	
	/**
     * Retrieves, but does not remove, the first element of this deque,
     * or returns {@code null} if this deque is empty.
     *
     * @return the head of this deque, or {@code null} if this deque is empty
     */
	@Override
	public E peekFirst() {
		if(size == 0)return null;
		else return head.getData();
	}

	/**
     * Retrieves, but does not remove, the last element of this deque,
     * or returns {@code null} if this deque is empty.
     *
     * @return the tail of this deque, or {@code null} if this deque is empty
     */
	@Override
	public E peekLast() {
		if(size == 0)return null;
		else return tail.getData();
	}

	/**
     * Removes the first occurrence of the specified element from this deque.
     * If the deque does not contain the element, it is unchanged.
     *
     * @param o element to be removed from this deque, if present
     * @return {@code true} if an element was removed as a result of this call
     * @throws IllegalArgumentException if the specified element is null
     */
	@Override
	public boolean removeFirstOccurrence(Object o) throws IllegalArgumentException {
		if(o == null) {
			throw new IllegalArgumentException();
		} else {
			Iterator<E> itr = new Itr();
			while(itr.hasNext()) {
				E e = itr.next();
				if(o.equals(e)) {
					itr.remove();
					return true;
				}
			}
			return false;
		}
	}

	/**
     * Removes the last occurrence of the specified element from this deque.
     * If the deque does not contain the element, it is unchanged.
     *
     * @param o element to be removed from this deque, if present
     * @return {@code true} if an element was removed as a result of this call
     * @throws IllegalArgumentException if the specified element is null
     */
	@Override
	public boolean removeLastOccurrence(Object o) throws IllegalArgumentException  {
		if(o == null) {
			throw new IllegalArgumentException();
		} else {
			Iterator<E> desItr = new DesItr();
			while(desItr.hasNext()) {
				E e = desItr.next();
				if(o.equals(e)) {
					desItr.remove();
					return true;
				}
			}
			return false;
		}
	}

	/**
     * Returns an iterator over the elements in this deque in proper sequence.
     * The elements will be returned in order from first (head) to last (tail).
     *
     * @return an iterator over the elements in this deque in proper sequence
     */
	@Override
	public Iterator<E> iterator() {
		return new Itr();
	}
	
	/**
     * Returns an iterator over the elements in this deque in reverse
     * sequential order.  The elements will be returned in order from
     * last (tail) to first (head).
     *
     * @return an iterator over the elements in this deque in reverse
     * sequence
     */
	@Override
	public Iterator<E> descendingIterator() {
		return new DesItr();
	}
	
	/**
	 * Iterator class that implements Iterator interface
	 */
	private class Itr implements Iterator<E> {
		private Node node = head;
		private Node prevNode = null;
		
		@Override
		public boolean hasNext() {
			return node != null;
		}

		@Override
		public E next() {
			if(node != null) {
				E e = node.getData();
				prevNode = node;
				node = node.getNext();
				return e;
			} else {
				throw new NoSuchElementException();
			}
		}
		
		@Override
		public void remove() {
	        if(prevNode != null) {
	        	if(prevNode.getNext() != null)prevNode.getNext().setPrev(prevNode.getPrev());
	        	else tail = prevNode.getPrev();
	        	if(prevNode.getPrev() != null)prevNode.getPrev().setNext(prevNode.getNext());
	        	else head = prevNode.getNext();
	        	deleteNode(prevNode);
	        	prevNode = null;
	        } else {
	        	throw new IllegalStateException();
	        }
	    }
    }
	
	/**
	 * Descending Iterator class that implements Iterator interface and
	 * iterates over nodes from last to first
	 */
	private class DesItr implements Iterator<E> {
		private Node node = tail;
		private Node nextNode = null;
		
		@Override
		public boolean hasNext() {
			return node != null;
		}

		@Override
		public E next() {
			if(node != null) {
				E e = node.getData();
				nextNode = node;
				node = node.getPrev();
				return e;
			} else {
				throw new NoSuchElementException();
			}
		}
		
		@Override
		public void remove() {
			if(nextNode != null) {
				if(nextNode.getPrev() != null)nextNode.getPrev().setNext(nextNode.getNext());
				else head = nextNode.getNext();
				if(nextNode.getNext() != null)nextNode.getNext().setPrev(nextNode.getPrev());
				else tail = nextNode.getPrev();
				deleteNode(nextNode);
	        	nextNode = null;
	        } else {
	        	throw new IllegalStateException();
	        }
	    }
    }

	/**
	 * Node class that holds an element of type E in it and points to the
	 * previous and next nodes like a double linked list node
	 */
	private class Node {
		E data;
		Node next;
		Node prev;

		public Node(E data,Node next,Node prev){
			this.data = data;
			this.next = next;
			this.prev = prev;
		}
		
		public E getData() {
			return data;
		}
		public Node getNext() {
			return next;
		}
		public Node getPrev() {
			return prev;
		}

		public void setData(E data) {
			this.data = data;
		}
		public void setNext(Node next) {
			this.next = next;
		}
		public void setPrev(Node prev) {
			this.prev = prev;
		}
	}
}
