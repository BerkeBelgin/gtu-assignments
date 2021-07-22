import java.util.Arrays;
import java.util.Random;

public class BTreeSkipList<E extends Comparable<E>> {
	private SLNode<E> head;
	private int maxLevel;
	private int maxCap;
	
	private int listSize;
	private int totalSize;
	
	private int maxDegree;
	private int minDegree;
	
	private Random rand = new Random();
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public BTreeSkipList(int minDegree, int maxDegree){// if min * 2 > max throw illegal argument
		if(minDegree * 2 > maxDegree)throw new IllegalArgumentException("The maximum degree should not be less than the minimum degree multiplied by 2.");
		this.minDegree = minDegree;
		this.maxDegree = maxDegree;
		listSize = 0;
		totalSize = 0;
		maxLevel = 0;
		maxCap = 0;
		head = new SLNode(maxLevel, maxDegree);
	}
	
	private double log2(double i) {
		return Math.log(i) / Math.log(2.0);
	}
	
	private int logRandom(){
		int k = (int) log2(rand.nextInt(maxCap) + 1);
		if(k > maxLevel - 1) k = maxLevel - 1;
		return maxLevel - k;
	}
	
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
	
	private static class SLNode<E extends Comparable<E>> {
		public SLNode<E>[] links;
		private E[] datas;
		private int size;
		
		@SuppressWarnings("unchecked")
		public SLNode(int linkLength, int dataLength){
			links = (SLNode<E>[]) new SLNode[linkLength];
			datas = (E[]) new Comparable[dataLength];
			size = 0;
		}
		
		public int getSize() {
			return size;
		}
		
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
		
		public E remove(E e) {
			for(int i = 0; i < size; i++) {
				if(datas[i].compareTo(e) == 0) return remove(i);
			}
			return null;
		}
		
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
