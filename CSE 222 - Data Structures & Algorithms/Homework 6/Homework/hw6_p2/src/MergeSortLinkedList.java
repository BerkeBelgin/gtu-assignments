import java.util.LinkedList;

public class MergeSortLinkedList {
	public static <T extends Comparable<T>> void sort(LinkedList<T> table) {
		if(table.size() > 1) {
			int halfSize = table.size()/2;

			LinkedList<T> leftTable = new LinkedList<T>();
			LinkedList<T> rightTable = new LinkedList<T>();
			
			for(int i = 0 ; i < halfSize ; i++) {
				leftTable.add(table.get(i));
			}
			
			for(int i = halfSize ; i < table.size() ; i++) {
				rightTable.add(table.get(i));
			}
			
			sort(leftTable);
			sort(rightTable);
			merge(table, leftTable, rightTable);
		}
	}

	private static <T extends Comparable<T>> void merge(LinkedList<T> outputSequence, LinkedList<T> leftSequence, LinkedList<T> rightSequence) {
		int i = 0;
		int j = 0;
		int k = 0;
		
		while (i < leftSequence.size() && j < rightSequence.size()) {
			if (leftSequence.get(i).compareTo(rightSequence.get(j)) < 0) {
				outputSequence.set(k++,leftSequence.get(i++));
			} else {
				outputSequence.set(k++,rightSequence.get(j++));
			}
		}
		while (i < leftSequence.size()) {
			outputSequence.set(k++,leftSequence.get(i++));
		}
		while (j < rightSequence.size()) {
			outputSequence.set(k++,rightSequence.get(j++));
		}
	}
}