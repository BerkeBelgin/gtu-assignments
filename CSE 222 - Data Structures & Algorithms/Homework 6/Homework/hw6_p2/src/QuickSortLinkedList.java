import java.util.LinkedList;

public class QuickSortLinkedList {
	public static <T extends Comparable<T>> void sort(LinkedList<T> table) {
		quickSort(table,0,table.size()-1);
	}
	
	private static <T extends Comparable<T>> void quickSort(LinkedList<T> table, int first,int last) {
		if(first < last) {
			int pivIndex = partition(table,first,last);
			quickSort(table, first, pivIndex-1);
			quickSort(table, pivIndex+1, last);
		}
	} 
	
	private static <T extends Comparable<T>> int partition(LinkedList<T> table, int first, int last) {
		T pivot = table.get(first);
		int up = first;
		int down = last;
		
		do {
			while((up < last) && (pivot.compareTo(table.get(up)) >= 0)) up++;
			
			while(pivot.compareTo(table.get(down)) < 0) down--;
			
			if(up < down) {
				swap(table,up,down);
			}
		}while(up<down);
		
		swap(table,first,down);
		return down;
	}
	
	private static <T extends Comparable<T>> void swap(LinkedList<T> table, int i, int j) {
		T temp = table.get(i);
		table.set(i, table.get(j));
		table.set(j, temp);
	}
}
