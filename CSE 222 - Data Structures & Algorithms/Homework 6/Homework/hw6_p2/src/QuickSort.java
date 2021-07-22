
public class QuickSort {
	public static <T extends Comparable<T>> void sort(T[] table) {
		quickSort(table,0,table.length-1);
	}
	
	private static <T extends Comparable<T>> void quickSort(T[] table, int first,int last) {
		if(first < last) {
			int pivIndex = partition(table,first,last);
			quickSort(table, first, pivIndex-1);
			quickSort(table, pivIndex+1, last);
		}
	} 
	
	private static <T extends Comparable<T>> int partition(T[] table, int first, int last) {
		T pivot = table[first];
		int up = first;
		int down = last;
		
		do {
			while((up < last) && (pivot.compareTo(table[up]) >= 0)) up++;
			
			while(pivot.compareTo(table[down]) < 0) down--;
			
			if(up < down) {
				swap(table,up,down);
			}
		}while(up<down);
		
		swap(table,first,down);
		return down;
	}
	
	private static <T extends Comparable<T>> void swap(T[] table, int i, int j) {
		T temp = table[i];
		table[i] = table[j];
		table[j] = temp;
	}
}
