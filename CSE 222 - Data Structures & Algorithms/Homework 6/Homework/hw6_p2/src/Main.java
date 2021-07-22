import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.Random;

public class Main {
	public static long selectionSort(int n, boolean isRandom) {
		Integer[] temp = new Integer[n];
		
		if(isRandom)for(int j = 0 ; j < n ; j++) temp[j] = new Random().nextInt(1000);
		else for(int i = 0 ; i < n ; i++) temp[i] = i;
		
		long startTime = System.currentTimeMillis();
		SelectionSort.sort(temp);
		long endTime = System.currentTimeMillis();
		long time = endTime - startTime;
		return time;
	}
	
	public static long bubbleSort(int n, boolean isRandom) {
		Integer[] temp = new Integer[n];
		
		if(isRandom)for(int j = 0 ; j < n ; j++) temp[j] = new Random().nextInt(1000);
		else for(int i = 0 ; i < n ; i++) temp[i] = i;
		
		long startTime = System.currentTimeMillis();
		BubbleSort.sort(temp);
		long endTime = System.currentTimeMillis();
		long time = endTime - startTime;
		return time;
	}
	
	public static long insertionSort(int n, boolean isRandom) {
		Integer[] temp = new Integer[n];
		
		if(isRandom)for(int j = 0 ; j < n ; j++) temp[j] = new Random().nextInt(1000);
		else for(int i = 0 ; i < n ; i++) temp[i] = i;
		
		long startTime = System.currentTimeMillis();
		InsertionSort.sort(temp);
		long endTime = System.currentTimeMillis();
		long time = endTime - startTime;
		return time;
	}
	
	public static long shellSort(int n, boolean isRandom) {
		Integer[] temp = new Integer[n];
		
		if(isRandom)for(int j = 0 ; j < n ; j++) temp[j] = new Random().nextInt(1000);
		else for(int i = 0 ; i < n ; i++) temp[i] = i;
		
		long startTime = System.currentTimeMillis();
		ShellSort.sort(temp);
		long endTime = System.currentTimeMillis();
		long time = endTime - startTime;
		return time;
	}
	
	public static long mergeSort(int n, boolean isRandom) {
		Integer[] temp = new Integer[n];
		
		if(isRandom)for(int j = 0 ; j < n ; j++) temp[j] = new Random().nextInt(1000);
		else for(int i = 0 ; i < n ; i++) temp[i] = i;
		
		long startTime = System.currentTimeMillis();
		MergeSort.sort(temp);
		long endTime = System.currentTimeMillis();
		long time = endTime - startTime;
		return time;
	}
	
	public static long heapSort(int n, boolean isRandom) {
		Integer[] temp = new Integer[n];
		
		if(isRandom)for(int j = 0 ; j < n ; j++) temp[j] = new Random().nextInt(1000);
		else for(int i = 0 ; i < n ; i++) temp[i] = i;
		
		long startTime = System.currentTimeMillis();
		HeapSort.sort(temp);
		long endTime = System.currentTimeMillis();
		long time = endTime - startTime;
		return time;
	}
	
	public static long quickSort(int n, boolean isRandom) {
		Integer[] temp = new Integer[n];
		
		if(isRandom)for(int j = 0 ; j < n ; j++) temp[j] = new Random().nextInt(1000);
		else for(int i = 0 ; i < n ; i++) temp[i] = i;
		
		long startTime = System.currentTimeMillis();
		QuickSort.sort(temp);
		long endTime = System.currentTimeMillis();
		long time = endTime - startTime;
		return time;
	}
	
	public static long mergeLLSort(int n, boolean isRandom) {
		LinkedList<Integer> temp = new LinkedList<Integer>();
		
		if(isRandom)for(int j = 0 ; j < n ; j++) temp.add(new Random().nextInt(1000));
		else for(int i = 0 ; i < n ; i++) temp.add(i);
		
		long startTime = System.currentTimeMillis();
		MergeSortLinkedList.sort(temp);
		long endTime = System.currentTimeMillis();
		long time = endTime - startTime;
		return time;
	}
	
