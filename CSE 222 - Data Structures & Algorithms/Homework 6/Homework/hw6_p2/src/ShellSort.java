
public class ShellSort {
	
	public static <T extends Comparable<T>> void sort(T[] table) {
		int gap = table.length / 2;
		while (gap > 0) {
			for (int nextPos = gap; nextPos < table.length; nextPos++) {
				insert(table, nextPos, gap);
			}
			if (gap == 2) {
				gap = 1;
			} else {
				gap = (int) (gap / 2.2);
			}
		}
	}

	private static <T extends Comparable<T>> void insert(T[] table, int nextPos, int gap) {
		T nextVal = table[nextPos];
		while((nextPos > gap - 1) && (nextVal.compareTo(table[nextPos-gap]) < 0)) {
			table[nextPos] = table[nextPos-gap];
			
			nextPos -= gap;
		}
		table[nextPos] = nextVal;
	}
	
}
