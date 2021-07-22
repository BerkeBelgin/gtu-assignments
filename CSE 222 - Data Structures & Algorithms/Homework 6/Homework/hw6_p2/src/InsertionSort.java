
public class InsertionSort {

	public static <T extends Comparable<T>> void sort(T[] table) {
		for(int nextPos = 1; nextPos < table.length; nextPos++) {
			insert(table,nextPos);
		}
	}
	
	private static <T extends Comparable<T>> void insert(T[] table, int nextPos) {
		T nextVal = table[nextPos];
		
		while(nextPos > 0 && nextVal.compareTo(table[nextPos-1]) < 0) {
			table[nextPos] = table[nextPos-1];
			nextPos--;
		}
		table[nextPos] = nextVal;
	}
}