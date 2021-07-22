import java.util.Arrays;
import java.util.Random;

/**
 * A skip list that is implemented like a BTree as verny node holds an array and when necessary those arrays are split or merged
 * @author Berke Belin 171044065
 * @param <E> Generic type which implements Comparable interface
 * @see Comparable
 */
public class BTreeSkipList<E extends Comparable<E>> {
	/**
     * Head of the skip-list
     */
	private SLNode<E> head;
	/**
     * The maximum level of the skip-list
     */
	private int maxLevel;
	/**
     * Smallest power of 2 that is greater than the current skip-list size
     */
	private int maxCap;
	/**
     * Size of the skip list
     */
	private int listSize;
	/**
     * Size of sum of all arrays in the list
     */
	private int totalSize;
	
	/**
	 * The maximum number for the elements an array can hold
	 */
	private int maxDegree;
	/**
	 * The minimum number for the elements an array can hold
	 */
	private int minDegree;
	
	private Random rand = new Random();
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public BTreeSkipList(int minDegree, int maxDegree){
		if(minDegree * 2 > maxDegree)throw new IllegalArgumentException("The maximum degree should not be less than the minimum degree multiplied by 2.");
		this.minDegree = minDegree;
		this.maxDegree = maxDegree;
		listSize = 0;
		totalSize = 0;
		maxLevel = 0;
		maxCap = 0;
		head = new SLNode(maxLevel, maxDegree);
	}
	
	/**
	 * Method that returns base 2 logarithm of i
	 * @param i the value that its base 2 logarithm be calculated
	 * @return base 2 logarithm of i
	 */
	private double log2(double i) {
		return Math.log(i) / Math.log(2.0);
	}
	
	/**
     * Method to generate a logarithmic distributed integer between 1 and maxLevel.
     *  I.E. 1/2 of the values are 1, 1/4 are 2, etc.
     * @return a random logarithmic distributed int between 1 and maxLevel
     */
	private int logRandom(){
		int k = (int) log2(rand.nextInt(maxCap) + 1);
		if(k > maxLevel - 1) k = maxLevel - 1;
		return maxLevel - k;
	}
	
	/**
     * Recompute the max cap
     * @param level
     * @return
     */
	private int computeMaxCap(int level){
		return (int) Math.pow(2, level) - 1;
	}
	
	@SuppressWarnings("unchecked")
	public SLNode<E>[] search(E target){
		SLNode<E>[] pred = (SLNode<E>[]) new SLNode[maxLevel];
		SLNode<E> current = head;
		for(int i = current.links.length - 1; i >= 0; i--){
			SLNode<E> next = current.links[i];
			while(next != null && next.getSize() > 0 && next.get(next.getSize() - 1).compareTo(target) < 0){
				current = next;
				next = current.links[i];
			}
			pred[i] = current;
		}
		return pred;
	}
	
	/**
     * Find an object in the skip-list
     * @param target The item being sought
     * @return A reference to the object in the skip-list that matches
     *         the target. If not found, null is returned 
     */
	public E find(E target){
		SLNode<E>[] pred = search(target);
		if(pred[0].links != null && pred[0].links.length > 0) {
			SLNode<E> current = pred[0].links[0];
			for(int i = 0; i < current.getSize(); i++) {
				if(current.get(i) != null && current.get(i).compareTo(target) == 0)return current.get(i);
			}
		}
		return null;
	}
	
	/**
     * Inserts the given item
     * @param item The item to add
     * @return true as the item is added
     */
	public boolean add(E item){
		SLNode<E>[] pred = search(item);
		if(pred.length > 0 && pred[0].links.length > 0 && pred[0].links[0] != null && pred[0].links[0].contains(item)) {
			return false;
		}
		
		totalSize++;
		if(pred.length > 0 && pred[0].links.length > 0 && pred[0].links[0] != null && pred[0].links[0].getSize() + 1 <= maxDegree) {
			pred[0].links[0].add(item);
		} else if(pred.length > 0 && pred[0] != head && !(pred[0].links.length > 0 && pred[0].links[0] != null) && pred[0].getSize() + 1 <= maxDegree) {
			pred[0].add(item);
		} else {
			listSize++;
			if(listSize > maxCap) {
				maxLevel++;
				maxCap = computeMaxCap(maxLevel);
				head.links = Arrays.copyOf(head.links, maxLevel);
				pred = Arrays.copyOf(pred, maxLevel);
				pred[maxLevel - 1] = head;
			}
			SLNode<E> newNode = new SLNode<E>(logRandom(), maxDegree);
			
			if(pred.length > 0 && pred[0].links.length > 0 && pred[0].links[0] != null ) {
				SLNode<E> currentNode = pred[0].links[0];
				
				for(int i = 0, size = (currentNode.getSize() / 2); i < size; i++) newNode.add(currentNode.remove(0));
				
				if(currentNode.getSize() > 0 && currentNode.get(0) != null && currentNode.get(0).compareTo(item) < 0) currentNode.add(item);
				else newNode.add(item);
			} else newNode.add(item);
			
			for(int i = 0; i < newNode.links.length; i++){
				newNode.links[i] = pred[i].links[i];
				pred[i].links[i] = newNode;
			}
		}
		return true;
	}
	
