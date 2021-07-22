
public class SelectionSort {
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public static void sort(Comparable[] table) {
		int n = table.length;
		
		for(int fill = 0; fill < n - 1; fill++) {
			
			int posMin = fill;
			for(int next = fill + 1; next < n; next++) {
				if(table[next].compareTo(table[posMin]) < 0) posMin = next;
			}
			
			Comparable temp = table[fill];
			table[fill] = table[posMin];
			table[posMin] = temp;
		}	
	}
	
}