	public static long quickLLSort(int n, boolean isRandom) {
		LinkedList<Integer> temp = new LinkedList<Integer>();
		
		if(isRandom)for(int j = 0 ; j < n ; j++) temp.add(new Random().nextInt(1000));
		else for(int i = 0 ; i < n ; i++) temp.add(i);
		
		long startTime = System.currentTimeMillis();
		QuickSortLinkedList.sort(temp);
		long endTime = System.currentTimeMillis();
		long time = endTime - startTime;
		return time;
	}
	
	public static void main(String[] args) {
		int[] sizes = {10000, 40000, 100000, 150000, 180000};
		long[][][] results = new long[9][5][21];
		
		//z = sort alg.
		//y = n
		//x = 21 times
		
		for(int y = 3; y < sizes.length - 1; y++) {//!!!!!!!!!!!!!!!!!
//			for(int x = 0; x < 21; x++) {
//				results[0][y][x] = selectionSort(sizes[y], x < 20);
//				System.out.println(0 + ", " + y + ", " + x + " : " + results[0][y][x]);
//			}
//			
//			for(int x = 0; x < 21; x++) {
//				results[1][y][x] = bubbleSort(sizes[y], x < 20);
//				System.out.println(1 + ", " + y + ", " + x + " : " + results[1][y][x]);
//			}
//			
//			for(int x = 0; x < 21; x++) {
//				results[2][y][x] = insertionSort(sizes[y], x < 20);
//				System.out.println(2 + ", " + y + ", " + x + " : " + results[2][y][x]);
//			}
//			
//			for(int x = 0; x < 21; x++) {
//				results[3][y][x] = shellSort(sizes[y], x < 20);
//				System.out.println(3 + ", " + y + ", " + x + " : " + results[3][y][x]);
//			}
//			
//			for(int x = 0; x < 21; x++) {
//				results[4][y][x] = mergeSort(sizes[y], x < 20);
//				System.out.println(4 + ", " + y + ", " + x + " : " + results[4][y][x]);
//			}
//			
//			for(int x = 0; x < 21; x++) {
//				results[5][y][x] = heapSort(sizes[y], x < 20);
//				System.out.println(5 + ", " + y + ", " + x + " : " + results[5][y][x]);
//			}
//
//			for(int x = 0; x < 20; x++) {
//				results[6][y][x] = quickSort(sizes[y], x < 20);
//				System.out.println(6 + ", " + y + ", " + x + " : " + results[6][y][x]);
//			}
//			
//			for(int x = 0; x < 21; x++) {
//				results[7][y][x] = mergeLLSort(sizes[y], x < 20);
//				System.out.println(7 + ", " + y + ", " + x + " : " + results[7][y][x]);
//			}
			
			for(int x = 0; x < 20; x++) {
				results[8][y][x] = quickLLSort(sizes[y], x < 20);
				System.out.println(8 + ", " + y + ", " + x + " : " + results[8][y][x]);
			}
			
			try (PrintWriter writer = new PrintWriter(new File("sort2_" + sizes[y] + ".csv"))) {
			      StringBuilder sb = new StringBuilder();
			      for(int x = 0; x < 21; x++) {
			    	  for(int z = 0; z < 9; z++) {
			    		  sb.append(results[z][y][x]);
			    		  if(z + 1 < 9)sb.append(',');
			    	  }
			    	  sb.append('\n');
			      }
			      writer.write(sb.toString());
			      writer.close();
			      
		    } catch (FileNotFoundException e) {
		      System.out.println(e.getMessage());
		    }
		}
		
		for(int z = 0; z < 9; z++) {
			for(int y = 0; y < 5; y++) {
				for(int x = 0; x < 21; x++) {
					System.out.println(z + ", " + y + ", " + x + " : " + results[z][y][x]);
			    }
		    }
	    }
	}
}