	/**
     * Removes an instance of the given item
     * @param item The item to remove
     * @return true if the item is removed, false if the item is not in the list
     */
	public boolean remove(E item){
		SLNode<E>[] pred = search(item);
		if(pred.length > 0 && pred[0].links.length > 0 && pred[0].links[0] != null && pred[0].links[0].contains(item)) {
			SLNode<E> preNode = pred[0];
			SLNode<E> currentNode = preNode.links[0];
			SLNode<E> nextNode = null;
			if(currentNode.links.length > 0 && currentNode.links[0] != null) nextNode = currentNode.links[0];
			
			totalSize--;
			currentNode.remove(item);
			if(currentNode.getSize() < minDegree) {
				if(nextNode != null) {
					if(nextNode.getSize() - 1 >= minDegree) {
						currentNode.add(nextNode.remove(0));
					} else {
						while(currentNode.getSize() > 0) {
							nextNode.add(currentNode.remove(0));
						}
						listSize--;
						for(int i = 0; i < preNode.links.length; i++){
							if(pred[i].links[i] != null) pred[i].links[i] = pred[i].links[i].links[i];
						}
					}
				} else if(preNode != head) {
					if(preNode.getSize() - 1 >= minDegree) {
						currentNode.add(preNode.remove(preNode.getSize() - 1));
					} else {
						while(currentNode.getSize() > 0) {
							preNode.add(currentNode.remove(0));
						}
						listSize--;
						for(int i = 0; i < preNode.links.length; i++){
							if(pred[i].links[i] != null) pred[i].links[i] = pred[i].links[i].links[i];
						}
					}
				}
			}
			return true;
		} else return false;
	}
	
	@SuppressWarnings("rawtypes")
	public String toString(){
		if(totalSize == 0)
			return "Empty";
		StringBuilder sc = new StringBuilder();
		SLNode itr = head;
		sc.append("Head: " + maxLevel);
		int lineMaker = 0;
		while(itr.links[0] != null){
			itr = itr.links[0];
			sc.append(" --> " + itr.toString());
			lineMaker++;
			if(lineMaker == 10){
				sc.append("\n");
				lineMaker = 0;
			}
		}
		return sc.toString();
	}
	
	/**
     * Static class to contain datas and links
     * @author Berke Belgin 171044065
     * @param <E> The type of data stored. Must be a Comparable
     */
	private static class SLNode<E extends Comparable<E>> {
		public SLNode<E>[] links;
		private E[] datas;
		private int size;
		
		/**
         * Create a node of level m
         * @param m The level of the node
         * @param data The data to be stored
         */
		@SuppressWarnings("unchecked")
		public SLNode(int linkLength, int dataLength){
			links = (SLNode<E>[]) new SLNode[linkLength];
			datas = (E[]) new Comparable[dataLength];
			size = 0;
		}
		
		public int getSize() {
			return size;
		}
		
		/**
		 * Adds the element e to the right place
		 * @param e
		 */
		public void add(E e) {
			if(size < datas.length) {
				int index = 0;
				while(index < size && e.compareTo(datas[index]) > 0) index++;
				for(int i = size; i > index; i--) {
					datas[i] = datas[i - 1];
				}
				datas[index] = e;
				size++;
			}
		}
		
		/**
		 * Removes the ith elements and shifts the array if neccessary
		 * @param index index of the element to be removed
		 * @return the removed element
		 */
		public E remove(int index) {
			E obj = null;
			if(0 <= index && index < size && datas[index] != null) {
				obj = datas[index];
				datas[index] = null;
				for(int i = index; i < size - 1; i++) {
					datas[i] = datas[i + 1];
				}
				datas[size - 1] = null;
				size--;
			}
			return obj;
		}
		
		/**
		 * Removes the element which is equal to given argument
		 * @param e element to be removed
		 * @return the removed element
		 */
		public E remove(E e) {
			for(int i = 0; i < size; i++) {
				if(datas[i].compareTo(e) == 0) return remove(i);
			}
			return null;
		}
		
		/**
		 * Gets the ith element
		 * @param index of the element
		 * @return ith element
		 */
		public E get(int index) {
			if(0 <= index && index < size)return datas[index];
			else return null;
		}
		
		public boolean contains(E e) {
			for(int i = 0; i < size; i++) {
				if(datas[i].compareTo(e) == 0)return true;
			}
			return false;
		}

		public String toString(){
			String out = "[";
			for(int i = 0; i < datas.length; i++) {
				if(datas[i] != null)out += datas[i].toString();
				else out += "__";
				if(i < datas.length - 1)out += ", ";
			}
			out += "]";
			return (out + " |" + links.length + "|"); 
		}
	}
}
